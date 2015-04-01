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

#include "HandlerManager.h"

HandlerManager::HandlerManager() :
    QObject()
{
    _updateChecker = new UpdateChecker(this);
    _parseUpdate = new ParseUpdate(this);
    _getUpdate = new GetUpdate(this);
        _ssl = new Ssl(this);
}

UpdateChecker* HandlerManager::updateChecker()
{
    return _updateChecker;
}
ParseUpdate* HandlerManager::parseUpdate()
{
    return _parseUpdate;
}
GetUpdate* HandlerManager::getUpdate()
{
    return _getUpdate;
}
Ssl* HandlerManager::ssl()
{
    return _ssl;
}
