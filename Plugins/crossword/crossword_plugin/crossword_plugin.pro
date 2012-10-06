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

DESTDIR = ./build
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += \
    src/crosswordplugin.cpp

HEADERS += icore.h \
    iplugin.h \
    src/crosswordplugin.h

win32 {
  QMAKE_POST_LINK = cmd /c $(MOVE) .\\build\\$(TARGET) ..\\..\\..\\bin\\plugins\\crossword.plugin
} else {
  QMAKE_POST_LINK = $(MOVE) ./build/$(TARGET) ../../../bin/plugins/crossword.plugin
}

OTHER_FILES += \
    web/page.html

RESOURCES += \
    crossword_plugin.qrc
