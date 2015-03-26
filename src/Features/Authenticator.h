#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>

class UpdaterWindow;

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QAuthenticator;
QT_END_NAMESPACE

class Authenticator : public QObject
{
        Q_OBJECT
    public:
        Authenticator();
        ~Authenticator();

        // HTTP Authentuication - for security reasons no getters are provided, only a setter
        void setHtAuthCredentials(QString user, QString pass);
        void setHtAuthUsername(QString user);
        void setHtAuthPassword(QString pass);


    private slots:
        void authenticationRequired ( QNetworkReply * reply, QAuthenticator * authenticator );

    private:
        //
        // Htauth-Infrastructure
        //
        QString htAuthUsername;
        QString htAuthPassword;

};

#endif // AUTHENTICATOR_H
