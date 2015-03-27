#ifndef ACTIONUPDATE_H
#define ACTIONUPDATE_H

#include <QtWidgets/QWidget>

class UpdaterWindow;

class ActionUpdate : public QObject
{
        Q_OBJECT
    public:
        explicit ActionUpdate(UpdaterWindow *window);
        ~ActionUpdate();

        void finishUpdate(QString pathToFinish = "");

    public slots:
        // Update window button slots

        void SkipUpdate();
        void RemindMeLater();
        void InstallUpdate();


        // Update confirmation dialog button slots
        void UpdateInstallationConfirmed();

    signals:
        void updatedFinishedSuccessfully();

    private:
        UpdaterWindow *d;
        void decideWhatToDoWithCurrentUpdateProposal();                 // Perform an action which is configured in settings

};

#endif // ACTIONUPDATE_H
