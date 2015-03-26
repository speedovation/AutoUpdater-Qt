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

    private:
        Ui::UpdaterWindow*	m_ui;
        QGraphicsScene* m_appIconScene;

        BaseManager *_baseManager;

};

#endif // FVUPDATEWINDOW_H


