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

#ifndef SSL_H
#define SSL_H

#include <QtCore/QObject>

class HandlerManager;

class Ssl : public QObject
{
        Q_OBJECT
    public:
        Ssl(HandlerManager *window);
        ~Ssl();

        void setRequiredSslFingerPrint(QString md5);
        QString getRequiredSslFingerPrint();	// returns md5!


    signals:

    public slots:

    private:
        HandlerManager *d;
    friend class GetUpdate;
        //
        // SSL Fingerprint Check infrastructure
        //
        QString m_requiredSslFingerprint;

        bool checkSslFingerPrint(QUrl urltoCheck);	// true=ssl Fingerprint accepted, false= ssl Fingerprint NOT accepted


};

#endif // SSL_H
