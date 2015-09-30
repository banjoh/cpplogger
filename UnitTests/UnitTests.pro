#-------------------------------------------------
#
# Project created by QtCreator 2015-09-29T21:20:23
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unitteststest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++14

TEMPLATE = app

INCLUDEPATH += "..\Logger"

SOURCES += tst_unitteststest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Logger/build/release/ -llogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Logger/build/debug/ -llogger
else:unix: LIBS += -L$$PWD/../Logger/build/ -llogger

INCLUDEPATH += $$PWD/../Logger/build/debug
DEPENDPATH += $$PWD/../Logger/build/debug
