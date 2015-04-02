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

#include "../Common/UpdateFileData.h"

class HandlerManager;



class ParseUpdate : public QObject
{
        Q_OBJECT
    public:
        ParseUpdate(   HandlerManager *window);
        ~ParseUpdate();

        //
        // XML parser
        //
        bool xmlParseFeed();				// Parse feed in m_xml



        UpdateFileData* getProposedUpdate();

        QXmlStreamReader m_xml;				// XML data collector and parser


    private:
        HandlerManager *d;
//        friend class GetUpdate;

        void startUpdater(const QString& program, const QStringList& args);

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
