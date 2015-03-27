#ifndef TESTS_H
#define TESTS_H

#include <QtWidgets/QWidget>

class Tests : public QWidget
{
        Q_OBJECT
    public:
        explicit Tests(QWidget *parent = 0);
        ~Tests();

    signals:

    public slots:
};

#endif // TESTS_H
