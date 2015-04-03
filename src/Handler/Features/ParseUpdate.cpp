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


#include "ParseUpdate.h"

#include <QProcess>
#include <QApplication>

//#include "UpdaterWindow.h"
#include "HandlerManager.h"
#include "../Common/UpdateFileData.h"
#include "../Common/Platform.h"
#include "../Common/IgnoredVersions.h"
#include "../Common/CommonTasks.h"

ParseUpdate::ParseUpdate(HandlerManager* window) : d(window)
{
    m_proposedUpdate = 0;
}

ParseUpdate::~ParseUpdate()
{
    if (m_proposedUpdate) {
		delete m_proposedUpdate;
		m_proposedUpdate = 0;
	}
}


bool ParseUpdate::xmlParseFeed()
{
	QString currentTag, currentQualifiedTag;

	QString xmlTitle, xmlLink, xmlReleaseNotesLink, xmlPubDate, xmlEnclosureUrl,
			xmlEnclosureVersion, xmlEnclosurePlatform, xmlEnclosureType;
	unsigned long xmlEnclosureLength = 0;

	// Parse
	while (! m_xml.atEnd()) {

		m_xml.readNext();

		if (m_xml.isStartElement()) {

			currentTag = m_xml.name().toString();
			currentQualifiedTag = m_xml.qualifiedName().toString();

			if (m_xml.name() == "item") {

				xmlTitle.clear();
				xmlLink.clear();
				xmlReleaseNotesLink.clear();
				xmlPubDate.clear();
				xmlEnclosureUrl.clear();
				xmlEnclosureVersion.clear();
				xmlEnclosurePlatform.clear();
				xmlEnclosureLength = 0;
				xmlEnclosureType.clear();

			} else if (m_xml.name() == "enclosure") {

				QXmlStreamAttributes attribs = m_xml.attributes();

				if (attribs.hasAttribute("fervor:platform"))
				{
					xmlEnclosurePlatform = attribs.value("fervor:platform").toString().trimmed();

					if (Platform::isCurrentOsSupported(xmlEnclosurePlatform))
					{
						xmlEnclosureUrl = attribs.hasAttribute("url") ? attribs.value("url").toString().trimmed() : "";

						xmlEnclosureVersion = "";
						if (attribs.hasAttribute("fervor:version"))
							xmlEnclosureVersion = attribs.value("fervor:version").toString().trimmed();
						if (attribs.hasAttribute("sparkle:version"))
							xmlEnclosureVersion = attribs.value("sparkle:version").toString().trimmed();

						xmlEnclosureLength = attribs.hasAttribute("length") ? attribs.value("length").toString().toLong() : 0;

						xmlEnclosureType = attribs.hasAttribute("type") ? attribs.value("type").toString().trimmed() : "";
					}

				}	// if hasAttribute flevor:platform END

			}	// IF encosure END

		} else if (m_xml.isEndElement()) {

			if (m_xml.name() == "item") {

				// That's it - we have analyzed a single <item> and we'll stop
				// here (because the topmost is the most recent one, and thus
				// the newest version.

				return searchDownloadedFeedForUpdates(xmlTitle,
													  xmlLink,
													  xmlReleaseNotesLink,
													  xmlPubDate,
													  xmlEnclosureUrl,
													  xmlEnclosureVersion,
													  xmlEnclosurePlatform,
													  xmlEnclosureLength,
													  xmlEnclosureType);

			}

		} else if (m_xml.isCharacters() && ! m_xml.isWhitespace()) {

			if (currentTag == "title") {
				xmlTitle += m_xml.text().toString().trimmed();

			} else if (currentTag == "link") {
				xmlLink += m_xml.text().toString().trimmed();

			} else if (currentQualifiedTag == "sparkle:releaseNotesLink") {
				xmlReleaseNotesLink += m_xml.text().toString().trimmed();

			} else if (currentTag == "pubDate") {
				xmlPubDate += m_xml.text().toString().trimmed();

			}

		}

		if (m_xml.error() && m_xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {

            ///SHOW message in app style
			///d->messageDialogs()->showErrorDialog(tr("Feed parsing failed: %1 %2.").arg(QString::number(m_xml.lineNumber()), m_xml.errorString()), false);
			return false;

		}
	}

    // No updates were found if we're at this point
    // (not a single <item> element found)
    ///show error in app style
    ///d->messageDialogs()->showInformationDialog(tr("No updates were found."), false);
	return false;
}


bool ParseUpdate::searchDownloadedFeedForUpdates(QString xmlTitle,
											   QString xmlLink,
											   QString xmlReleaseNotesLink,
											   QString xmlPubDate,
											   QString xmlEnclosureUrl,
											   QString xmlEnclosureVersion,
											   QString xmlEnclosurePlatform,
											   unsigned long xmlEnclosureLength,
											   QString xmlEnclosureType)
{
    qDebug() << "Title:" << xmlTitle;
    qDebug() << "Link:" << xmlLink;
    qDebug() << "Release notes link:" << xmlReleaseNotesLink;
    qDebug() << "Pub. date:" << xmlPubDate;
    qDebug() << "Enclosure URL:" << xmlEnclosureUrl;
    qDebug() << "Enclosure version:" << xmlEnclosureVersion;
    qDebug() << "Enclosure platform:" << xmlEnclosurePlatform;
    qDebug() << "Enclosure length:" << xmlEnclosureLength;
    qDebug() << "Enclosure type:" << xmlEnclosureType;

	// Validate
	if (xmlReleaseNotesLink.isEmpty()) {
		if (xmlLink.isEmpty()) {

            ///d->messageDialogs()->showErrorDialog(tr("Feed error: \"release notes\" link is empty"), false);

            return false;
		} else {
			xmlReleaseNotesLink = xmlLink;
		}
	} else {
		xmlLink = xmlReleaseNotesLink;
	}
	if (! (xmlLink.startsWith("http://") || xmlLink.startsWith("https://"))) {

        ///d->messageDialogs()->showErrorDialog(tr("Feed error: invalid \"release notes\" link"), false);

        return false;
	}
	if (xmlEnclosureUrl.isEmpty() || xmlEnclosureVersion.isEmpty() || xmlEnclosurePlatform.isEmpty()) {

        ///d->messageDialogs()->showErrorDialog(tr("Feed error: invalid \"enclosure\" with the download link"), false);

        return false;
	}

	// Relevant version?
	if (IgnoredVersions::isVersionIgnored(xmlEnclosureVersion)) {
		qDebug() << "Version '" << xmlEnclosureVersion << "' is ignored, too old or something like that.";

		///d->messageDialogs()->showInformationDialog(tr("No updates were found."), false);

		return true;	// Things have succeeded when you think of it.
	}


	//
	// Success! At this point, we have found an update that can be proposed
	// to the user.
	//

	if (m_proposedUpdate) {
		delete m_proposedUpdate; m_proposedUpdate = 0;
	}
	m_proposedUpdate = new UpdateFileData();
	m_proposedUpdate->setTitle(xmlTitle);
	m_proposedUpdate->setReleaseNotesLink(xmlReleaseNotesLink);
	m_proposedUpdate->setPubDate(xmlPubDate);
	m_proposedUpdate->setEnclosureUrl(xmlEnclosureUrl);
	m_proposedUpdate->setEnclosureVersion(xmlEnclosureVersion);
	m_proposedUpdate->setEnclosurePlatform(xmlEnclosurePlatform);
	m_proposedUpdate->setEnclosureLength(xmlEnclosureLength);
	m_proposedUpdate->setEnclosureType(xmlEnclosureType);

	// Show "look, there's an update" window
	/// d->UpdateWindowWithCurrentProposedUpdate();
	// Decide ourselves what to do
//	decideWhatToDoWithCurrentUpdateProposal();
//#endif
//    if (d->getUpdate()->m_silentAsMuchAsItCouldGet) {
//			// Don't show errors in the silent mode
//			return;
//		///Fixme here
//	}

    qDebug() << "Update found";


  CommonTasks::startUpdater("AutoUpdater",
                            QStringList()
                            << xmlEnclosureUrl
                            << xmlReleaseNotesLink
                            << xmlEnclosureVersion
                            << qApp->applicationVersion()
                            );


	return true;
}





