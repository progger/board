#-------------------------------------------------
#
# Project created by QtCreator 2012-02-28T19:51:28
#
#-------------------------------------------------

QT       += core opengl declarative

TARGET = Board
TEMPLATE = app
VERSION = 1.0.0

OBJECTS_DIR = ./build
DESTDIR = ../bin
MOC_DIR = ./build
UI_DIR = ./build
RCC_DIR = ./build

SOURCES += src/main.cpp \
    src/mainview.cpp \
    src/core.cpp

HEADERS += \
    src/const.h \
    src/mainview.h \
    src/core.h

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
