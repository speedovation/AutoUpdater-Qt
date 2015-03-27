#ifndef PARSEUPDATE_H
#define PARSEUPDATE_H


#include <QObject>
#include <QXmlStreamReader>

#include "UpdateFileData/UpdateFileData.h"

class UpdaterWindow;



class ParseUpdate : public QObject
{
        Q_OBJECT
    public:
        ParseUpdate(   UpdaterWindow *window);
        ~ParseUpdate();

        //
        // XML parser
        //
        bool xmlParseFeed();				// Parse feed in m_xml



        UpdateFileData* getProposedUpdate();



    private:
        UpdaterWindow *d;
        friend class GetUpdate;

        QXmlStreamReader m_xml;				// XML data collector and parser


        // Available update (NULL if not fetched)
        UpdateFileData* m_proposedUpdate;


        bool searchDownloadedFeedForUpdates(QString xmlTitle,
                                            QString xmlLink,
                                            QString xmlReleaseNotesLink,
                                            QString xmlPubDate,
                                            QString xmlEnclosureUrl,
                                            QString xmlEnclosureVersion,
                                            QString xmlEnclosurePlatform,
                                            unsigned long xmlEnclosureLength,
                                            QString xmlEnclosureType);


};

#endif // PARSEUPDATE_H
