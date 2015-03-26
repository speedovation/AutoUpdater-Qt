#include "BaseManager.h"

#include "UpdaterWindow.h"
#include "GetReleaseNotes.h"

BaseManager::BaseManager(UpdaterWindow* window) :
    QObject(window) , d(window)
{
    _getReleaseNotes = new GetReleaseNotes(window);

}

GetReleaseNotes* BaseManager::getReleaseNotes()
{
    return _getReleaseNotes;
}
