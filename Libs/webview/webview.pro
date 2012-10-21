#-------------------------------------------------
#
# Project created by QtCreator 2012-10-15T14:05:22
#
#-------------------------------------------------

QT       -= gui

TARGET = webview
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ./build
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../Shared

SOURCES += src/webview.cpp \
    src/webviewobject.cpp

HEADERS += icore.h \
    iexternal.h \
    iwebview.h \
    iweblib.h \
    iwebviewobject.h \
    src/webview.h \
    src/webviewobject.h

OTHER_FILES += qml/webPage.js \
    qml/WebPage.qml \
    web/error.js

RESOURCES += webview.qrc

win32 {
  QMAKE_POST_LINK = cmd /c $(MOVE) .\\build\\$(TARGET) ..\\..\\bin\\libs\\webview.lib
} else {
  QMAKE_POST_LINK = $(MOVE) ./build/$(TARGET) ../../bin/libs/webview.lib
}
