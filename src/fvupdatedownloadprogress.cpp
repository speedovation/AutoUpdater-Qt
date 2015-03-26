#include "fvupdatedownloadprogress.h"
#include "ui_fvupdatedownloadprogress.h"


FvUpdateDownloadProgress::FvUpdateDownloadProgress(QWidget *parent)
	: QWidget(parent, Qt::SplashScreen) ,
      	ui(new Ui::FvUpdateDownloadProgress)
{
	ui->setupUi(this);

	ui->progress->setValue(0);

}

FvUpdateDownloadProgress::~FvUpdateDownloadProgress()
{

}

void FvUpdateDownloadProgress::downloadProgress ( qint64 bytesReceived, qint64 bytesTotal )
{
	ui->progress->setValue( ((float)bytesReceived / (float)bytesTotal) * 100 );
}

void FvUpdateDownloadProgress::close()
{
	this->deleteLater();
	QWidget::close();
}
