#include "CommonTasks.h"

#include <QProcess>
#include <QDebug>


void CommonTasks::startUpdater(const QString& program, const QStringList& args)
{
    QString p = program;

#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    p.prepend("./");
#elif defined(Q_OS_WIN)
    p.append(".exe");
#endif

    bool f =  QProcess::startDetached(p,args);

    if(f)
        qDebug() << "Running Updater...";
    else
        qDebug() << "Failed to run Updater";
}
