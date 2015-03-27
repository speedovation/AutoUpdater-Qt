#ifndef SSL_H
#define SSL_H

#include <QtCore/QObject>

class UpdaterWindow;

class Ssl : public QObject
{
        Q_OBJECT
    public:
        Ssl(UpdaterWindow *window);
        ~Ssl();

        void setRequiredSslFingerPrint(QString md5);
        QString getRequiredSslFingerPrint();	// returns md5!


    signals:

    public slots:

    private:
        UpdaterWindow *d;
        friend class GetUpdate;

        //
        // SSL Fingerprint Check infrastructure
        //
        QString m_requiredSslFingerprint;

        bool checkSslFingerPrint(QUrl urltoCheck);	// true=ssl Fingerprint accepted, false= ssl Fingerprint NOT accepted


};

#endif // SSL_H
