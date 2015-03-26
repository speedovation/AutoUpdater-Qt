#include "GetUpdate.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include "UpdaterWindow.h"
#include "Partials/UpdateDownloadProgress.h"
#include "UpdateFileData/UpdateFileData.h"

GetUpdate::GetUpdate(UpdaterWindow *window) : d(window)
{
    skipVersionAllowed = true;
	remindLaterAllowed = true;
    m_reply = 0;
    	m_proposedUpdate = 0;
}

GetUpdate::~GetUpdate()
{
    if (m_proposedUpdate) {
		delete m_proposedUpdate;
		m_proposedUpdate = 0;
	}

}

void GetUpdate::startDownloadFeed(QUrl url)
{
	m_xml.clear();

	// Check SSL Fingerprint if required
	if(url.scheme()=="https" && !m_requiredSslFingerprint.isEmpty())
		if( !checkSslFingerPrint(url) )	// check failed
		{
			qWarning() << "Update aborted.";
			return;
		}


	m_reply = m_qnam.get(QNetworkRequest(url));

	connect(m_reply, SIGNAL(readyRead()), this, SLOT(httpFeedReadyRead()));
	connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(httpFeedUpdateDataReadProgress(qint64, qint64)));
	connect(m_reply, SIGNAL(finished()), this, SLOT(httpFeedDownloadFinished()));
}

void GetUpdate::cancelDownloadFeed()
{
	if (m_reply) {
		m_httpRequestAborted = true;
		m_reply->abort();
	}
}


void GetUpdate::httpFeedReadyRead()
{
	// this slot gets called every time the QNetworkReply has new data.
	// We read all of its new data and write it into the file.
	// That way we use less RAM than when reading it at the finished()
	// signal of the QNetworkReply
	m_xml.addData(m_reply->readAll());
}

void GetUpdate::httpFeedUpdateDataReadProgress(qint64 bytesRead,
											   qint64 totalBytes)
{
	Q_UNUSED(bytesRead);
	Q_UNUSED(totalBytes);

	if (m_httpRequestAborted) {
		return;
	}
}

void GetUpdate::httpFeedDownloadFinished()
{
	if (m_httpRequestAborted) {
		m_reply->deleteLater();
		return;
	}

	QVariant redirectionTarget = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	if (m_reply->error()) {

		// Error.
		///showErrorDialog(tr("Feed download failed: %1.").arg(m_reply->errorString()), false);

	} else if (! redirectionTarget.isNull()) {
		QUrl newUrl = m_feedURL.resolved(redirectionTarget.toUrl());

		m_feedURL = newUrl;
		m_reply->deleteLater();

		startDownloadFeed(m_feedURL);
		return;

	} else {

		// Done.
		d->manager()->parseUpdate()->xmlParseFeed();

	}

	m_reply->deleteLater();
	m_reply = 0;
}

void GetUpdate::SetFeedURL(QUrl feedURL)
{
	m_feedURL = feedURL;
}

void GetUpdate::SetFeedURL(QString feedURL)
{
	SetFeedURL(QUrl(feedURL));
}

QString GetUpdate::GetFeedURL()
{
	return m_feedURL.toString();
}



void GetUpdate::setSkipVersionAllowed(bool allowed)
{
	skipVersionAllowed = allowed;
}

void GetUpdate::setRemindLaterAllowed(bool allowed)
{
	remindLaterAllowed = allowed;
}

bool GetUpdate::getSkipVersionAllowed()
{
	return skipVersionAllowed;
}

bool GetUpdate::getRemindLaterAllowed()
{
	return remindLaterAllowed;
}




UpdateFileData* GetUpdate::GetProposedUpdate()
{
	return m_proposedUpdate;
}


void GetUpdate::InstallUpdate()
{
	qDebug() << "Install update";
	if(m_proposedUpdate==NULL)
	{
		qWarning() << "Abort Update: No update prososed! This should not happen.";
		return;
	}

	//showUpdateConfirmationDialogUpdatedWithCurrentUpdateProposal();
	// Prepare download
	QUrl url = m_proposedUpdate->getEnclosureUrl();

	// Check SSL Fingerprint if required
	if(url.scheme()=="https" && !m_requiredSslFingerprint.isEmpty())
		if( !checkSslFingerPrint(url) )	// check failed
		{
			qWarning() << "Update aborted.";
			return;
		}

    ///remove below
    QNetworkAccessManager m_qnam;

	// Start Download
	QNetworkReply* reply = m_qnam.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()), this, SLOT(httpUpdateDownloadFinished()));

	// Maybe Check request 's return value
	if (reply->error() != QNetworkReply::NoError)
	{
		qDebug()<<"Unable to download the update: "<<reply->errorString();
		return;
	}
	else
		qDebug()<<"OK";

	// Show download Window
#ifdef FV_GUI
	dlwindow = new UpdateDownloadProgress;
	connect(reply, SIGNAL(downloadProgress(qint64, qint64)), dlwindow, SLOT(downloadProgress(qint64, qint64) ));
	connect(&m_qnam, SIGNAL(finished(QNetworkReply*)), dlwindow, SLOT(close()));
	//dlwindow->show();
#endif
	emit (updatedFinishedSuccessfully());


#ifdef FV_GUI
	hideUpdaterWindow();
#endif
}


bool GetUpdate::searchDownloadedFeedForUpdates(QString xmlTitle,
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
			d->manager()->messageDialogs()->showErrorDialog(tr("Feed error: \"release notes\" link is empty"), false);
			return false;
		} else {
			xmlReleaseNotesLink = xmlLink;
		}
	} else {
		xmlLink = xmlReleaseNotesLink;
	}
	if (! (xmlLink.startsWith("http://") || xmlLink.startsWith("https://"))) {
		d->manager()->messageDialogs()->showErrorDialog(tr("Feed error: invalid \"release notes\" link"), false);
		return false;
	}
	if (xmlEnclosureUrl.isEmpty() || xmlEnclosureVersion.isEmpty() || xmlEnclosurePlatform.isEmpty()) {
		d->manager()->messageDialogs()->showErrorDialog(tr("Feed error: invalid \"enclosure\" with the download link"), false);
		return false;
	}

	// Relevant version?
	if (FVIgnoredVersions::isVersionIgnored(xmlEnclosureVersion)) {
		qDebug() << "Version '" << xmlEnclosureVersion << "' is ignored, too old or something like that.";

		d->manager()->messageDialogs()->showInformationDialog(tr("No updates were found."), false);

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

#ifdef FV_GUI
	// Show "look, there's an update" window
	showUpdaterWindowUpdatedWithCurrentUpdateProposal();
#else
	// Decide ourselves what to do
	decideWhatToDoWithCurrentUpdateProposal();
#endif

	return true;
}

