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

#ifndef UPDATERWINDOW_H
#define UPDATERWINDOW_H

#include <QMainWindow>

#include "Features/BaseManager.h"
#include "Partials/UpdateDownloadProgress.h"

class QGraphicsScene;


namespace Ui {
    class UpdaterWindow;
}

class UpdaterWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit UpdaterWindow(QWidget *parent = 0, bool skipVersionAllowed = true, bool remindLaterAllowed = true);
        ~UpdaterWindow();

        // Update the current update proposal from FvUpdater
        bool UpdateWindowWithCurrentProposedUpdate();

        void closeEvent(QCloseEvent* event);

        BaseManager* manager();
        UpdateDownloadProgress* updateDownloadProgress();

        void showProgress(bool show);

    private:
        Ui::UpdaterWindow*	ui;
//        QGraphicsScene* m_appIconScene;

        BaseManager *_baseManager;

};

#endif // FVUPDATEWINDOW_H


