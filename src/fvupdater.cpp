#include "fvupdater.h"

#include "Platform.h"
#include "fvignoredversions.h"



#ifdef FV_GUI
#include "UpdaterWindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#else
// QSettings key for automatic update installation
#define FV_NEW_VERSION_POLICY_KEY              "FVNewVersionPolicy"
#endif

#ifdef FV_DEBUG

#endif

//extern QSettings* settings;

