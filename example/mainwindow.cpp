#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fvupdater.h"
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    w = new UpdaterWindow(0 , true, true) ;

    w->manager()->getUpdate()->setFeedURL("http://kiwi.po/update.xml");

	// Connect the "check for updates manually" button with the autoupdater
	connect(ui->updateButton, SIGNAL(clicked()),
			w->manager()->updateChecker(), SLOT(CheckForUpdatesNotSilent() ));




	ui->label->setText( tr("Version %1").arg(QApplication::applicationVersion()) );
}

MainWindow::~MainWindow()
{
	delete ui;
}
