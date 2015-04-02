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

#ifndef MESSAGEDIALOGS_H
#define MESSAGEDIALOGS_H

#include <QtCore/QObject>


class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QXmlStreamReader;
QT_END_NAMESPACE


class MessageDialogs : public QObject
{
        Q_OBJECT
    public:
        MessageDialogs(UpdaterWindow *window);
        ~MessageDialogs();


        void showErrorDialog(QString message, bool showEvenInSilentMode = false);			// Show an error message
        void showInformationDialog(QString message, bool showEvenInSilentMode = false);		// Show an informational message




    private:
        UpdaterWindow *d;
};

#endif // MESSAGEDIALOGS_H
