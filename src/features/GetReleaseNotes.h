#ifndef GETRELEASENOTES_H
#define GETRELEASENOTES_H

#include <QObject>

class UpdaterWindow;

class GetReleaseNotes : public QObject
{
        Q_OBJECT
    public:
        explicit GetReleaseNotes(UpdaterWindow *parent);



    signals:

    public slots:

    private slots:

    private:
        UpdaterWindow *d;


};

#endif // GETRELEASENOTES_H
