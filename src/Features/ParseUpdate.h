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


    private:
        UpdaterWindow *d;

        QXmlStreamReader m_xml;				// XML data collector and parser
};

#endif // PARSEUPDATE_H
