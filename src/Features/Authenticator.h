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

#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

class Authenticator : public QObject
{
        Q_OBJECT
    public:
        Authenticator(UpdaterWindow *window);
        ~Authenticator();

        // HTTP Authentuication - for security reasons no getters are provided, only a setter
        void setHtAuthCredentials(QString user, QString pass);
        void setHtAuthUsername(QString user);
        void setHtAuthPassword(QString pass);


    private slots:
        void authenticationRequired ( QNetworkReply * reply, QAuthenticator * authenticator );

    private:
        UpdaterWindow *d;
        //
        // Htauth-Infrastructure
        //
        QString htAuthUsername;
        QString htAuthPassword;

};

#endif // AUTHENTICATOR_H
