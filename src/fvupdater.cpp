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

void FvUpdater::SkipUpdate()
{
	qDebug() << "Skip update";

///	UpdateFileData* proposedUpdate = GetProposedUpdate();
///	if (! proposedUpdate) {
///		qWarning() << "Proposed update is NULL (shouldn't be at this point)";
///		return;
///	}

	// Start ignoring this particular version
///	FVIgnoredVersions::IgnoreVersion(proposedUpdate->getEnclosureVersion());

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
//	qDebug() << "Confirm update installation";

///	UpdateFileData* proposedUpdate = GetProposedUpdate();
///	if (! proposedUpdate) {
///		qWarning() << "Proposed update is NULL (shouldn't be at this point)";
///		return;
///	}

///	// Open a link
///	if (! QDesktopServices::openUrl(proposedUpdate->getEnclosureUrl())) {
///		showErrorDialog(tr("Unable to open this link in a browser. Please do it manually."), true);
///		return;
///	}

	//hideUpdaterWindow();
	//hideUpdateConfirmationDialog();
}

void FvUpdater::UpdateInstallationNotConfirmed()
{
	qDebug() << "Do not confirm update installation";

	hideUpdateConfirmationDialog();	// if any; shouldn't be shown at this point, but who knows
	// leave the "update proposal window" inact
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
