#ifndef ACTIONUPDATE_H
#define ACTIONUPDATE_H

#include <QtWidgets/QWidget>
#include <QNetworkAccessManager>

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

    private slots:
        	void httpUpdateDownloadFinished();

    signals:
        void updatedFinishedSuccessfully();

    private:
        UpdaterWindow *d;
        void decideWhatToDoWithCurrentUpdateProposal();                 // Perform an action which is configured in settings

        QNetworkAccessManager m_qnam;


};

#endif // ACTIONUPDATE_H
