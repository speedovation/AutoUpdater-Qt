#include "ParseUpdate.h"

#include "UpdaterWindow.h"

ParseUpdate::ParseUpdate(UpdaterWindow* window) : d(window)
{

}

ParseUpdate::~ParseUpdate()
{

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

			showErrorDialog(tr("Feed parsing failed: %1 %2.").arg(QString::number(m_xml.lineNumber()), m_xml.errorString()), false);
			return false;

		}
	}

    // No updates were found if we're at this point
    // (not a single <item> element found)
    showInformationDialog(tr("No updates were found."), false);
	return false;
}

