#ifndef PARSEUPDATE_H
#define PARSEUPDATE_H


#include <QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QXmlStreamReader;
QT_END_NAMESPACE


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
