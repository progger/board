QT       += core opengl declarative

TARGET = Board
TEMPLATE = app
VERSION = 1.1.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ../bin
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../Shared

SOURCES += \
    src/main.cpp \
    src/mainview.cpp \
    src/core.cpp \
    src/plugininfo.cpp

HEADERS += \
    icore.h \
    iexternal.h \
    iplugin.h \
    src/mainview.h \
    src/core.h \
    src/plugininfo.h \
    src/macro.h

OTHER_FILES += \
    qml/Board.qml \
    qml/board.js \
    qml/Button.qml \
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
    res/back.svg \
    web/error.js

RESOURCES += core.qrc
