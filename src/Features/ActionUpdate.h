/****************************************************************************
**
** Copyright (C) 2015 Yash Pal, Speedovation
** Copyright (C) 2012 Linas Valiukas
**
** Contact: Speedovation Lab (info@speedovation.com)
**
** KineticWing Auto Updater
** http:// kineticwing.com
** This file is part of the KiWi Editor (IDE)
**
** Author: Yash Pal, Linas Valiukas
** License : Apache License 2.0
**
** All rights are reserved.
**
**/

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
