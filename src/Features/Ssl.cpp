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

#include "Ssl.h"
#include <QSslSocket>
#include <QSslCertificate>

#include "UpdaterWindow.h"

Ssl::Ssl(UpdaterWindow* window) : QObject(window), d(window)
{
    m_requiredSslFingerprint = "";

}

Ssl::~Ssl()
{

}


void Ssl::setRequiredSslFingerPrint(QString md5)
{
	m_requiredSslFingerprint = md5.remove(":");
}

QString Ssl::getRequiredSslFingerPrint()
{
	return m_requiredSslFingerprint;
}

bool Ssl::checkSslFingerPrint(QUrl urltoCheck)
{
	if(urltoCheck.scheme()!="https")
	{
		qWarning()<<tr("SSL fingerprint check: The url %1 is not a ssl connection!").arg(urltoCheck.toString());
		return false;
	}

	QSslSocket *socket = new QSslSocket(this);
	socket->connectToHostEncrypted(urltoCheck.host(), 443);
	if( !socket->waitForEncrypted(1000))	// waits until ssl emits encrypted(), max 1000msecs
	{
		qWarning()<<"SSL fingerprint check: Unable to connect SSL server: "<<socket->sslErrors();
		return false;
	}

	QSslCertificate cert = socket->peerCertificate();

	if(cert.isNull())
	{
		qWarning()<<"SSL fingerprint check: Unable to retrieve SSL server certificate.";
		return false;
	}

	// COmpare digests
	if(cert.digest().toHex() != m_requiredSslFingerprint)
	{
		qWarning()<<"SSL fingerprint check: FINGERPRINT MISMATCH! Server digest="<<cert.digest().toHex()<<", requiered ssl digest="<<m_requiredSslFingerprint;
		return false;
	}

	return true;
}

