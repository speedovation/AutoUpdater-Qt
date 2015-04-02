#ifndef UPDATEFILEDATA_H
#define UPDATEFILEDATA_H

#include <QObject>
#include <QUrl>

class UpdateFileData : public QObject
{
        Q_OBJECT
    public:
        explicit UpdateFileData(QObject *parent = 0);

        QString getTitle();
        void setTitle(QString title);

        QUrl getReleaseNotesLink();
        void setReleaseNotesLink(QUrl releaseNotesLink);
        void setReleaseNotesLink(QString releaseNotesLink);

        QString getPubDate();
        void setPubDate(QString pubDate);

        QUrl getEnclosureUrl();
        void setEnclosureUrl(QUrl enclosureUrl);
        void setEnclosureUrl(QString enclosureUrl);

        QString getEnclosureVersion();
        void setEnclosureVersion(QString enclosureVersion);

        QString getEnclosurePlatform();
        void setEnclosurePlatform(QString enclosurePlatform);

        unsigned long getEnclosureLength();
        void setEnclosureLength(unsigned long enclosureLength);

        QString getEnclosureType();
        void setEnclosureType(QString enclosureType);

    private:
        QString m_title;
        QUrl m_releaseNotesLink;
        QString m_pubDate;
        QUrl m_enclosureUrl;
        QString m_enclosureVersion;
        QString m_enclosurePlatform;
        unsigned long m_enclosureLength;
        QString m_enclosureType;

};

#endif // FVAVAILABLEUPDATE_H
