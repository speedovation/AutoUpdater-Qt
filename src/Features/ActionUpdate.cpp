/****************************************************************************
**
** Copyright (C) 2015 Yash Pal, Speedovation
** Copyright (C) 2012 Linas Valiukas
**
** Contact: Speedovation Lab (info@speedovation.com)
**
** KineticWing Auto Updater
** http:// kineticwing.com
** This file is part of the KiWi Editor (IDE)
**
** Author: Yash Pal, Linas Valiukas
** License : Apache License 2.0
**
** All rights are reserved.
**
**/

#include "ActionUpdate.h"

#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QNetworkReply>
#include <QDesktopServices>

#include "UpdaterWindow.h"
#include "Partials/UpdateDownloadProgress.h"
#include "Common/IgnoredVersions.h"

#define FV_NEW_VERSION_POLICY_KEY  "FVNewVersionPolicy"

ActionUpdate::ActionUpdate(UpdaterWindow* window) : QObject(window),  d(window)
{

}

ActionUpdate::~ActionUpdate()
{

}


void ActionUpdate::SkipUpdate()
{
	qDebug() << "Skip update";

	UpdateFileData* proposedUpdate = d->manager()->parseUpdate()->getProposedUpdate();
	if (! proposedUpdate) {
		qWarning() << "Proposed update is NULL (shouldn't be at this point)";
		return;
	}

    //	 Start ignoring this particular version
	IgnoredVersions::setVersionIgnored(proposedUpdate->getEnclosureVersion());

}

void ActionUpdate::RemindMeLater()
{
	// qDebug() << "Remind me later";

    // hide update window
    d->hide();
}

void ActionUpdate::UpdateInstallationConfirmed()
{
	qDebug() << "Confirm update installation";

    UpdateFileData* proposedUpdate = d->manager()->parseUpdate()->getProposedUpdate();
	if (! proposedUpdate) {
		qWarning() << "Proposed update is NULL (shouldn't be at this point)";
		return;
	}


	// Open a link
	if (! QDesktopServices::openUrl(proposedUpdate->getEnclosureUrl())) {
		d->manager()->messageDialogs()->showErrorDialog(tr("Unable to open this link in a browser. Please do it manually."), true);
		return;
	}

	//hideUpdaterWindow();
	//hideUpdateConfirmationDialog();
}

void ActionUpdate::finishUpdate(QString pathToFinish)
{
	pathToFinish = pathToFinish.isEmpty() ? QCoreApplication::applicationDirPath() : pathToFinish;
	QDir appDir(pathToFinish);
	appDir.setFilter( QDir::Files | QDir::Dirs );

	QFileInfoList dirEntries = appDir.entryInfoList();
	foreach (QFileInfo fi, dirEntries)
	{
		if ( fi.isDir() )
		{
            QString dirname = fi.fileName();
            if ((dirname==".") || (dirname == ".."))
                continue;

			// recursive clean up subdirectory
			finishUpdate(fi.filePath());
		}
		else
		{
			if(fi.suffix()=="oldversion")
				if( !appDir.remove( fi.absoluteFilePath() ) )
					qDebug()<<"Error: Unable to clean up file: "<<fi.absoluteFilePath();

		}
	}	// For each dir entry END
}


void ActionUpdate::decideWhatToDoWithCurrentUpdateProposal()
{
    QSettings settings(QSettings::NativeFormat,
                       QSettings::UserScope,
                       QCoreApplication::organizationDomain(),
                       QCoreApplication::applicationName());

    QString policy = settings.value(FV_NEW_VERSION_POLICY_KEY).toString();
	if(policy == "install")
		InstallUpdate();
	else if(policy == "skip")
		SkipUpdate();
	else
		RemindMeLater();
}


void ActionUpdate::InstallUpdate()
{
	qDebug() << "Install update";
	if(d->manager()->parseUpdate()->getProposedUpdate()==NULL)
	{
		qWarning() << "Abort Update: No update prososed! This should not happen.";
		return;
	}

	//showUpdateConfirmationDialogUpdatedWithCurrentUpdateProposal();
	// Prepare download
	QUrl url = d->manager()->parseUpdate()->getProposedUpdate()->getEnclosureUrl();

	// Check SSL Fingerprint if required
	if(url.scheme()=="https" && !d->manager()->ssl()->m_requiredSslFingerprint.isEmpty())
		if( ! d->manager()->ssl()->checkSslFingerPrint(url) )	// check failed
		{
			qWarning() << "Update aborted.";
			return;
		}


	// Start Download
	QNetworkReply* reply = m_qnam.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()), this, SLOT(httpUpdateDownloadFinished()));

	// Maybe Check request 's return value
	if (reply->error() != QNetworkReply::NoError)
	{
		qDebug()<<"Unable to download the update: "<<reply->errorString();
		return;
	}
	else
		qDebug()<<"OK";


	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), d->updateDownloadProgress(), SLOT(downloadProgress(qint64, qint64) ));


    ///On finish hide bar and don't close
    ///connect(&m_qnam, SIGNAL(finished(QNetworkReply*)), d->updateDownloadProgress(), SLOT(close()));


    //dlwindow->show();
	emit updatedFinishedSuccessfully();

    //Don't hide show progress on widget itself...I mean window
}


void ActionUpdate::httpUpdateDownloadFinished()
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


