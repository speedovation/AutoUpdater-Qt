#contains(QT_VERSION, ^5\\.[0-9]\\..*){

   QT += core widgets webkitwidgets network

#}else{
    #QT += core gui webkit network
#    QT += core network
#    fervor_gui {
#        DEFINES += FV_GUI
#        QT += gui
#    }
#    win32:INCLUDEPATH += $$[QT_INSTALL_PREFIX]/../../../../QtSources/4.8.1/src/3rdparty/zlib
#}


DEFINES += FV_APP_NAME=\\\"$$TARGET\\\"
DEFINES += FV_APP_VERSION=\\\"$$VERSION\\\"
CONFIG   += c++11


DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

!include("../../thirdparty/miniz-cpp/Miniz.pri") {
	error("Unable to include Minz.")
}


SOURCES += \
        $$PWD/Features/UpdateChecker.cpp \
        $$PWD/Features/GetUpdate.cpp \
        $$PWD/Features/ParseUpdate.cpp \
        $$PWD/HandlerManager.cpp \
        $$PWD/../Common/UpdateFileData.cpp \
        $$PWD/../Common/VersionComparator.cpp \
        $$PWD/../Common/Platform.cpp \
        $$PWD/../Common/IgnoredVersions.cpp \
    $$PWD/Features/Ssl.cpp

HEADERS += \
        $$PWD/Features/UpdateChecker.h \
        $$PWD/Features/ParseUpdate.h \
        $$PWD/HandlerManager.h \
        $$PWD/Features/GetUpdate.h \
        $$PWD/../Common/UpdateFileData.h \
        $$PWD/../Common/VersionComparator.h \
        $$PWD/../Common/Platform.h \
        $$PWD/../Common/IgnoredVersions.h \
    $$PWD/Features/Ssl.h



FORMS += \






