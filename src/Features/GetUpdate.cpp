#include "GetUpdate.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

GetUpdate::GetUpdate(UpdaterWindow *window) : d(window)
{

}

GetUpdate::~GetUpdate()
{

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
		showErrorDialog(tr("Feed download failed: %1.").arg(m_reply->errorString()), false);

	} else if (! redirectionTarget.isNull()) {
		QUrl newUrl = m_feedURL.resolved(redirectionTarget.toUrl());

		m_feedURL = newUrl;
		m_reply->deleteLater();

		startDownloadFeed(m_feedURL);
		return;

	} else {

		// Done.
		xmlParseFeed();

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

