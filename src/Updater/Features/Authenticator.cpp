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

#include "Authenticator.h"

#include "UpdaterWindow.h"

#include <QAuthenticator>
#include <QNetworkReply>

Authenticator::Authenticator(UpdaterWindow* window) : d(window)
{
    htAuthUsername = "";
	htAuthPassword = "";


    /// Use Manager and connect
	///connect(&m_qnam, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
    ///        this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));

}

Authenticator::~Authenticator()
{

}

void Authenticator::authenticationRequired ( QNetworkReply * reply, QAuthenticator * authenticator )
{
	if(reply==NULL || authenticator==NULL)
		return;

	if(!authenticator->user().isEmpty())	// If there is already a login user set but an authentication is still required: credentials must be wrong -> abort
	{
		reply->abort();
		qWarning()<<"Http authentication: Wrong credentials!";
		return;
	}

	authenticator->setUser(htAuthUsername);
	authenticator->setPassword(htAuthPassword);
}

void Authenticator::setHtAuthCredentials(QString user, QString pass)
{
	htAuthUsername = user;
	htAuthPassword = pass;
}

void Authenticator::setHtAuthUsername(QString user)
{
	htAuthUsername = user;
}

void Authenticator::setHtAuthPassword(QString pass)
{
	htAuthPassword = pass;
}
