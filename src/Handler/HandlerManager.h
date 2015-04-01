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

#ifndef HANDLERMANAGER_H
#define HANDLERMANAGER_H

#include <QObject>

//class UpdaterWindow;
//class GetReleaseNotes;
//class Authenticator;
//class UpdateChecker;
//class ParseUpdate;
//class GetUpdate;


#include "GetUpdate.h"
#include "ParseUpdate.h"
#include "UpdateChecker.h"
#include "Ssl.h"

class HandlerManager : public QObject
{
        Q_OBJECT
    public:
        explicit HandlerManager();

        UpdateChecker* updateChecker();
        ParseUpdate* parseUpdate();
        GetUpdate* getUpdate();
  Ssl* ssl();

    signals:

    public slots:

    private:
        UpdateChecker* _updateChecker;
        ParseUpdate* _parseUpdate;
        GetUpdate* _getUpdate;
         Ssl* _ssl;

};

#endif // HANDLERMANAGER_H
