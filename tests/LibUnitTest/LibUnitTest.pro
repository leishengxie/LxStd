#-------------------------------------------------
#
# Project created by QtCreator 2019-10-08T09:41:20
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_libunittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_libunittesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LQtTool/bin/ -lLQtToold

INCLUDEPATH += $$PWD/../LQtTool/include
DEPENDPATH += $$PWD/../LQtTool/include
