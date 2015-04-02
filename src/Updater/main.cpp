#include <QApplication>

#include "UpdaterWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	// Prerequisite for the Fervor updater
	QApplication::setOrganizationName("speedovation");
	QApplication::setOrganizationDomain("speedovation.com");
	QApplication::setApplicationName("KineticWing IDE");
    QApplication::setApplicationVersion("1.0.0");

    // Show main window
	UpdaterWindow *w = new UpdaterWindow;

    w->manager()->mode()->handler(qApp->arguments());

	
	return a.exec();
}
