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

#ifndef GETUPDATE_H
#define GETUPDATE_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>


class UpdaterWindow;
class UpdateDownloadProgress;

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QAuthenticator;
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
        void setFeedURL(QUrl feedURL);
        void setFeedURL(QString feedURL);
        QString getFeedURL();

        void setSkipVersionAllowed(bool allowed);
        void setRemindLaterAllowed(bool allowed);
        bool getSkipVersionAllowed();
        bool getRemindLaterAllowed();





    public slots:
        void httpFeedReadyRead();
        void httpFeedUpdateDataReadProgress(qint64 bytesRead,
                                            qint64 totalBytes);
        void httpFeedDownloadFinished();





    private:
        UpdaterWindow *d;
        friend class UpdateChecker;
        friend class MessageDialogs;

        // Dialogs (notifications)
        bool skipVersionAllowed;
        bool remindLaterAllowed;

        // If true, don't show the error dialogs and the "no updates." dialog
        // (silentAsMuchAsItCouldGet from CheckForUpdates() goes here)
        // Useful for automatic update checking upon application startup.
        bool m_silentAsMuchAsItCouldGet;







        UpdateDownloadProgress* dlwindow;



};


#endif // GETUPDATE_H
