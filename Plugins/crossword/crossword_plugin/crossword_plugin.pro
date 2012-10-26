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

SOURCES += \
    src/crosswordplugin.cpp \
    src/crossword.cpp \
    src/parser.cpp \
    src/word.cpp \
    src/cell.cpp \
    src/row.cpp

HEADERS += \
    icore.h \
    iplugin.h \
    src/crosswordplugin.h \
    src/crossword.h \
    src/parser.h \
    src/word.h \
    src/cell.h \
    src/row.h

OTHER_FILES += \
    qml/Field.qml \
    res/winter.txt

RESOURCES += crossword_plugin.qrc
