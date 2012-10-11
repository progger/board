#-------------------------------------------------
#
# Project created by QtCreator 2012-10-06T21:12:06
#
#-------------------------------------------------

QT       -= gui

TARGET = crossword_plugin
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ./build
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += \
    src/crosswordplugin.cpp \
    src/crossword.cpp \
    src/parser.cpp \
    src/word.cpp

HEADERS += icore.h \
    iplugin.h \
    src/crosswordplugin.h \
    src/crossword.h \
    src/parser.h \
    src/word.h

win32 {
  QMAKE_POST_LINK = cmd /c $(MOVE) .\\build\\$(TARGET) ..\\..\\..\\bin\\plugins\\crossword.plugin
} else {
  QMAKE_POST_LINK = $(MOVE) ./build/$(TARGET) ../../../bin/plugins/crossword.plugin
}

OTHER_FILES += \
    web/page.html \
    web/main.js

RESOURCES += \
    crossword_plugin.qrc
