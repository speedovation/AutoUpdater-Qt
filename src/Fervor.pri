contains(QT_VERSION, ^5\\.[0-9]\\..*){
    QT += core widgets webkitwidgets network
    win32:INCLUDEPATH += $$[QT_INSTALL_PREFIX]/include/QtZlib
}else{
    #QT += core gui webkit network
    QT += core webkit network
    fervor_gui {
        DEFINES += FV_GUI
        QT += gui
    }
    win32:INCLUDEPATH += $$[QT_INSTALL_PREFIX]/../../../../QtSources/4.8.1/src/3rdparty/zlib
}
DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"



DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

SOURCES += \
        $$PWD/fvupdatewindow.cpp \
        $$PWD/fvupdater.cpp \
        $$PWD/fvversioncomparator.cpp \
        $$PWD/fvplatform.cpp \
        $$PWD/fvignoredversions.cpp \
        $$PWD/fvupdateconfirmdialog.cpp \
        $$PWD/fvavailableupdate.cpp \

HEADERS += \
        $$PWD/fvupdatewindow.h \
        $$PWD/fvupdater.h \
        $$PWD/fvversioncomparator.h \
        $$PWD/fvplatform.h \
        $$PWD/fvignoredversions.h \
        $$PWD/fvupdateconfirmdialog.h \
        $$PWD/fvavailableupdate.h \


FORMS += \
        $$PWD/fvupdatewindow.ui \
        $$PWD/fvupdateconfirmdialog.ui \

fervor_gui {

    SOURCES += \
            $$PWD/fvupdatewindow.cpp \
            $$PWD/fvupdatedownloadprogress.cpp \

TRANSLATIONS += $$PWD/fervor_lt.ts

HEADERS += $$PWD/fvupdatewindow.h \
            $$PWD/fvupdatedownloadprogress.h

FORMS += $$PWD/fvupdatewindow.ui \
            $$PWD/fvupdatedownloadprogress.ui
}


TRANSLATIONS += fervor_lt.ts
CODECFORTR = UTF-8

DISTFILES += \
    $$PWD/fervor_lt.qm \
    $$PWD/fervor_lt.ts \
    $$PWD/OriginalReadme.md
