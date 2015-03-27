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


#ifndef HELPER_H
#define HELPER_H

#include <QtWidgets/QWidget>

class UpdaterWindow;

class Helper : public QObject
{
        Q_OBJECT
    public:
        explicit Helper(UpdaterWindow *window);
        ~Helper();

        //
        // Helpers
        //
        void installTranslator();			// Initialize translation mechanism
        void restartApplication();			// Restarts application after update



    signals:

    public slots:

    private:
        UpdaterWindow *d;
};

#endif // HELPER_H
