#include "Helper.h"

#include <QProcess>
#include <QTranslator>
#include <QApplication>

#include "UpdaterWindow.h"

Helper::Helper(UpdaterWindow* window) : d(window)
{
    installTranslator();
}

Helper::~Helper()
{

}

void Helper::restartApplication()
{
    // Spawn a new instance of myApplication:
    QString app = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString wd = QDir::currentPath();
    qDebug() << app << arguments << wd;
    QProcess::startDetached(app, arguments, wd);
    QApplication::exit();
}
void Helper::installTranslator()
{
    QTranslator translator;
    QString locale = QLocale::system().name();
    translator.load(QString("fervor_") + locale);

    qApp->installTranslator(&translator);
}

