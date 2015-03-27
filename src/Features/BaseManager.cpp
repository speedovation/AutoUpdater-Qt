#include "BaseManager.h"

#include "UpdaterWindow.h"



BaseManager::BaseManager(UpdaterWindow* window) :
    QObject(window) , d(window)
{
    _getReleaseNotes = new GetReleaseNotes(window);
    _authenticator = new Authenticator(window);
    _updateChecker = new UpdateChecker(window);
    _parseUpdate = new ParseUpdate(window);
    _getUpdate = new GetUpdate(window);
    _messageDialogs = new MessageDialogs(window);
    _zip = new Zip(window);
    _helper = new Helper(window);
    _actionUpdate = new ActionUpdate(window);
    _ssl = new Ssl(window);
    _tests = new Tests(window);

}

GetReleaseNotes* BaseManager::getReleaseNotes()
{
    return _getReleaseNotes;
}
Authenticator* BaseManager::authenticator()
{
    return _authenticator;
}
UpdateChecker* BaseManager::updateChecker()
{
    return _updateChecker;
}
ParseUpdate* BaseManager::parseUpdate()
{
    return _parseUpdate;
}
GetUpdate* BaseManager::getUpdate()
{
    return _getUpdate;
}
MessageDialogs* BaseManager::messageDialogs()
{
    return _messageDialogs;
}
Zip* BaseManager::zip()
{
    return _zip;
}
Helper* BaseManager::helper()
{
    return _helper;
}
ActionUpdate* BaseManager::actionUpdate()
{
    return _actionUpdate;
}
Ssl* BaseManager::ssl()
{
    return _ssl;
}
Tests* BaseManager::tests()
{
    return _tests;
}
