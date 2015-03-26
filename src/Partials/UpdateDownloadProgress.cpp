#include "UpdateDownloadProgress.h"
#include "ui_UpdateDownloadProgress.h"


UpdateDownloadProgress::UpdateDownloadProgress(QWidget *parent)
	: QWidget(parent) ,
      	ui(new Ui::UpdateDownloadProgress)
{
	ui->setupUi(this);

	ui->progress->setValue(0);

}

UpdateDownloadProgress::~UpdateDownloadProgress()
{

}

void UpdateDownloadProgress::downloadProgress ( qint64 bytesReceived, qint64 bytesTotal )
{
	ui->progress->setValue( ((float)bytesReceived / (float)bytesTotal) * 100 );
}

void UpdateDownloadProgress::close()
{
	this->deleteLater();
	QWidget::close();
}
