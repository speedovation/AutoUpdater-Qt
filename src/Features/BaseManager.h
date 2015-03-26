#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <QObject>

class UpdaterWindow;
class GetReleaseNotes;


class BaseManager : public QObject
{
        Q_OBJECT
    public:
        explicit BaseManager(UpdaterWindow *window);

        GetReleaseNotes* getReleaseNotes();


    signals:

    public slots:

    private:
        friend class BaseWindow;
        UpdaterWindow *d;

        GetReleaseNotes* _getReleaseNotes;

};

#endif // BASEMANAGER_H
