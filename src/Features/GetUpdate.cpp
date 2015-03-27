#include "GetUpdate.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFile>
#include <QApplication>
#include <QFileInfo>

#include "UpdaterWindow.h"

#include "Partials/UpdateDownloadProgress.h"
#include "UpdateFileData/UpdateFileData.h"
#include "fvignoredversions.h"

GetUpdate::GetUpdate(UpdaterWindow *window) : QObject(window), d(window)
{
    skipVersionAllowed = true;
	remindLaterAllowed = true;
    m_reply = 0;

}

GetUpdate::~GetUpdate()
{


}

void GetUpdate::startDownloadFeed(QUrl url)
{
	d->manager()->parseUpdate()->m_xml.clear();

	// Check SSL Fingerprint if required
	if(url.scheme()=="https" && ! d->manager()->ssl()->m_requiredSslFingerprint.isEmpty())
		if( !d->manager()->ssl()->checkSslFingerPrint(url) )	// check failed
		{
			qWarning() << "Update aborted.";
			return;
		}


	m_reply = m_qnam.get(QNetworkRequest(url));

	connect(m_reply, SIGNAL(readyRead()), this, SLOT(httpFeedReadyRead()));
	connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(httpFeedUpdateDataReadProgress(qint64, qint64)));
	connect(m_reply, SIGNAL(finished()), this, SLOT(httpFeedDownloadFinished()));
}

void GetUpdate::cancelDownloadFeed()
{
	if (m_reply) {
		m_httpRequestAborted = true;
		m_reply->abort();
	}
}


void GetUpdate::httpFeedReadyRead()
{
	// this slot gets called every time the QNetworkReply has new data.
	// We read all of its new data and write it into the file.
	// That way we use less RAM than when reading it at the finished()
	// signal of the QNetworkReply
	d->manager()->parseUpdate()->m_xml.addData(m_reply->readAll());
}

void GetUpdate::httpFeedUpdateDataReadProgress(qint64 bytesRead,
											   qint64 totalBytes)
{
	Q_UNUSED(bytesRead);
	Q_UNUSED(totalBytes);

	if (m_httpRequestAborted) {
		return;
	}
}

void GetUpdate::httpFeedDownloadFinished()
{
	if (m_httpRequestAborted) {
		m_reply->deleteLater();
		return;
	}

	QVariant redirectionTarget = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	if (m_reply->error()) {

		// Error.
		///showErrorDialog(tr("Feed download failed: %1.").arg(m_reply->errorString()), false);

	} else if (! redirectionTarget.isNull()) {
		QUrl newUrl = m_feedURL.resolved(redirectionTarget.toUrl());

		m_feedURL = newUrl;
		m_reply->deleteLater();

		startDownloadFeed(m_feedURL);
		return;

	} else {

		// Done.
		d->manager()->parseUpdate()->xmlParseFeed();

	}

	m_reply->deleteLater();
	m_reply = 0;
}

void GetUpdate::setFeedURL(QUrl feedURL)
{
	m_feedURL = feedURL;
}

void GetUpdate::setFeedURL(QString feedURL)
{
	setFeedURL(QUrl(feedURL));
}

QString GetUpdate::getFeedURL()
{
	return m_feedURL.toString();
}



void GetUpdate::setSkipVersionAllowed(bool allowed)
{
	skipVersionAllowed = allowed;
}

void GetUpdate::setRemindLaterAllowed(bool allowed)
{
	remindLaterAllowed = allowed;
}

bool GetUpdate::getSkipVersionAllowed()
{
	return skipVersionAllowed;
}

bool GetUpdate::getRemindLaterAllowed()
{
	return remindLaterAllowed;
}




void GetUpdate::httpUpdateDownloadFinished()
{
	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
	if(reply==NULL)
	{
		qWarning()<<"The slot httpUpdateDownloadFinished() should only be invoked by S&S.";
		return;
	}

	if(reply->error() == QNetworkReply::NoError)
	{
		int httpstatuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

		// no error received?
		if (reply->error() == QNetworkReply::NoError)
		{
			if (reply->isReadable())
			{
#ifdef Q_WS_MAC
                CFURLRef appURLRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
                char path[PATH_MAX];
                if (!CFURLGetFileSystemRepresentation(appURLRef, TRUE, (UInt8 *)path, PATH_MAX)) {
                    // error!
                }

                CFRelease(appURLRef);
                QString filePath = QString(path);
                QString rootDirectory = filePath.left(filePath.lastIndexOf("/"));
#else
                QString rootDirectory = QCoreApplication::applicationDirPath() + "/";
#endif

				// Write download into File
				QFileInfo fileInfo=reply->url().path();
				QString fileName = rootDirectory + fileInfo.fileName();
				//qDebug()<<"Writing downloaded file into "<<fileName;

				QFile file(fileName);
				file.open(QIODevice::WriteOnly);
				file.write(reply->readAll());
				file.close();

				// Retrieve List of updated files (Placed in an extra scope to avoid QuaZIP handles the archive permanently and thus avoids the deletion.)
				{
///					QuaZip zip(fileName);
///					if (!zip.open(QuaZip::mdUnzip)) {
///						qWarning("testRead(): zip.open(): %d", zip.getZipError());
///						return;
///					}
///					zip.setFileNameCodec("IBM866");
///					QList<QuaZipFileInfo> updateFiles = zip.getFileInfoList();

					// Rename all current files with available update.
///					for (int i=0;i<updateFiles.size();i++)
///					{
///						QString sourceFilePath = rootDirectory + "\\" + updateFiles[i].name;
///						QDir appDir( QCoreApplication::applicationDirPath() );

///						QFileInfo file(	sourceFilePath );
///						if(file.exists())
///						{
///							//qDebug()<<tr("Moving file %1 to %2").arg(sourceFilePath).arg(sourceFilePath+".oldversion");
///							appDir.rename( sourceFilePath, sourceFilePath+".oldversion" );
///						}
///					}
				}

				// Install updated Files
				///unzipUpdate(fileName, rootDirectory);

				// Delete update archive
                while(QFile::remove(fileName) )
                {
                };

				// Restart ap to clean up and start usual business
				d->manager()->helper()->restartApplication();

			}
			else qDebug()<<"Error: QNetworkReply is not readable!";
		}
		else
		{
			qDebug()<<"Download errors ocurred! HTTP Error Code:"<<httpstatuscode;
		}

		reply->deleteLater();
    }	// If !reply->error END
}	// httpUpdateDownloadFinished END

