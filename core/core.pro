QT += core gui qml quick

TARGET = board
TEMPLATE = app
VERSION = 2.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ../bin
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../shared

SOURCES += \
    src/core.cpp \
    src/main.cpp \
    src/mainview.cpp \
    src/paint/circlegen.cpp \
    src/paint/ellipse.cpp \
    src/paint/ellipsegen.cpp \
    src/paint/magicpengen.cpp \
    src/paint/paint.cpp \
    src/paint/paintutils.cpp \
    src/paint/pathprocessor/ellipse_pp.cpp \
    src/paint/pathprocessor/pathprocessor.cpp \
    src/paint/pathprocessor/polygon.cpp \
    src/paint/pathprocessor/shapehunter.cpp \
    src/paint/pathprocessor/utils.cpp \
    src/paint/pen.cpp \
    src/paint/pengen.cpp \
    src/paint/rectangle.cpp \
    src/paint/rectanglegen.cpp \
    src/paint/selectgen.cpp \
    src/paint/shape.cpp \
    src/paint/shapegen.cpp \
    src/paint/sheetcanvas.cpp \
    src/paint/textgen.cpp \
    src/paint/textwrapper.cpp

HEADERS += \
    src/core.h \
    src/mainview.h \
    src/paint/circlegen.h \
    src/paint/ellipse.h \
    src/paint/ellipsegen.h \
    src/paint/magicpengen.h \
    src/paint/paint.h \
    src/paint/paintutils.h \
    src/paint/pathprocessor/ellipse.h \
    src/paint/pathprocessor/pathprocessor.h \
    src/paint/pathprocessor/points.h \
    src/paint/pathprocessor/polygon.h \
    src/paint/pathprocessor/shape.h \
    src/paint/pathprocessor/shapehunter.h \
    src/paint/pathprocessor/utils.h \
    src/paint/pen.h \
    src/paint/pengen.h \
    src/paint/rectangle.h \
    src/paint/rectanglegen.h \
    src/paint/selectgen.h \
    src/paint/shape.h \
    src/paint/shapegen.h \
    src/paint/sheetcanvas.h \
    src/paint/textgen.h \
    src/paint/textwrapper.h

OTHER_FILES += \
    qml/Board.qml \
    qml/Button.qml \
    qml/keyboard.js \
    qml/Keyboard.qml \
    qml/ModeBar.qml \
    qml/sheet.js \
    qml/Sheet.qml \
    qml/SpinBox.qml \
    qml/Style.qml \
    qml/TextWrapper.qml \
    qml/ToolBar.qml \
    res/backspace.svg \
    res/back.svg \
    res/circle.svg \
    res/close.svg \
    res/color.svg \
    res/delete.svg \
    res/down_arrow.svg \
    res/duplicate.svg \
    res/ellipse.svg \
    res/enter.svg \
    res/font_size.svg \
    res/help \
    res/image.svg \
    res/left_arrow.svg \
    res/magic_pen.svg \
    res/minimize.svg \
    res/move.svg \
    res/open.svg \
    res/pen.svg \
    res/rectangle.svg \
    res/redo.svg \
    res/right_arrow.svg \
    res/save.svg \
    res/select.svg \
    res/text.svg \
    res/thickness.svg \
    res/undo.svg \
    res/up_arrow.svg

RESOURCES += core.qrc
