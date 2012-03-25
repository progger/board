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
    src/boarddraw.cpp \
    src/diff/diffitem.cpp \
    src/diff/diffstack.cpp \
    src/mainview.cpp \
    src/core.cpp

HEADERS += \
    src/const.h \
    src/boarddraw.h \
    src/diff/diffitem.h \
    src/diff/diffstack.h \
    src/mainview.h \
    src/core.h

FORMS +=

OTHER_FILES += web/page.html \
    web/main.js \
    web/tool.js \
    res/pen.svg \
    res/rectangle.svg \
    res/circle.svg \
    res/move.svg \
    web/draw.js \
    web/error.js \
    res/ellipse.svg \
    web/transform.js \
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
    res/right_arrow.svg

RESOURCES += \
    res.qrc
