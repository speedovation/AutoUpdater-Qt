#ifndef SSL_H
#define SSL_H

#include <QtCore/QObject>

class Ssl : public QObject
{
        Q_OBJECT
    public:
        explicit Ssl(QObject *parent = 0);
        ~Ssl();

    signals:

    public slots:
};

#endif // SSL_H
