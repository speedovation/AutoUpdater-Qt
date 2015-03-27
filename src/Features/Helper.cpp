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

#include "Helper.h"

#include <QProcess>
#include <QTranslator>
#include <QApplication>
#include <QDir>

#include "UpdaterWindow.h"

Helper::Helper(UpdaterWindow* window) : d(window)
{
    installTranslator();
}

Helper::~Helper()
{

}

void Helper::restartApplication()
{
    // Spawn a new instance of myApplication:
    QString app = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString wd = QDir::currentPath();
    qDebug() << app << arguments << wd;
    QProcess::startDetached(app, arguments, wd);
    QApplication::exit();
}
void Helper::installTranslator()
{
    QTranslator translator;
    QString locale = QLocale::system().name();
    translator.load(QString("fervor_") + locale);

    qApp->installTranslator(&translator);
}

