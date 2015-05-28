QT += core gui qml quick

TARGET = mimio-shapes
TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/mimiotext.cpp \
    src/plugin.cpp

HEADERS +=\
    src/mimiotext.h \
    src/plugin.h

RESOURCES += mimio-shapes.qrc

target.path=/opt/board/plugins
INSTALLS += target
