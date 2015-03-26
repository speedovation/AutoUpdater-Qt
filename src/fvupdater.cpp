#include "fvupdater.h"
#include "UpdaterWindow.h"
#include "fvupdateconfirmdialog.h"
#include "Partials/UpdateDownloadProgress.h"
#include "UpdateFileData/UpdateFileData.h"
#include "Platform.h"
#include "fvignoredversions.h"
#include <QApplication>
#include <QtNetwork>
#include <QDebug>
#include <QSettings>
#include <QDesktopServices>

//#include "quazip.h"
//#include "quazipfile.h"

#ifdef Q_WS_MAC
#include "CoreFoundation/CoreFoundation.h"
#endif

#ifdef FV_GUI
#include "UpdaterWindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#else
// QSettings key for automatic update installation
#define FV_NEW_VERSION_POLICY_KEY              "FVNewVersionPolicy"
#endif

#ifdef FV_DEBUG
	// Unit tests
#	include "fvversioncomparatortest.h"
#endif

//extern QSettings* settings;



FvUpdater::FvUpdater() : QObject(0)
{

#ifdef FV_GUI
	m_updaterWindow = 0;
	m_updateConfirmationDialog = 0;
#endif
	m_proposedUpdate = 0;
	m_requiredSslFingerprint = "";



    /// Use Manager and connect
	///connect(&m_qnam, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
    ///        this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));

	// Translation mechanism
	installTranslator();

#ifdef FV_DEBUG
	// Unit tests
	FvVersionComparatorTest* test = new FvVersionComparatorTest();
	test->runAll();
	delete test;
#endif

}

FvUpdater::~FvUpdater()
{
	if (m_proposedUpdate) {
		delete m_proposedUpdate;
		m_proposedUpdate = 0;
	}

#ifdef FV_GUI
    hideUpdateConfirmationDialog();
	hideUpdaterWindow();
#endif
}

void FvUpdater::installTranslator()
{
	QTranslator translator;
	QString locale = QLocale::system().name();
	translator.load(QString("fervor_") + locale);

	qApp->installTranslator(&translator);
}

#ifdef FV_GUI
void FvUpdater::showUpdaterWindowUpdatedWithCurrentUpdateProposal()
{
	// Destroy window if already exists
	hideUpdaterWindow();

	/// FIX with manager Create a new window
	///m_updaterWindow = new UpdaterWindow(NULL, skipVersionAllowed, remindLaterAllowed);
	///m_updaterWindow->UpdateWindowWithCurrentProposedUpdate();
	///m_updaterWindow->show();
}

void FvUpdater::hideUpdaterWindow()
{
	if (m_updaterWindow) {
		if (! m_updaterWindow->close()) {
			qWarning() << "Update window didn't close, leaking memory from now on";
		}

		// not deleting because of Qt::WA_DeleteOnClose

		m_updaterWindow = 0;
	}
}

void FvUpdater::updaterWindowWasClosed()
{
	// (Re-)nullify a pointer to a destroyed QWidget or you're going to have a bad time.
	m_updaterWindow = 0;
}

void FvUpdater::showUpdateConfirmationDialogUpdatedWithCurrentUpdateProposal()
{
	// Destroy dialog if already exists
	hideUpdateConfirmationDialog();

	// Create a new window
///	m_updateConfirmationDialog = new FvUpdateConfirmDialog();
///	m_updateConfirmationDialog->UpdateWindowWithCurrentProposedUpdate();
///	m_updateConfirmationDialog->show();
}

void FvUpdater::hideUpdateConfirmationDialog()
{
	if (m_updateConfirmationDialog) {
		if (! m_updateConfirmationDialog->close()) {
			qWarning() << "Update confirmation dialog didn't close, leaking memory from now on";
		}

		// not deleting because of Qt::WA_DeleteOnClose

		m_updateConfirmationDialog = 0;
	}
}

void FvUpdater::updateConfirmationDialogWasClosed()
{
	// (Re-)nullify a pointer to a destroyed QWidget or you're going to have a bad time.
	m_updateConfirmationDialog = 0;
}
#endif


UpdateFileData* FvUpdater::GetProposedUpdate()
{
	return m_proposedUpdate;
}


void FvUpdater::InstallUpdate()
{
	qDebug() << "Install update";
	if(m_proposedUpdate==NULL)
	{
		qWarning() << "Abort Update: No update prososed! This should not happen.";
		return;
	}

	//showUpdateConfirmationDialogUpdatedWithCurrentUpdateProposal();
	// Prepare download
	QUrl url = m_proposedUpdate->getEnclosureUrl();

	// Check SSL Fingerprint if required
	if(url.scheme()=="https" && !m_requiredSslFingerprint.isEmpty())
		if( !checkSslFingerPrint(url) )	// check failed
		{	
			qWarning() << "Update aborted.";
			return;
		}

    ///remove below
    QNetworkAccessManager m_qnam;

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

	// Show download Window
#ifdef FV_GUI
	dlwindow = new UpdateDownloadProgress;
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), dlwindow, SLOT(downloadProgress(qint64, qint64) ));
	connect(&m_qnam, SIGNAL(finished(QNetworkReply*)), dlwindow, SLOT(close()));
	//dlwindow->show();
#endif
	emit (updatedFinishedSuccessfully());


#ifdef FV_GUI
	hideUpdaterWindow();
#endif
}

void FvUpdater::httpUpdateDownloadFinished()
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
				restartApplication();

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

bool FvUpdater::unzipUpdate(const QString & filePath, const QString & extDirPath, const QString & singleFileName )
{
//	QuaZip zip(filePath);

//    if (!zip.open(QuaZip::mdUnzip)) {
//		qWarning()<<tr("Error: Unable to open zip archive %1 for unzipping: %2").arg(filePath).arg(zip.getZipError());
//		return false;
//	}

//	zip.setFileNameCodec("IBM866");

//	//qWarning("Update contains %d files\n", zip.getEntriesCount());

//	QuaZipFileInfo info;
//	QuaZipFile file(&zip);
//	QFile out;
//	QString name;
//	QDir appDir(extDirPath);
//	for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
//	{
//		if (!zip.getCurrentFileInfo(&info)) {
//			qWarning()<<tr("Error: Unable to retrieve fileInfo about the file to extract: %2").arg(zip.getZipError());
//			return false;
//		}

//		if (!singleFileName.isEmpty())
//			if (!info.name.contains(singleFileName))
//				continue;

//		if (!file.open(QIODevice::ReadOnly)) {
//			qWarning()<<tr("Error: Unable to open file %1 for unzipping: %2").arg(filePath).arg(file.getZipError());
//			return false;
//		}

//		name = QString("%1/%2").arg(extDirPath).arg(file.getActualFileName());

//		if (file.getZipError() != UNZ_OK) {
//			qWarning()<<tr("Error: Unable to retrieve zipped filename to unzip from %1: %2").arg(filePath).arg(file.getZipError());
//			return false;
//		}
		
//		QFileInfo fi(name);
//		appDir.mkpath(fi.absolutePath() );	// Ensure that subdirectories - if required - exist
//		out.setFileName(name);
//		out.open(QIODevice::WriteOnly);
//		out.write( file.readAll() );
//		out.close();

//		if (file.getZipError() != UNZ_OK) {
//			qWarning()<<tr("Error: Unable to unzip file %1: %2").arg(name).arg(file.getZipError());
//			return false;
//		}

//		if (!file.atEnd()) {
//			qWarning()<<tr("Error: Have read all available bytes, but pointer still does not show EOF: %1").arg(file.getZipError());
//			return false;
//		}

//		file.close();

//		if (file.getZipError() != UNZ_OK) {
//			qWarning()<<tr("Error: Unable to close zipped file %1: %2").arg(name).arg(file.getZipError());
//			return false;
//		}
//	}

//	zip.close();

//	if (zip.getZipError() != UNZ_OK) {
//		qWarning()<<tr("Error: Unable to close zip archive file %1: %2").arg(filePath).arg(file.getZipError());
//		return false;
//	}

	return true;
}


void FvUpdater::SkipUpdate()
{
	qDebug() << "Skip update";

	UpdateFileData* proposedUpdate = GetProposedUpdate();
	if (! proposedUpdate) {
		qWarning() << "Proposed update is NULL (shouldn't be at this point)";
		return;
	}

	// Start ignoring this particular version
	FVIgnoredVersions::IgnoreVersion(proposedUpdate->getEnclosureVersion());

#ifdef FV_GUI
	hideUpdaterWindow();
	hideUpdateConfirmationDialog();	// if any; shouldn't be shown at this point, but who knows
#endif
}

void FvUpdater::RemindMeLater()
{
	//qDebug() << "Remind me later";

#ifdef FV_GUI
	hideUpdaterWindow();
	hideUpdateConfirmationDialog();	// if any; shouldn't be shown at this point, but who knows
#endif
}

void FvUpdater::UpdateInstallationConfirmed()
{
	qDebug() << "Confirm update installation";

	UpdateFileData* proposedUpdate = GetProposedUpdate();
	if (! proposedUpdate) {
		qWarning() << "Proposed update is NULL (shouldn't be at this point)";
		return;
	}

	// Open a link
	if (! QDesktopServices::openUrl(proposedUpdate->getEnclosureUrl())) {
		showErrorDialog(tr("Unable to open this link in a browser. Please do it manually."), true);
		return;
	}

	//hideUpdaterWindow();
	//hideUpdateConfirmationDialog();
}

void FvUpdater::UpdateInstallationNotConfirmed()
{
	qDebug() << "Do not confirm update installation";

	hideUpdateConfirmationDialog();	// if any; shouldn't be shown at this point, but who knows
	// leave the "update proposal window" inact
}



bool FvUpdater::searchDownloadedFeedForUpdates(QString xmlTitle,
											   QString xmlLink,
											   QString xmlReleaseNotesLink,
											   QString xmlPubDate,
											   QString xmlEnclosureUrl,
											   QString xmlEnclosureVersion,
											   QString xmlEnclosurePlatform,
											   unsigned long xmlEnclosureLength,
											   QString xmlEnclosureType)
{
    qDebug() << "Title:" << xmlTitle;
    qDebug() << "Link:" << xmlLink;
    qDebug() << "Release notes link:" << xmlReleaseNotesLink;
    qDebug() << "Pub. date:" << xmlPubDate;
    qDebug() << "Enclosure URL:" << xmlEnclosureUrl;
    qDebug() << "Enclosure version:" << xmlEnclosureVersion;
    qDebug() << "Enclosure platform:" << xmlEnclosurePlatform;
    qDebug() << "Enclosure length:" << xmlEnclosureLength;
    qDebug() << "Enclosure type:" << xmlEnclosureType;

	// Validate
	if (xmlReleaseNotesLink.isEmpty()) {
		if (xmlLink.isEmpty()) {
			showErrorDialog(tr("Feed error: \"release notes\" link is empty"), false);
			return false;
		} else {
			xmlReleaseNotesLink = xmlLink;
		}
	} else {
		xmlLink = xmlReleaseNotesLink;
	}
	if (! (xmlLink.startsWith("http://") || xmlLink.startsWith("https://"))) {
		showErrorDialog(tr("Feed error: invalid \"release notes\" link"), false);
		return false;
	}
	if (xmlEnclosureUrl.isEmpty() || xmlEnclosureVersion.isEmpty() || xmlEnclosurePlatform.isEmpty()) {
		showErrorDialog(tr("Feed error: invalid \"enclosure\" with the download link"), false);
		return false;
	}

	// Relevant version?
	if (FVIgnoredVersions::VersionIsIgnored(xmlEnclosureVersion)) {
		qDebug() << "Version '" << xmlEnclosureVersion << "' is ignored, too old or something like that.";

		showInformationDialog(tr("No updates were found."), false);

		return true;	// Things have succeeded when you think of it.
	}


	//
	// Success! At this point, we have found an update that can be proposed
	// to the user.
	//

	if (m_proposedUpdate) {
		delete m_proposedUpdate; m_proposedUpdate = 0;
	}
	m_proposedUpdate = new UpdateFileData();
	m_proposedUpdate->setTitle(xmlTitle);
	m_proposedUpdate->setReleaseNotesLink(xmlReleaseNotesLink);
	m_proposedUpdate->setPubDate(xmlPubDate);
	m_proposedUpdate->setEnclosureUrl(xmlEnclosureUrl);
	m_proposedUpdate->setEnclosureVersion(xmlEnclosureVersion);
	m_proposedUpdate->setEnclosurePlatform(xmlEnclosurePlatform);
	m_proposedUpdate->setEnclosureLength(xmlEnclosureLength);
	m_proposedUpdate->setEnclosureType(xmlEnclosureType);

#ifdef FV_GUI
	// Show "look, there's an update" window
	showUpdaterWindowUpdatedWithCurrentUpdateProposal();
#else
	// Decide ourselves what to do
	decideWhatToDoWithCurrentUpdateProposal();
#endif

	return true;
}


void FvUpdater::showErrorDialog(QString message, bool showEvenInSilentMode)
{
	if (m_silentAsMuchAsItCouldGet) {
		if (! showEvenInSilentMode) {
			// Don't show errors in the silent mode
			return;
		}
	}

#ifdef FV_GUI
	QMessageBox dlFailedMsgBox;
	dlFailedMsgBox.setIcon(QMessageBox::Critical);
	dlFailedMsgBox.setText(tr("Error"));
	dlFailedMsgBox.setInformativeText(message);
	dlFailedMsgBox.exec();
#else
	qCritical() << message;
#endif
}

void FvUpdater::showInformationDialog(QString message, bool showEvenInSilentMode)
{
	if (m_silentAsMuchAsItCouldGet) {
		if (! showEvenInSilentMode) {
			// Don't show information dialogs in the silent mode
			return;
		}
	}

#ifdef FV_GUI
	QMessageBox dlInformationMsgBox;
	dlInformationMsgBox.setIcon(QMessageBox::Information);
	dlInformationMsgBox.setText(tr("Information"));
	dlInformationMsgBox.setInformativeText(message);
	dlInformationMsgBox.exec();
#else
	qDebug() << message;
#endif
}

void FvUpdater::finishUpdate(QString pathToFinish)
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

void FvUpdater::restartApplication()
{
	// Spawn a new instance of myApplication:
    QString app = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString wd = QDir::currentPath();
    qDebug() << app << arguments << wd;
    QProcess::startDetached(app, arguments, wd);
    QApplication::exit();
}

void FvUpdater::setRequiredSslFingerPrint(QString md5)
{
	m_requiredSslFingerprint = md5.remove(":");
}

QString FvUpdater::getRequiredSslFingerPrint()
{
	return m_requiredSslFingerprint;
}

bool FvUpdater::checkSslFingerPrint(QUrl urltoCheck)
{
	if(urltoCheck.scheme()!="https")
	{
		qWarning()<<tr("SSL fingerprint check: The url %1 is not a ssl connection!").arg(urltoCheck.toString());
		return false;
	}

	QSslSocket *socket = new QSslSocket(this);
	socket->connectToHostEncrypted(urltoCheck.host(), 443);
	if( !socket->waitForEncrypted(1000))	// waits until ssl emits encrypted(), max 1000msecs
	{
		qWarning()<<"SSL fingerprint check: Unable to connect SSL server: "<<socket->sslErrors();
		return false;
	}

	QSslCertificate cert = socket->peerCertificate();

	if(cert.isNull())
	{
		qWarning()<<"SSL fingerprint check: Unable to retrieve SSL server certificate.";
		return false;
	}

	// COmpare digests
	if(cert.digest().toHex() != m_requiredSslFingerprint)
	{
		qWarning()<<"SSL fingerprint check: FINGERPRINT MISMATCH! Server digest="<<cert.digest().toHex()<<", requiered ssl digest="<<m_requiredSslFingerprint;
		return false;
	}
	
	return true;
}



#ifndef FV_GUI

void FvUpdater::decideWhatToDoWithCurrentUpdateProposal()
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

#endif
