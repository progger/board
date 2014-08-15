QT += core gui qml quick widgets

TARGET = board
TEMPLATE = app
LIBS += -lz
DESTDIR =  ../../bin
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)
include(../../third-party/quazip-0.5.1/quazip/quazip.pri)

SOURCES += \
    src/brd/brdnetworkaccessmanager.cpp \
    src/brd/brdnetworkaccessmanagerfactory.cpp \
    src/brd/brdreply.cpp \
    src/brd/brdstore.cpp \
    src/core.cpp \
    src/main.cpp \
    src/paint/circlegen.cpp \
    src/paint/ellipse.cpp \
    src/paint/ellipsegen.cpp \
    src/paint/erasergen.cpp \
    src/paint/imagegen.cpp \
    src/paint/imagewrapper.cpp \
    src/paint/line.cpp \
    src/paint/linegen.cpp \
    src/paint/magicpengen.cpp \
    src/paint/movegen.cpp \
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
    src/paint/sheet.cpp \
    src/paint/sheetcanvas.cpp \
    src/paint/textgen.cpp \
    src/paint/textwrapper.cpp \
    src/paint/videogen.cpp \
    src/paint/videoplayer.cpp \
    src/panel.cpp \
    src/str_stack/strstack.cpp \
    src/style.cpp \
    src/tool.cpp

HEADERS += \
    src/brd/brdnetworkaccessmanager.h \
    src/brd/brdnetworkaccessmanagerfactory.h \
    src/brd/brdreply.h \
    src/brd/brdstore.h \
    src/core.h \
    src/paint/circlegen.h \
    src/paint/ellipse.h \
    src/paint/ellipsegen.h \
    src/paint/erasergen.h \
    src/paint/imagegen.h \
    src/paint/imagewrapper.h \
    src/paint/line.h \
    src/paint/linegen.h \
    src/paint/magicpengen.h \
    src/paint/movegen.h \
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
    src/paint/sheet.h \
    src/paint/sheetcanvas.h \
    src/paint/textgen.h \
    src/paint/textwrapper.h \
    src/paint/videogen.h \
    src/paint/videoplayer.h \
    src/panel.h \
    src/str_stack/strstack.h \
    src/style.h \
    src/tool.h

RESOURCES += app.qrc

target.path=/opt/board
INSTALLS += target
