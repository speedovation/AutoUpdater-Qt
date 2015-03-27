#ifndef PARSEUPDATE_H
#define PARSEUPDATE_H


#include <QObject>

class UpdaterWindow;

#include <QXmlStreamReader>


class ParseUpdate : public QObject
{
    public:
        ParseUpdate(   UpdaterWindow *window);
        ~ParseUpdate();

        //
        // XML parser
        //
        bool xmlParseFeed();				// Parse feed in m_xml


        bool searchDownloadedFeedForUpdates(QString xmlTitle,
                                            QString xmlLink,
                                            QString xmlReleaseNotesLink,
                                            QString xmlPubDate,
                                            QString xmlEnclosureUrl,
                                            QString xmlEnclosureVersion,
                                            QString xmlEnclosurePlatform,
                                            unsigned long xmlEnclosureLength,
                                            QString xmlEnclosureType);



    private:
        UpdaterWindow *d;
        friend class GetUpdate;

        QXmlStreamReader m_xml;				// XML data collector and parser
};

#endif // PARSEUPDATE_H
