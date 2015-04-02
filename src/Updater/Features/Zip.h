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

#ifndef ZIP_H
#define ZIP_H

#include <QtCore/QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QNetworkReply;
QT_END_NAMESPACE

class zip_file;

class Zip : public QObject
{
        Q_OBJECT
    public:
        Zip( UpdaterWindow *window);
        ~Zip();


        void extract(QNetworkReply* reply);

        void extractAll(zip_file* zipFile);

    private:
        UpdaterWindow *d;

        bool copyDir(const QString &src, const QString &dest);

};

#endif // ZIP_H
