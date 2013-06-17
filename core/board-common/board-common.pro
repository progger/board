QT += core gui qml quick

TARGET = board-common
TEMPLATE = lib
VERSION = 2.0.0
QMAKE_CXXFLAGS += -std=c++11
DESTDIR = ../../bin

include(../../main.pri)

SOURCES += \
    src/global.cpp \
    src/shape.cpp \
    src/shapegen.cpp

HEADERS += \
    ../../shared/core/global.h \
    ../../shared/core/ibrdstore.h \
    ../../shared/core/icore.h \
    ../../shared/core/ipaint.h \
    ../../shared/core/iplugin.h \
    ../../shared/core/isheetcanvas.h \
    ../../shared/core/isheet.h \
    ../../shared/core/shape.h \
    ../../shared/core/shapegen.h

headers.path=$$PREFIX/include/board
headers.files=$$HEADERS
target.path=$$PREFIX/lib
INSTALLS += headers target
