#include <QApplication>

#include "UpdateWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	// Prerequisite for the Fervor updater
	QApplication::setOrganizationName("speedovation");
	QApplication::setOrganizationDomain("speedovation.com");
	QApplication::setApplicationName("KineticWing IDE");
    QApplication::setApplicationVersion("1.0.0");

    if(qApp->arguments().count() != 4)
    {
        qDebug() << "Wrong arguments";
//        exit(100);
    }

      qDebug() << qApp->arguments();

	// Show main window
	UpdateWindow w;




	w.show();
	
	return a.exec();
}
