#include "UpdateFileData.h"

UpdateFileData::UpdateFileData(QObject *parent) :
    QObject(parent)
{
    // noop
}

QString UpdateFileData::getTitle()
{
    return m_title;
}

void UpdateFileData::setTitle(QString title)
{
    m_title = title;
}

QUrl UpdateFileData::getReleaseNotesLink()
{
    return m_releaseNotesLink;
}

void UpdateFileData::setReleaseNotesLink(QUrl releaseNotesLink)
{
    m_releaseNotesLink = releaseNotesLink;
}

void UpdateFileData::setReleaseNotesLink(QString releaseNotesLink)
{
    setReleaseNotesLink(QUrl(releaseNotesLink));
}

QString UpdateFileData::getPubDate()
{
    return m_pubDate;
}

void UpdateFileData::setPubDate(QString pubDate)
{
    m_pubDate = pubDate;
}

QUrl UpdateFileData::getEnclosureUrl()
{
    return m_enclosureUrl;
}

void UpdateFileData::setEnclosureUrl(QUrl enclosureUrl)
{
    m_enclosureUrl = enclosureUrl;
}

void UpdateFileData::setEnclosureUrl(QString enclosureUrl)
{
    setEnclosureUrl(QUrl(enclosureUrl));
}

QString UpdateFileData::getEnclosureVersion()
{
    return m_enclosureVersion;
}

void UpdateFileData::setEnclosureVersion(QString enclosureVersion)
{
    m_enclosureVersion = enclosureVersion;
}

QString UpdateFileData::getEnclosurePlatform()
{
    return m_enclosurePlatform;
}

void UpdateFileData::setEnclosurePlatform(QString enclosurePlatform)
{
    m_enclosurePlatform = enclosurePlatform;
}

unsigned long UpdateFileData::getEnclosureLength()
{
    return m_enclosureLength;
}

void UpdateFileData::setEnclosureLength(unsigned long enclosureLength)
{
    m_enclosureLength = enclosureLength;
}

QString UpdateFileData::getEnclosureType()
{
    return m_enclosureType;
}

void UpdateFileData::setEnclosureType(QString enclosureType)
{
    m_enclosureType = enclosureType;
}
