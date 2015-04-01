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

#include "BaseManager.h"

#include "UpdaterWindow.h"



BaseManager::BaseManager(UpdaterWindow* window) :
    QObject(window) , d(window)
{
    _getReleaseNotes = new GetReleaseNotes(window);
    _authenticator = new Authenticator(window);

    _messageDialogs = new MessageDialogs(window);
    _zip = new Zip(window);
    _helper = new Helper(window);
    _actionUpdate = new ActionUpdate(window);

    _tests = new Tests(window);

}

GetReleaseNotes* BaseManager::getReleaseNotes()
{
    return _getReleaseNotes;
}
Authenticator* BaseManager::authenticator()
{
    return _authenticator;
}

MessageDialogs* BaseManager::messageDialogs()
{
    return _messageDialogs;
}
Zip* BaseManager::zip()
{
    return _zip;
}
Helper* BaseManager::helper()
{
    return _helper;
}
ActionUpdate* BaseManager::actionUpdate()
{
    return _actionUpdate;
}

Tests* BaseManager::tests()
{
    return _tests;
}
