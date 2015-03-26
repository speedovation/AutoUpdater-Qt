#ifndef MESSAGEDIALOGS_H
#define MESSAGEDIALOGS_H

#include <QtCore/QObject>


class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QXmlStreamReader;
QT_END_NAMESPACE


class MessageDialogs
{
    public:
        MessageDialogs(UpdaterWindow *window);
        ~MessageDialogs();


        void showErrorDialog(QString message, bool showEvenInSilentMode = false);			// Show an error message
        void showInformationDialog(QString message, bool showEvenInSilentMode = false);		// Show an informational message




    private:
        UpdaterWindow *d;
};

#endif // MESSAGEDIALOGS_H
