QT       -= gui

TARGET = crossword
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
    src/crosswordplugin.cpp \
    src/crossword.cpp

HEADERS += \
    icore.h \
    iplugin.h \
    icross.h \
    iparser.h \
    iword.h \
    icell.h \
    igrid.h \
    src/crosswordplugin.h \
    src/crossword.h

OTHER_FILES += \
    qml/Field.qml \
    res/winter.txt

RESOURCES += crossword_plugin.qrc
