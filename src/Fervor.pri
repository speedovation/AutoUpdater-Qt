contains(QT_VERSION, ^5\\.[0-9]\\..*){
    QT += core widgets webkitwidgets network
    win32:INCLUDEPATH += $$[QT_INSTALL_PREFIX]/include/QtZlib
}else{
    #QT += core gui webkit network
    QT += core network
    fervor_gui {
        DEFINES += FV_GUI
        QT += gui
    }
    win32:INCLUDEPATH += $$[QT_INSTALL_PREFIX]/../../../../QtSources/4.8.1/src/3rdparty/zlib
}
DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"
DEFINES += FV_GUI=\\\"true\\\"



DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

SOURCES += \
        $$PWD/fvupdater.cpp \
#        $$PWD/fvupdateconfirmdialog.cpp \
        $$PWD/Features/GetReleaseNotes.cpp \
        $$PWD/Features/BaseManager.cpp \
        $$PWD/UpdaterWindow.cpp \
        $$PWD/UpdateFileData/UpdateFileData.cpp \
        $$PWD/Partials/UpdateDownloadProgress.cpp \
        $$PWD/Features/Authenticator.cpp \
        $$PWD/Features/UpdateChecker.cpp \
        $$PWD/Features/GetUpdate.cpp \
        $$PWD/Features/ParseUpdate.cpp \
        $$PWD/Features/MessageDialogs.cpp \
        $$PWD/Features/Zip.cpp \
        $$PWD/Features/Ssl.cpp \
        $$PWD/Features/Helper.cpp \
        $$PWD/Features/ActionUpdate.cpp \
        $$PWD/Features/Tests.cpp \
        $$PWD/Common/Platform.cpp \
        $$PWD/Common/VersionComparator.cpp \
        $$PWD/Common/IgnoredVersions.cpp

HEADERS += \
        $$PWD/fvupdater.h \
#        $$PWD/fvupdateconfirmdialog.h \
        $$PWD/Features/GetReleaseNotes.h \
        $$PWD/Features/BaseManager.h \
        $$PWD/UpdaterWindow.h \
        $$PWD/UpdateFileData/UpdateFileData.h \
        $$PWD/Partials/UpdateDownloadProgress.h \
        $$PWD/Features/Authenticator.h \
        $$PWD/Features/UpdateChecker.h \
        $$PWD/Features/GetUpdate.h \
        $$PWD/Features/ParseUpdate.h \
        $$PWD/Features/MessageDialogs.h \
        $$PWD/Features/Zip.h \
        $$PWD/Features/Ssl.h \
        $$PWD/Features/Helper.h \
        $$PWD/Features/ActionUpdate.h \
        $$PWD/Features/Tests.h \
        $$PWD/Common/Platform.h \
        $$PWD/Common/VersionComparator.h \
        $$PWD/Common/IgnoredVersions.h


FORMS += \
    $$PWD/UpdaterWindow.ui \
    $$PWD/Partials/UpdateDownloadProgress.ui

fervor_gui {

    SOURCES += \
            $$PWD/fvupdatedownloadprogress.cpp \

    TRANSLATIONS += $$PWD/fervor_lt.ts

    HEADERS += \
            $$PWD/fvupdatedownloadprogress.h

    FORMS += \
            $$PWD/fvupdatedownloadprogress.ui

}


TRANSLATIONS += fervor_lt.ts
CODECFORTR = UTF-8

DISTFILES += \
    $$PWD/fervor_lt.qm \
    $$PWD/fervor_lt.ts \
    $$PWD/OriginalReadme.md
