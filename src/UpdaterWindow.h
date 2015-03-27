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

#include <QWidget>

#include "Features/BaseManager.h"

class QGraphicsScene;


namespace Ui {
    class UpdaterWindow;
}

class UpdaterWindow : public QWidget
{
        Q_OBJECT

    public:
        explicit UpdaterWindow(QWidget *parent, bool skipVersionAllowed, bool remindLaterAllowed);
        ~UpdaterWindow();

        // Update the current update proposal from FvUpdater
        bool UpdateWindowWithCurrentProposedUpdate();

        void closeEvent(QCloseEvent* event);

        BaseManager* manager();
        UpdateDownloadProgress* updateDownloadProgress();

    private:
        Ui::UpdaterWindow*	m_ui;
        QGraphicsScene* m_appIconScene;

        BaseManager *_baseManager;

};

#endif // FVUPDATEWINDOW_H


