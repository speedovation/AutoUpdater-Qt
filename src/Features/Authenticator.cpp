#include "Authenticator.h"

#include "UpdaterWindow.h"

#include <QAuthenticator>
#include <QNetworkReply>

Authenticator::Authenticator()
{
    htAuthUsername = "";
	htAuthPassword = "";
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
