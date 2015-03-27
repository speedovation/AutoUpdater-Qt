#include "MessageDialogs.h"
#include "UpdaterWindow.h"

#include <QMessageBox>

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

#ifdef FV_GUI
	QMessageBox dlFailedMsgBox;
	dlFailedMsgBox.setIcon(QMessageBox::Critical);
	dlFailedMsgBox.setText(tr("Error"));
	dlFailedMsgBox.setInformativeText(message);
	dlFailedMsgBox.exec();
#else
	qCritical() << message;
#endif
}

void MessageDialogs::showInformationDialog(QString message, bool showEvenInSilentMode)
{
	if (d->manager()->getUpdate()->m_silentAsMuchAsItCouldGet) {
		if (! showEvenInSilentMode) {
			// Don't show information dialogs in the silent mode
			return;
		}
	}

#ifdef FV_GUI
	QMessageBox dlInformationMsgBox;
	dlInformationMsgBox.setIcon(QMessageBox::Information);
	dlInformationMsgBox.setText(tr("Information"));
	dlInformationMsgBox.setInformativeText(message);
	dlInformationMsgBox.exec();
#else
	qDebug() << message;
#endif
}
