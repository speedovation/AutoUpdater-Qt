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

    if(qApp->arguments().count() != 5)
    {
        qDebug() << "Wrong arguments";
        exit(100);
    }

      qDebug() << qApp->arguments();

     UpdateInfo info;
     info.downloadLink = qApp->arguments().at(1);
     info.releaseLink = qApp->arguments().at(2);
     info.version = qApp->arguments().at(3);
     info.oldVersion = qApp->arguments().at(4);

	// Show main window
	UpdaterWindow w;

    w.manager()->actionUpdate()->setUpdateInfo(info);


	w.UpdateWindowWithCurrentProposedUpdate();
	
	return a.exec();
}
