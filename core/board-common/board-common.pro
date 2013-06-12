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
    ../../shared/core/shape.h
