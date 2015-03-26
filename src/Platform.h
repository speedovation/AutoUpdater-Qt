#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>

class Platform : public QObject
{
	Q_OBJECT

public:
	static bool isCurrentOsSupported(QString platform);

private:
	explicit Platform(QObject *parent = 0);
		
};

#endif // FVPLATFORM_H
