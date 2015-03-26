#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <QObject>

//class UpdaterWindow;
//class GetReleaseNotes;
//class Authenticator;
//class UpdateChecker;
//class ParseUpdate;
//class GetUpdate;


#include "GetReleaseNotes.h"
#include "GetUpdate.h"
#include "ParseUpdate.h"
#include "UpdateChecker.h"
#include "Authenticator.h"
#include "MessageDialogs.h"
#include "Zip.h"


class BaseManager : public QObject
{
        Q_OBJECT
    public:
        explicit BaseManager(UpdaterWindow *window);

        GetReleaseNotes* getReleaseNotes();
        Authenticator* authenticator();
        UpdateChecker* updateChecker();
        ParseUpdate* parseUpdate();
        GetUpdate* getUpdate();
        MessageDialogs* messageDialogs();
        Zip* zip();



    signals:

    public slots:

    private:
        friend class BaseWindow;
        UpdaterWindow *d;

        GetReleaseNotes* _getReleaseNotes;
        Authenticator* _authenticator;
        UpdateChecker* _updateChecker;
        ParseUpdate* _parseUpdate;
        GetUpdate* _getUpdate;
        MessageDialogs* _messageDialogs;
        Zip* _zip;

};

#endif // BASEMANAGER_H
