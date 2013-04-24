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

SOURCES += \
    src/paintplugin.cpp \
    src/paint.cpp \
    src/pathprocessor.cpp \
    src/shape/utils.cpp \
    src/shape/shapehunter.cpp \
    src/shape/polygon.cpp \
    src/shape/ellipse.cpp

HEADERS += \
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
    qml/Sheet.qml \
    qml/sheet.js \
    qml/ToolBar.qml \
    qml/ModeBar.qml \
    qml/ColorSelector.qml \
    qml/colorSelector.js \
    js/tool.js \
    js/shape.js \
    js/shapes/select.js \
    js/shapes/pen.js \
    js/shapes/magic_pen.js \
    js/shapes/rectangle.js \
    js/shapes/circle.js \
    js/shapes/ellipse.js \
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
    res/color.svg

RESOURCES += paint_plugin.qrc
