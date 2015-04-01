/****************************************************************************
**
** Copyright (C) 2015 Yash Pal, Speedovation
**
** Contact: Speedovation Lab (info@speedovation.com)
**
** KineticWing Auto Updater
** http:// kineticwing.com
** This file is part of the KiWi Editor (IDE)
**
** Author: Yash Pal
** License : Apache License 2.0
**
** All rights are reserved.
**
**/

#ifndef MODE_H
#define MODE_H

#include <QtCore/QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QNetworkReply;
QT_END_NAMESPACE


class Mode : public QObject
{
        Q_OBJECT
    public:
        Mode( UpdaterWindow *window);
        ~Mode();

        void deltaUpdateMode();

        void updateMode();


    private:
        UpdaterWindow *d;

};

#endif // MODE_H
