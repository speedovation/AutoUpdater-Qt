#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <QObject>

class UpdaterWindow;
class GetReleaseNotes;
class Authenticator;
class UpdateChecker;
class ParseUpdate;
class GetUpdate;



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

};

#endif // BASEMANAGER_H
