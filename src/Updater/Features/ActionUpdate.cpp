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
#include "../Common/IgnoredVersions.h"


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

    //	 Start ignoring this particular version
	IgnoredVersions::setVersionIgnored(_updateInfo.version);
    d->manager()->messageDialogs()->showInformationDialog("This version is skipped.");
    exit(0);

}

void ActionUpdate::RemindMeLater()
{
	qDebug() << "Remind me later";

    // hide update window
    exit(0);
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


///
/// TODO  : NO support for SSL
void ActionUpdate::InstallUpdate()
{
	qDebug() << "Install update";

	QUrl url = QUrl(_updateInfo.downloadLink);

	// Check SSL Fingerprint if required
//	if(url.scheme()=="https" && !d->manager()->ssl()->m_requiredSslFingerprint.isEmpty())
//		if( ! d->manager()->ssl()->checkSslFingerPrint(url) )	// check failed
//		{
//			qWarning() << "Update aborted.";
//			return;
//		}


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

    d->showProgress(true);
}


void ActionUpdate::httpUpdateDownloadFinished()
{
	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    d->showProgress(false);

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

               d->manager()->zip()->extract(reply);
			else
                qDebug()<<"Error: QNetworkReply is not readable!";
		}
		else
		{
			qDebug()<<"Download errors ocurred! HTTP Error Code:"<<httpstatuscode;
		}

		reply->deleteLater();
    }	// If !reply->error END
}	// httpUpdateDownloadFinished END


UpdateInfo ActionUpdate::getUpdateInfo()
{
    return _updateInfo;
}

void ActionUpdate::setUpdateInfo(UpdateInfo info)
{
    _updateInfo = info;
}

/**
 * @brief ActionUpdate::clean
 *
 * Remove directory
 */
void ActionUpdate::clean()
{
    QDir dir(_updateInfo.localFolderPath);

    dir.removeRecursively();

    ///Restart APP
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
