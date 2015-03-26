#ifndef UPDATERWINDOW_H
#define UPDATERWINDOW_H

#include <QWidget>

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

    private:
        Ui::UpdaterWindow*	m_ui;
        QGraphicsScene* m_appIconScene;

};

#endif // FVUPDATEWINDOW_H


