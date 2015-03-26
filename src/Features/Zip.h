#ifndef ZIP_H
#define ZIP_H

#include <QtCore/QObject>

class UpdaterWindow;

class Zip : public QObject
{
        Q_OBJECT
    public:
        Zip( UpdaterWindow *window);
        ~Zip();


        //
        // Download and install Update infrastructure
        //

        bool unzipUpdate(const QString & filePath, const QString & extDirPath, const QString & singleFileName = QString(""));	// returns true on success

    private:
        UpdaterWindow *d;

};

#endif // ZIP_H
