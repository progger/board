QT       -= gui

TARGET = crossedit
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ../../../bin/plugins
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += \
    src/crosseditplugin.cpp

HEADERS += \
    icore.h \
    iplugin.h \
    src/crosseditplugin.h
