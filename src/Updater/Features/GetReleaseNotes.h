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

#ifndef GETRELEASENOTES_H
#define GETRELEASENOTES_H

#include <QObject>

class UpdaterWindow;

class GetReleaseNotes : public QObject
{
        Q_OBJECT
    public:
        explicit GetReleaseNotes(UpdaterWindow *parent);



    signals:

    public slots:

    private slots:

    private:
        UpdaterWindow *d;


};

#endif // GETRELEASENOTES_H
