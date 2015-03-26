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
	if (d->mam_feedURL.isEmpty()) {
		qCritical() << "Please set feed URL via setFeedURL() before calling CheckForUpdates().";
		return false;
	}

	m_silentAsMuchAsItCouldGet = silentAsMuchAsItCouldGet;

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

	cancelDownloadFeed();
	m_httpRequestAborted = false;
	startDownloadFeed(m_feedURL);

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



