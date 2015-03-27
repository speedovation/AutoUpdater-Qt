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

#include "MessageDialogs.h"
#include "UpdaterWindow.h"

#include <QMessageBox>

/// Don't popup extra dialog
/// show inside single window itself
/// I hate popups ;)


MessageDialogs::MessageDialogs(UpdaterWindow* window) : QObject(window), d(window)
{

}

MessageDialogs::~MessageDialogs()
{

}


void MessageDialogs::showErrorDialog(QString message, bool showEvenInSilentMode)
{
	if (d->manager()->getUpdate()->m_silentAsMuchAsItCouldGet) {
		if (! showEvenInSilentMode) {
			// Don't show errors in the silent mode
			return;
		}
	}

	QMessageBox dlFailedMsgBox;
	dlFailedMsgBox.setIcon(QMessageBox::Critical);
	dlFailedMsgBox.setText(tr("Error"));
	dlFailedMsgBox.setInformativeText(message);
	dlFailedMsgBox.exec();
}

void MessageDialogs::showInformationDialog(QString message, bool showEvenInSilentMode)
{
	if (d->manager()->getUpdate()->m_silentAsMuchAsItCouldGet) {
		if (! showEvenInSilentMode) {
			// Don't show information dialogs in the silent mode
			return;
		}
	}

	QMessageBox dlInformationMsgBox;
	dlInformationMsgBox.setIcon(QMessageBox::Information);
	dlInformationMsgBox.setText(tr("Information"));
	dlInformationMsgBox.setInformativeText(message);
	dlInformationMsgBox.exec();
}
