#-------------------------------------------------
#
# Project created by QtCreator 2012-02-28T19:51:28
#
#-------------------------------------------------

QT       += core opengl declarative

TARGET = Board
TEMPLATE = app
VERSION = 1.1.0

DESTDIR = ../bin
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../Shared

SOURCES += src/main.cpp \
    src/mainview.cpp \
    src/core.cpp \
    src/plugininfo.cpp

HEADERS += src/mainview.h \
    src/core.h \
    iplugin.h \
    iplugininfo.h \
    src/plugininfo.h

OTHER_FILES += qml/Board.qml \
    qml/Button.qml \
    qml/Draw.qml \
    qml/Keyboard.qml \
    qml/keyboard.js \
    qml/SpinBox.qml \
    qml/Style.qml \
    qml/Menu.qml \
    res/select.svg \
    res/backspace.svg \
    res/enter.svg \
    res/left_arrow.svg \
    res/right_arrow.svg \
    res/up_arrow.svg \
    res/down_arrow.svg \
    res/close.svg \
    res/undo.svg \
    res/redo.svg \
    res/delete.svg \
    res/save.svg \
    res/menu.svg

RESOURCES += \
    core.qrc
