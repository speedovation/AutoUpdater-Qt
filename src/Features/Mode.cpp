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

}

