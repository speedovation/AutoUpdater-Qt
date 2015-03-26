#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

class UpdateChecker : public QObject
{
        Q_OBJECT
    public:
        UpdateChecker(UpdaterWindow *window);
        ~UpdateChecker();


    public slots:
        // Check for updates
        bool CheckForUpdates(bool silentAsMuchAsItCouldGet = true);

        // Aliases
        bool CheckForUpdatesSilent();
        bool CheckForUpdatesNotSilent();

    private slots:

    private:
        UpdaterWindow *d;


};

#endif // AUTHENTICATOR_H
