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


#include "UpdateChecker.h"

#include "UpdaterWindow.h"

#include <QAuthenticator>
#include <QNetworkReply>
#include <QApplication>

UpdateChecker::UpdateChecker(UpdaterWindow* window) : d(window)
{

}

UpdateChecker::~UpdateChecker()
{

}


bool UpdateChecker::CheckForUpdates(bool silentAsMuchAsItCouldGet)
{
	if (d->manager()->getUpdate()->m_feedURL.isEmpty()) {
		qCritical() << "Please set feed URL via setFeedURL() before calling CheckForUpdates().";
		return false;
	}

    d->manager()->getUpdate()->m_silentAsMuchAsItCouldGet = silentAsMuchAsItCouldGet;

	// Check if application's organization name and domain are set, fail otherwise
	// (nowhere to store QSettings to)
	if (QCoreApplication::organizationName().isEmpty()) {
		qCritical() << "QCoreApplication::organizationName is not set. Please do that.";
		return false;
	}
	if (QCoreApplication::organizationDomain().isEmpty()) {
		qCritical() << "QCoreApplication::organizationDomain is not set. Please do that.";
		return false;
	}

	if(QCoreApplication::applicationName().isEmpty()) {
		qCritical() << "QCoreApplication::applicationName is not set. Please do that.";
		return false;
	}

	// Set application version is not set yet
	if (QCoreApplication::applicationVersion().isEmpty()) {
		qCritical() << "QCoreApplication::applicationVersion is not set. Please do that.";
		return false;
	}

	d->manager()->getUpdate()->cancelDownloadFeed();
	d->manager()->getUpdate()->m_httpRequestAborted = false;
	d->manager()->getUpdate()->startDownloadFeed(d->manager()->getUpdate()->m_feedURL);


	return true;
}

bool UpdateChecker::CheckForUpdatesSilent()
{
	return CheckForUpdates(true);
}

bool UpdateChecker::CheckForUpdatesNotSilent()
{
	return CheckForUpdates(false);
}



