QT += core widgets network

CONFIG   += c++11


DEPENDPATH += "$$PWD"
INCLUDEPATH += "$$PWD"

!include("../../thirdparty/miniz-cpp/Miniz.pri") {
	error("Unable to include Minz.")
}


SOURCES += \
        $$PWD/HandlerManager.cpp \
        $$PWD/Features/UpdateChecker.cpp \
        $$PWD/Features/ParseUpdate.cpp \
        $$PWD/Features/GetUpdate.cpp \
        $$PWD/Features/Ssl.cpp \
        $$PWD/../Common/UpdateFileData.cpp \
        $$PWD/../Common/VersionComparator.cpp \
        $$PWD/../Common/Platform.cpp \
        $$PWD/../Common/IgnoredVersions.cpp \

HEADERS += \
        $$PWD/HandlerManager.h \
        $$PWD/Features/UpdateChecker.h \
        $$PWD/Features/ParseUpdate.h \
        $$PWD/Features/GetUpdate.h \
        $$PWD/Features/Ssl.h \
        $$PWD/../Common/UpdateFileData.h \
        $$PWD/../Common/VersionComparator.h \
        $$PWD/../Common/Platform.h \
        $$PWD/../Common/IgnoredVersions.h \



FORMS += \






