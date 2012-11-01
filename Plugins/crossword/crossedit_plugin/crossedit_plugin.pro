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
INCLUDEPATH += ../../../Shared/cross

SOURCES += \
    src/crosseditplugin.cpp \
    src/crossedit.cpp

HEADERS += \
    icore.h \
    iplugin.h \
    ilibobject.h \
    icross.h \
    iparser.h \
    iword.h \
    icell.h \
    igrid.h \
    src/crosseditplugin.h \
    src/crossedit.h

OTHER_FILES += \
    qml/Field.qml

RESOURCES += crossedit_plugin.qrc
