#ifndef HELPER_H
#define HELPER_H

#include <QtWidgets/QWidget>

class UpdaterWindow;

class Helper : public QObject
{
        Q_OBJECT
    public:
        explicit Helper(UpdaterWindow *window);
        ~Helper();

        //
        // Helpers
        //
        void installTranslator();			// Initialize translation mechanism
        void restartApplication();			// Restarts application after update



    signals:

    public slots:

    private:
        UpdaterWindow *d;
};

#endif // HELPER_H
