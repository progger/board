QT += core gui qml quick

TARGET = black-yellow
TEMPLATE = lib
CONFIG += plugin
QMAKE_CXXFLAGS += -std=c++11
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/plugin.cpp \
    src/blackyellowbutton.cpp \
    src/blackyellow.cpp \
    src/blackyellowitem.cpp

HEADERS +=\
    src/plugin.h \
    src/blackyellowbutton.h \
    src/blackyellow.h \
    src/blackyellowitem.h

RESOURCES += black-yellow.qrc

target.path=/opt/board/plugins
INSTALLS += target
