QT += core gui widgets
TARGET = Sample
VERSION = 1.0
TEMPLATE = app

DEFINES += TARGET=\\\"$TARGET\\\"

#DEFINES +=QUAZIP_STATIC
DEFINES += NOMINMAX
mac:ICON = sample.icns
win32:RC_FILE = sample.rc

INCLUDEPATH += $$PWD




# Fervor autoupdater
# (set TARGET and VERSION of your app before including Fervor.pri)
!include("../src/Handler/Handler.pri") {
	error("Unable to include Handler.")
}
#!include("../src/AutoUpdater.pri") {
#	error("Unable to include Autoupdater.")
#}

# The sample application
SOURCES += main.cpp \
		mainwindow.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui
