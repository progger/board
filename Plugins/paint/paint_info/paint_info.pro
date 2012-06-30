#-------------------------------------------------
#
# Project created by QtCreator 2012-06-26T22:08:24
#
#-------------------------------------------------

QT       -= gui

TARGET = paint_info
TARGET_EXT = test
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0

DESTDIR = ./build
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += src/paintinfo.cpp

HEADERS += src/paintinfo.h \
    iplugininfo.h

RESOURCES += \
    paint_info.qrc

win32 {
  QMAKE_POST_LINK = cmd /c $(MOVE) .\\build\\$(TARGET) ..\\..\\..\\bin\\plugins\\paint.info
} else {
  QMAKE_POST_LINK = $(MOVE) ./build/$(TARGET) ../../../bin/plugins/paint.info
}
