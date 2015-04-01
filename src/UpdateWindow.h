#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include <QtGui/QMainWindow>

namespace Ui {
    class UpdateWindow;
}

class UpdateWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit UpdateWindow(QWidget *parent = 0);
        ~UpdateWindow();

    protected:
        void changeEvent(QEvent *e);

    private:
        Ui::UpdateWindow *ui;
};

#endif // UPDATEWINDOW_H
