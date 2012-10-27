QT       -= gui

TARGET = crossword_info
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ../../../bin/info
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += \
    src/crosswordinfo.cpp

HEADERS += \
    iplugininfo.h \
    src/crosswordinfo.h

OTHER_FILES += \
    res/logo.svg \
    res/edit_logo.svg

RESOURCES += crossword_info.qrc
