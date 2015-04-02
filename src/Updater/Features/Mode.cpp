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

#include "Mode.h"
#include "UpdaterWindow.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QNetworkReply>

#ifdef Q_OS_MAC
#include "CoreFoundation/CoreFoundation.h"
#endif

//#include "Mode_file.hpp"


Mode::Mode(UpdaterWindow* window) : d(window)
{

}

Mode::~Mode()
{

}

void Mode::handler(const QStringList& args)
{
    qDebug() <<"Arguments: " << qApp->arguments();

    if(args.count() < 2)
    {
        qDebug() << "Don't run app without proper mode.";
        exit(500);
    }

    UpdateInfo info;
    info.mode = (UpdateModeFlag)args.at(1).toInt();

    //Find out which mode is supplied and no. of arguments depend on mod

    ///Update mode requires 6(1 is mode itself) arguments
    /// Update Mode
    /// Filename  Mode Downloadlink releaselink version oldversion
    ///
    /// Install mode
    /// Filename Mode apppath localfolderpath
    ///
    /// Clean mode
    /// Filename Mode localfolderpath
    ///
    ///

    bool error = false;

    switch (info.mode) {
        case UpdateMode:
            if(qApp->arguments().count() >= 6)
            {
                info.downloadLink = args.at(2);
                info.releaseLink =args.at(3);
                info.version = args.at(4);
                info.oldVersion = args.at(5);
            }
            else
                error = true;

            break;
        case InstallMode:
            if(qApp->arguments().count() >= 4)
            {
                info.appPath = args.at(2);
                info.localFolderPath =args.at(3);
            }
            else
                error = true;
            break;
        case CleanMode:
            if(qApp->arguments().count() >= 3)
            {
                info.localFolderPath =args.at(2);
            }
            else
                error = true;
            break;
        default:
            break;
    }

    if(error)
    {
        qDebug() << "Wrong arguments";

        d->show();
        return;
        ///REMOVE below comment when in production
//        exit(100);
    }


    d->manager()->actionUpdate()->setUpdateInfo(info);
    d->UpdateWindowWithCurrentProposedUpdate();


}

/**
 * This is old updater trigger by app when new update found
 *
 * Update mode
 *   App handler will notify about new update
 *   Launch Updater in update mode
 *
 * ConfirmUpdate will call this function
 *
 * Download Latest App zip from server
 * Extract in folder  app.version name
 * Execute this latest Updater in install mode
 *
 *
 * @brief Mode::updateMode
 */
void Mode::updateMode()
{

    // Call download link
    // download file

    // It will trigger extract action
    // Run updater in install mode


}

/**
 *    Delta mode
 *      Download
 *      Extract
 *      Rename files in zip list
 *      Replace files
 *      Relaunch
 *
 * @brief Mode::deltaUpdateMode
 *
 */
void Mode::deltaUpdateMode()
{
    //
}
