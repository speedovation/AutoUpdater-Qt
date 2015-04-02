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

#include "IgnoredVersions.h"
#include "VersionComparator.h"
#include <QSettings>
#include <QCoreApplication>
#include <string>

// QSettings key for the latest skipped version
#define FV_IGNORED_VERSIONS_LATEST_SKIPPED_VERSION_KEY	"FVLatestSkippedVersion"


IgnoredVersions::IgnoredVersions(QObject *parent) :
QObject(parent)
{
	// noop
}

bool IgnoredVersions::isVersionIgnored(QString version)
{
	// We assume that variable 'version' contains either:
	//	1) The current version of the application (ignore)
	//	2) The version that was skipped before and thus stored in QSettings (ignore)
	//	3) A newer version (don't ignore)
	// 'version' is not likely to contain an older version in any case.
    
	if (version == QCoreApplication::applicationVersion()) {
		return true;
	}
    
    QSettings settings(QSettings::NativeFormat,
					   QSettings::UserScope,
					   QCoreApplication::organizationDomain(),
					   QCoreApplication::applicationName());
    
	//QSettings settings;
	if (settings.contains(FV_IGNORED_VERSIONS_LATEST_SKIPPED_VERSION_KEY)) {
		QString lastSkippedVersion = settings.value(FV_IGNORED_VERSIONS_LATEST_SKIPPED_VERSION_KEY).toString();
		if (version == lastSkippedVersion) {
			// Implicitly skipped version - skip
			return true;
		}
	}
    
	std::string currentAppVersion = QCoreApplication::applicationVersion().toStdString();
	std::string suggestedVersion = std::string(version.toStdString());
	if (VersionComparator::CompareVersions(currentAppVersion, suggestedVersion) == VersionComparator::kAscending) {
		// Newer version - do not skip
		return false;
	}
    
	// Fallback - skip
	return true;
}

void IgnoredVersions::setVersionIgnored(QString version)
{
	if (version == QCoreApplication::applicationVersion()) {
		// Don't ignore the current version
		return;
	}
    
	if (version.isEmpty()) {
		return;
	}
    
    QSettings settings(QSettings::NativeFormat,
					   QSettings::UserScope,
					   QCoreApplication::organizationDomain(),
					   QCoreApplication::applicationName());
    

	settings.setValue(FV_IGNORED_VERSIONS_LATEST_SKIPPED_VERSION_KEY, version);
    
	return;
}
