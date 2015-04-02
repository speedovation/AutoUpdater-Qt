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

#include "UpdaterWindow.h"
#include "ui_UpdaterWindow.h"

#include "../Common/UpdateFileData.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QDebug>

#ifdef Q_OS_MAC
#include "CoreFoundation/CoreFoundation.h"
#endif

/**
 *
 *  Updater mode
 *
 *    Requires admin permission. Add manifest.
 *    Check chmod permission on current folders
 *
 *    Delta mode
 *      Download
 *      Extract
 *      Rename files in zip list
 *      Replace files
 *      Relaunch
 *
 *   Full update
 *      Update mode
 *        App handler will notify about new update
 *        Launch Updater in update mode
 *        Download Latest App zip from server
 *        Extract in folder  app.version name
 *        Execute this latest Updater in install mode
 *
 *      Install mode
 *        Run Updater saying you're latest and app is old folder
 *        Make a copy of app (with version name) This may be used for rollback actions
 *        Copy all files from app.version to app
 *
 *      Clean mode
 *        Run latest updater again but from app dir
 *        Remove this extracted folder
 *        Run Updater for cleaning up folder
 *
 *
 *  It requires:
 *    version
 *    download link
 *    release note link
 *
 *
 *
 * @brief UpdaterWindow::UpdaterWindow
 * @param parent
 * @param skipVersionAllowed
 * @param remindLaterAllowed
 *
 *
 */
UpdaterWindow::UpdaterWindow(QWidget *parent, bool skipVersionAllowed, bool remindLaterAllowed) :
	QMainWindow(parent),
    ui(new Ui::UpdaterWindow)
{
	ui->setupUi(this);

//	m_appIconScene = 0;

	if(!skipVersionAllowed)
		ui->skipThisVersionButton->hide();

    if(!remindLaterAllowed)
		ui->remindMeLaterButton->hide();

	// Delete on close
	setAttribute(Qt::WA_DeleteOnClose, true);

	// Set the "new version is available" string
	QString newVersString = ui->newVersionIsAvailableLabel->text().arg(QApplication::applicationName());
	ui->newVersionIsAvailableLabel->setText(newVersString);

    ui->updateDownloadProgress->hide();

    _baseManager = new BaseManager(this);


    // Connect buttons
	connect(ui->installUpdateButton, SIGNAL(clicked()),
			_baseManager->actionUpdate() , SLOT(InstallUpdate()));
	connect(ui->skipThisVersionButton, SIGNAL(clicked()),
			_baseManager->actionUpdate(), SLOT(SkipUpdate()));
	connect(ui->remindMeLaterButton, SIGNAL(clicked()),
            _baseManager->actionUpdate(), SLOT(RemindMeLater()));


    //Move the dialog away from the center
    setGeometry(0,0,this->width(),this->height());
    int i = 0;
    if ( qApp->desktop()->screenCount() > 1 )
    {
        i = qApp->desktop()->screenNumber(this) ;
    }

    //Put the dialog in the screen center
    const QRect screen = qApp->desktop()->screenGeometry(i);
    move( screen.center() - rect().center() );

    setWindowFlags(Qt::WindowStaysOnTopHint);


}

UpdaterWindow::~UpdaterWindow()
{
//	m_ui->releaseNotesWebView->stop();
	delete ui;
}

bool UpdaterWindow::UpdateWindowWithCurrentProposedUpdate()
{


	QString downloadString = ui->wouldYouLikeToDownloadLabel->text()
			.arg(QApplication::applicationName(),_baseManager->actionUpdate()->getUpdateInfo().version ,
                 _baseManager->actionUpdate()->getUpdateInfo().oldVersion );


    ui->wouldYouLikeToDownloadLabel->setText(downloadString);

    ui->releaseNotes->setHtml ( QString("<h3>What's changed</h3>Please visit for more :<br><br><a href='%1'>%1</a>")
                                .arg(_baseManager->actionUpdate()->getUpdateInfo().releaseLink) ) ;


    switch (_baseManager->actionUpdate()->getUpdateInfo().mode) {
        case DeltaMode:

            break;
        case UpdateMode:
                setWindowTitle("Software update : New update found");
//                ui->newVersionIsAvailableLabel->setText("New update found. Please download and Install it.");
                ui->newVersionIsAvailableLabel->setText( tr("A new version of %1 is available!.").arg(qApp->applicationName()) );

            break;
        case InstallMode:
            setWindowTitle("Software update : Installing...");
            ui->newVersionIsAvailableLabel->setText( tr("Don't close this or open %1. \nWe are in process of updating latest files.").arg(qApp->applicationName()) );
//            ui->newVersionIsAvailableLabel->hide();
            ui->wouldYouLikeToDownloadLabel->hide();
            showProgress(true);

            break;
        case CleanMode:
            setWindowTitle("Software update : Cleaning...");
            ui->newVersionIsAvailableLabel->setText("We're cleaning. In a minute we will be ready.");

//            ui->newVersionIsAvailableLabel->hide();
            ui->wouldYouLikeToDownloadLabel->hide();
            showProgress(true);


            break;
        default:
            qDebug() << "Error : no mode found";
            exit(100);
            break;
    }




    //Get change notes from download link and set it inside
    //m_ui->releaseNotes

//	m_ui->releaseNotesWebView->stop();
//	m_ui->releaseNotesWebView->load(proposedUpdate->GetReleaseNotesLink());

    show();

	return true;
}

void UpdaterWindow::closeEvent(QCloseEvent* event)
{
    hide();
    event->accept();
}

BaseManager* UpdaterWindow::manager()
{
    return _baseManager;
}

UpdateDownloadProgress* UpdaterWindow::updateDownloadProgress()
{
    return ui->updateDownloadProgress;
}

void UpdaterWindow::showProgress(bool show)
{
    if(show)
    {
        ui->updateDownloadProgress->show();
        ui->installUpdateButton->hide();
        ui->remindMeLaterButton->hide();
        ui->skipThisVersionButton->hide();

    }
    else
    {
        ui->updateDownloadProgress->hide();
    }
}

/// Handler
/// Include 	This in handler before shown
///
/// /// FIX with manager Create a new window
///m_updaterWindow = new UpdaterWindow(NULL, skipVersionAllowed, remindLaterAllowed);
///m_updaterWindow->UpdateWindowWithCurrentProposedUpdate();
///m_updaterWindow->show();

