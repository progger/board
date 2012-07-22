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
DESTDIR = ./bin
MOC_DIR = ./build
UI_DIR = ./build
RCC_DIR = ./build

SOURCES += src/main.cpp \
    src/mainview.cpp \
    src/core.cpp \
    src/pathprocessor.cpp \
    src/shape/shapehunter.cpp \
    src/shape/utils.cpp \
    src/shape/polygon.cpp \
    src/shape/ellipse.cpp

HEADERS += \
    src/const.h \
    src/mainview.h \
    src/core.h \
    src/pathprocessor.h \
    src/shape/pointarray.h \
    src/shape/shapehunter.h \
    src/shape/shape.h \
    src/shape/utils.h \
    src/shape/polygon.h \
    src/shape/ellipse.h

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
    web/tool.js \
    res/delete.svg \
    res/duplicate.svg \
    res/save.svg \
    qml/SpinBox.qml \
    res/up_arrow.svg \
    res/down_arrow.svg \
    res/thickness.svg \
    res/font_size.svg \
    res/image.svg \
    web/shapes/image.js \
    res/magic_pen.svg \
    web/shapes/magic_pen.js \
    res/color.svg

RESOURCES += \
    res.qrc
