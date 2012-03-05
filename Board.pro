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
    web/tool.js \
    res/pen.svg \
    res/rectangle.svg \
    res/circle.svg \
    res/move.svg \
    web/draw.js \
    web/error.js \
    res/color/yellow.svg \
    res/color/red.svg \
    res/color/fuchsia.svg \
    res/color/blue.svg \
    res/color/black.svg \
    res/color/aqua.svg \
    res/color/lime.svg

RESOURCES += \
    res.qrc









