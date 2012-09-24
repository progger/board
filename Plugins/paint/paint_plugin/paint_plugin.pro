#-------------------------------------------------
#
# Project created by QtCreator 2012-06-26T23:06:05
#
#-------------------------------------------------

TARGET = paint
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0

DESTDIR = ./build
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += src/paintplugin.cpp \
    src/paint.cpp \
    src/pathprocessor.cpp \
    src/shape/utils.cpp \
    src/shape/shapehunter.cpp \
    src/shape/polygon.cpp \
    src/shape/ellipse.cpp

HEADERS += icore.h \
    iplugin.h \
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

RESOURCES += \
    paint_plugin.qrc

OTHER_FILES += \
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
    web/error.js \
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

win32 {
  QMAKE_POST_LINK = cmd /c $(MOVE) .\\build\\$(TARGET) ..\\..\\..\\bin\\plugins\\paint.plugin
} else {
  QMAKE_POST_LINK = $(MOVE) ./build/$(TARGET) ../../../bin/plugins/paint.plugin
}
