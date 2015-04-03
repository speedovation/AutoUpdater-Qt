QT += core widgets webkitwidgets network

TEMPLATE=app
TARGET = AutoUpdater
VERSION = 2.0.8


CONFIG   += c++11

DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

!include("../../thirdparty/miniz-cpp/Miniz.pri") {
	error("Unable to include Minz.")
}


SOURCES += \
        $$PWD/main.cpp \
        $$PWD/UpdaterWindow.cpp \
        $$PWD/Features/GetReleaseNotes.cpp \
        $$PWD/Features/BaseManager.cpp \
        $$PWD/Partials/UpdateDownloadProgress.cpp \
        $$PWD/Features/Authenticator.cpp \
        $$PWD/Features/MessageDialogs.cpp \
        $$PWD/Features/Zip.cpp \
        $$PWD/Features/Helper.cpp \
        $$PWD/Features/ActionUpdate.cpp \
        $$PWD/Features/Tests.cpp \
        $$PWD/Features/Mode.cpp \
        $$PWD/../Common/UpdateFileData.cpp \
        $$PWD/../Common/Platform.cpp \
        $$PWD/../Common/VersionComparator.cpp \
        $$PWD/../Common/IgnoredVersions.cpp \
        $$PWD/../Common/CommonTasks.cpp

HEADERS += \
        $$PWD/UpdaterWindow.h \
        $$PWD/Features/GetReleaseNotes.h \
        $$PWD/Features/BaseManager.h \
        $$PWD/Partials/UpdateDownloadProgress.h \
        $$PWD/Features/Authenticator.h \
        $$PWD/Features/GetUpdate.h \
        $$PWD/Features/MessageDialogs.h \
        $$PWD/Features/Zip.h \
        $$PWD/Features/Helper.h \
        $$PWD/Features/ActionUpdate.h \
        $$PWD/Features/Tests.h \
        $$PWD/Features/Mode.h \
        $$PWD/../Common/UpdateFileData.h \
        $$PWD/../Common/Platform.h \
        $$PWD/../Common/VersionComparator.h \
        $$PWD/../Common/IgnoredVersions.h \
        $$PWD/../Common/CommonTasks.h


FORMS += \
    $$PWD/UpdaterWindow.ui \
    $$PWD/Partials/UpdateDownloadProgress.ui \
#    UpdateWindow.ui


TRANSLATIONS += $$PWD/src/fervor_lt.ts


CODECFORTR = UTF-8

DISTFILES += \
    $$PWD/fervor_lt.qm \
    $$PWD/fervor_lt.ts \
    $$PWD/OriginalReadme.md
