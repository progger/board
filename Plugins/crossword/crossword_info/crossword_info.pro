#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T19:11:46
#
#-------------------------------------------------

QT       -= gui

TARGET = crossword_info
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0

DESTDIR = ./build
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += src/crosswordinfo.cpp

HEADERS += iexternal.h \
    src/crosswordinfo.h

win32 {
  QMAKE_POST_LINK = cmd /c $(MOVE) .\\build\\$(TARGET) ..\\..\\..\\bin\\plugins\\crossword.info
} else {
  QMAKE_POST_LINK = $(MOVE) ./build/$(TARGET) ../../../bin/plugins/crossword.info
}
