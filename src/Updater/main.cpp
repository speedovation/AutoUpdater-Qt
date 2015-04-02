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

    qDebug() <<"Arguments: " << qApp->arguments();

    if(qApp->arguments().count() == 5)
    {
        UpdateInfo info;
        info.downloadLink = qApp->arguments().at(1);
        info.releaseLink = qApp->arguments().at(2);
        info.version = qApp->arguments().at(3);
        info.oldVersion = qApp->arguments().at(4);

       w->manager()->actionUpdate()->setUpdateInfo(info);

       w->UpdateWindowWithCurrentProposedUpdate();
    }
    else
    {
        qDebug() << "Wrong arguments";
        w->show();
        ///REMOVE below comment when in production
//        exit(100);
    }

	
	return a.exec();
}
