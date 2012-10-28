QT       -= gui

TARGET = webview
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ../../bin/libs
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../Shared
INCLUDEPATH += ../../Shared/webview

SOURCES += \
    src/webview.cpp \
    src/webviewobject.cpp

HEADERS += \
    icore.h \
    iexternal.h \
    iwebview.h \
    iwebviewobject.h \
    src/webview.h \
    src/webviewobject.h

OTHER_FILES += \
    qml/webPage.js \
    qml/WebPage.qml \
    web/error.js

RESOURCES += webview.qrc
