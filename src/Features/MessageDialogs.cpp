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
