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
        $$PWD/UpdateChecker.cpp \
        $$PWD/GetUpdate.cpp \
        $$PWD/ParseUpdate.cpp \
        $$PWD/HandlerManager.cpp \
        $$PWD/../UpdateFileData/UpdateFileData.cpp \
        $$PWD/../Common/VersionComparator.cpp \
        $$PWD/../Common/Platform.cpp \
        $$PWD/../Common/IgnoredVersions.cpp \
    $$PWD/Ssl.cpp

HEADERS += \
        $$PWD/UpdateChecker.h \
        $$PWD/ParseUpdate.h \
        $$PWD/HandlerManager.h \
        $$PWD/GetUpdate.h \
        $$PWD/../UpdateFileData/UpdateFileData.h \
        $$PWD/../Common/VersionComparator.h \
        $$PWD/../Common/Platform.h \
        $$PWD/../Common/IgnoredVersions.h \
    $$PWD/Ssl.h



FORMS += \






