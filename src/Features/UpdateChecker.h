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

#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

class UpdateChecker : public QObject
{
        Q_OBJECT
    public:
        UpdateChecker(UpdaterWindow *window);
        ~UpdateChecker();


    public slots:
        // Check for updates
        bool CheckForUpdates(bool silentAsMuchAsItCouldGet = true);

        // Aliases
        bool CheckForUpdatesSilent();
        bool CheckForUpdatesNotSilent();

    private slots:

    private:
        UpdaterWindow *d;


};

#endif // UPDATECHECKER_H
