QT       += core widgets qml quick opengl

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
    src/menuitem.cpp

HEADERS += \
    icore.h \
    iexternal.h \
    iplugininfo.h \
    iplugin.h \
    src/mainview.h \
    src/core.h \
    src/macro.h \
    src/global.h \
    src/menuitem.h

OTHER_FILES += \
    qml/Board.qml \
    qml/board.js \
    qml/Button.qml \
    qml/Keyboard.qml \
    qml/keyboard.js \
    qml/SpinBox.qml \
    qml/Style.qml \
    qml/Menu.qml \
    res/help \
    res/select.svg \
    res/backspace.svg \
    res/enter.svg \
    res/left_arrow.svg \
    res/right_arrow.svg \
    res/up_arrow.svg \
    res/down_arrow.svg \
    res/close.svg \
    res/minimize.svg \
    res/undo.svg \
    res/redo.svg \
    res/delete.svg \
    res/open.svg \
    res/save.svg \
    res/back.svg

RESOURCES += core.qrc
