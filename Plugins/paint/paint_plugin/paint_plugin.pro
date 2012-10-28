TARGET = paint
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ../../../bin/plugins
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared
INCLUDEPATH += ../../../Shared/webview

SOURCES += \
    src/paintplugin.cpp \
    src/paint.cpp \
    src/pathprocessor.cpp \
    src/shape/utils.cpp \
    src/shape/shapehunter.cpp \
    src/shape/polygon.cpp \
    src/shape/ellipse.cpp

HEADERS += \
    icore.h \
    iplugin.h \
    iwebviewobject.h \
    iwebview.h \
    src/paintplugin.h \
    src/const.h \
    src/paint.h \
    src/pathprocessor.h \
    src/shape/utils.h \
    src/shape/shapehunter.h \
    src/shape/shape.h \
    src/shape/polygon.h \
    src/shape/pointarray.h \
    src/shape/ellipse.h

OTHER_FILES += \
    qml/Draw.qml \
    qml/ToolBar.qml \
    qml/ModeBar.qml \
    qml/ColorSelector.qml \
    qml/colorSelector.js \
    res/pen.svg \
    res/magic_pen.svg \
    res/rectangle.svg \
    res/circle.svg \
    res/ellipse.svg \
    res/text.svg \
    res/image.svg \
    res/move.svg \
    res/duplicate.svg \
    res/thickness.svg \
    res/font_size.svg \
    res/color.svg \
    web/page.html \
    web/main.js \
    web/tool.js \
    web/draw.js \
    web/diff.js \
    web/shapes/select.js \
    web/shapes/pen.js \
    web/shapes/rectangle.js \
    web/shapes/circle.js \
    web/shapes/ellipse.js \
    web/shapes/text.js \
    web/shapes/image.js \
    web/shapes/magic_pen.js

RESOURCES += paint_plugin.qrc
