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
