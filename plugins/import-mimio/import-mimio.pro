QT += core gui qml quick xml

TARGET = import-mimio
TEMPLATE = lib
LIBS += -lquazip5
CONFIG += plugin
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/importer.cpp \
    src/plugin.cpp \
    src/rtfconverter.cpp \
    src/rtfparser.cpp

HEADERS +=\
    src/importer.h \
    src/plugin.h \
    src/rtfconverter.h \
    src/rtfparser.h

target.path=/opt/board/plugins
INSTALLS += target
