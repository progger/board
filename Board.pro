#-------------------------------------------------
#
# Project created by QtCreator 2012-02-28T19:51:28
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = Board
TEMPLATE = app
VERSION = 0.0.1

OBJECTS_DIR = ./build
DESTDIR = ./bin
MOC_DIR = ./build
UI_DIR = ./build
RCC_DIR = ./build

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/boardcore.cpp \
    src/boarddraw.cpp

HEADERS += src/mainwindow.h \
    src/const.h \
    src/boardcore.h \
    src/boarddraw.h

FORMS += ui/mainwindow.ui

OTHER_FILES += web/page.html \
    web/main.js \
    web/tool.js

RESOURCES += \
    res.qrc








