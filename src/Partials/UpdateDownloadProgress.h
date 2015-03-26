#ifndef UPDATEDOWNLOADPROGRESS_H
#define UPDATEDOWNLOADPROGRESS_H

#include <QWidget>


namespace Ui {
    class UpdateDownloadProgress;
}

class UpdateDownloadProgress : public QWidget
{
        Q_OBJECT

    public:
        UpdateDownloadProgress(QWidget *parent = 0);
        ~UpdateDownloadProgress();

    public slots:
        void downloadProgress ( qint64 bytesReceived, qint64 bytesTotal );
        void close();

    private:
        Ui::UpdateDownloadProgress* ui;
};

#endif // FVUPDATEDOWNLOADPROGRESS_H
