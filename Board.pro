#-------------------------------------------------
#
# Project created by QtCreator 2012-02-28T19:51:28
#
#-------------------------------------------------

QT       += core opengl declarative

TARGET = Board
TEMPLATE = app
VERSION = 0.0.2

OBJECTS_DIR = ./build
DESTDIR = ./bin
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

FORMS +=

OTHER_FILES += web/page.html \
    web/main.js \
    res/pen.svg \
    res/rectangle.svg \
    res/circle.svg \
    res/move.svg \
    web/draw.js \
    web/error.js \
    res/ellipse.svg \
    qml/Draw.qml \
    qml/ModeBar.qml \
    qml/Style.qml \
    qml/Button.qml \
    qml/Keyboard.qml \
    qml/keyboard.js \
    qml/Board.qml \
    res/backspace.svg \
    res/enter.svg \
    res/left_arrow.svg \
    res/right_arrow.svg \
    qml/ToolBar.qml \
    res/close.svg \
    qml/ColorSelector.qml \
    qml/colorSelector.js \
    res/more.svg \
    res/select.svg \
    web/diff.js \
    res/undo.svg \
    res/redo.svg \
    web/shapes/select.js \
    web/shapes/pen.js \
    web/shapes/rectangle.js \
    web/shapes/circle.js \
    web/shapes/ellipse.js \
    web/shapes/text.js \
    web/tool.js

RESOURCES += \
    res.qrc
