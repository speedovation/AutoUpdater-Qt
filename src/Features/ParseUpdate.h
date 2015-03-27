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
