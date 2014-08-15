QT += core gui qml quick

TARGET = board-common
TEMPLATE = lib
VERSION = 2.0.0
QMAKE_CXXFLAGS += -std=c++11
DESTDIR = ../../bin
LIBSDIR = ../../bin

include(../../main.pri)

SOURCES += \
    src/commonshape.cpp \
    src/global.cpp \
    src/paneltool.cpp \
    src/shape.cpp \
    src/shapegen.cpp

HEADERS += \
    ../../shared/core/commonshape.h \
    ../../shared/core/global.h \
    ../../shared/core/ibrdstore.h \
    ../../shared/core/icore.h \
    ../../shared/core/ipaint.h \
    ../../shared/core/iplugin.h \
    ../../shared/core/isheetcanvas.h \
    ../../shared/core/isheet.h \
    ../../shared/core/paneltool.h \
    ../../shared/core/shape.h \
    ../../shared/core/shapegen.h

headers.path=/opt/board/include/board
headers.files=$$HEADERS
target.path=/opt/board
INSTALLS += headers target
