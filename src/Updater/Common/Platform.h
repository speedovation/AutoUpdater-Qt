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

#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class Platform : public QObject
{
	Q_OBJECT

public:
	static bool isCurrentOsSupported(QString platform);

private:
	explicit Platform(QObject *parent = 0);
		
};

#endif // FVPLATFORM_H
