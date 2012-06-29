#-------------------------------------------------
#
# Project created by QtCreator 2012-06-26T23:06:05
#
#-------------------------------------------------

TARGET = paint
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0

DESTDIR = ../../../bin/plugins
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += src/paintplugin.cpp \
    src/paint.cpp

HEADERS += src/paintplugin.h \
    icore.h \
    iplugin.h \
    src/const.h \
    src/paint.h

RESOURCES += \
    paint_plugin.qrc

OTHER_FILES += \
    qml/ToolBar.qml \
    qml/ModeBar.qml \
    qml/ColorSelector.qml \
    qml/colorSelector.js \
    res/pen.svg \
    res/rectangle.svg \
    res/circle.svg \
    res/ellipse.svg \
    res/text.svg \
    res/image.svg \
    res/move.svg \
    res/duplicate.svg \
    res/thickness.svg \
    res/font_size.svg
