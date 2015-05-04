QT += core gui qml quick

TARGET = import-mimio
TEMPLATE = lib
LIBS += -lquazip-qt5
CONFIG += plugin
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/plugin.cpp

HEADERS +=\
    src/plugin.h

target.path=/opt/board/plugins
INSTALLS += target
