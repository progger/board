QT       -= gui

TARGET = paint_info
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0

DESTDIR = ../../../bin/info
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += src/paintinfo.cpp

HEADERS += \
    src/paintinfo.h

OTHER_FILES += \
    res/logo.svg

RESOURCES += paint_info.qrc
