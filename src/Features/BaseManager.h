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

#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <QObject>

//class UpdaterWindow;
//class GetReleaseNotes;
//class Authenticator;
//class UpdateChecker;
//class ParseUpdate;
//class GetUpdate;


#include "GetReleaseNotes.h"
//#include "GetUpdate.h"
//#include "ParseUpdate.h"
//#include "UpdateChecker.h"
#include "Authenticator.h"
#include "MessageDialogs.h"
#include "Zip.h"
#include "Helper.h"
#include "ActionUpdate.h"

#include "Tests.h"

class BaseManager : public QObject
{
        Q_OBJECT
    public:
        explicit BaseManager(UpdaterWindow *window);
        ~BaseManager();

        GetReleaseNotes* getReleaseNotes();
        Authenticator* authenticator();

        MessageDialogs* messageDialogs();
        Zip* zip();
        Helper* helper();
        ActionUpdate* actionUpdate();

        Tests* tests();



    signals:

    public slots:

    private:
        friend class BaseWindow;
        UpdaterWindow *d;

        GetReleaseNotes* _getReleaseNotes;
        Authenticator* _authenticator;

        MessageDialogs* _messageDialogs;
        Zip* _zip;
        Helper* _helper;
        ActionUpdate* _actionUpdate;

        Tests* _tests;

};

#endif // BASEMANAGER_H
