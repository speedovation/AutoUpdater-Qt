#include "BaseManager.h"

#include "UpdaterWindow.h"

#include "GetReleaseNotes.h"
#include "GetUpdate.h"
#include "ParseUpdate.h"
#include "UpdateChecker.h"
#include "Authenticator.h"

BaseManager::BaseManager(UpdaterWindow* window) :
    QObject(window) , d(window)
{
    _getReleaseNotes = new GetReleaseNotes(window);
    _authenticator = new Authenticator(window);
    _updateChecker = new UpdateChecker(window);
    _parseUpdate = new ParseUpdate(window);
    _getUpdate = new GetUpdate(window);

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
