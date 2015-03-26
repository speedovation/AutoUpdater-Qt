#ifndef GETUPDATE_H
#define GETUPDATE_H

#include <QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QAuthenticator;
class QNetworkAccessManager;
QT_END_NAMESPACE

class GetUpdate : public QObject
{
        Q_OBJECT

    public:
        GetUpdate(UpdaterWindow *window);
        ~GetUpdate();

        //
        // HTTP feed fetcher infrastructure
        //
        QUrl m_feedURL;					// Feed URL that will be fetched
        QNetworkAccessManager m_qnam;
        QNetworkReply* m_reply;
        int m_httpGetId;
        bool m_httpRequestAborted;

        void startDownloadFeed(QUrl url);	// Start downloading feed
        void cancelDownloadFeed();			// Stop downloading the current feed

        // Set / get feed URL
        void SetFeedURL(QUrl feedURL);
        void SetFeedURL(QString feedURL);
        QString GetFeedURL();

        void setSkipVersionAllowed(bool allowed);
        void setRemindLaterAllowed(bool allowed);
        bool getSkipVersionAllowed();
        bool getRemindLaterAllowed();

    public slots:
        void httpFeedReadyRead();
        void httpFeedUpdateDataReadProgress(qint64 bytesRead,
                                            qint64 totalBytes);
        void httpFeedDownloadFinished();

    private slots:

    private:
        UpdaterWindow *d;

        // Dialogs (notifications)
        bool skipVersionAllowed;
        bool remindLaterAllowed;


};


#endif // GETUPDATE_H
