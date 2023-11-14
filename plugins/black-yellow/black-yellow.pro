QT += core gui qml quick

TARGET = black-yellow
TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/blackyellowbutton.cpp \
    src/blackyellow.cpp \
    src/blackyellowitem.cpp \
    src/blackyellowplugin.cpp

HEADERS +=\
    src/blackyellowbutton.h \
    src/blackyellow.h \
    src/blackyellowitem.h \
    src/blackyellowplugin.h

RESOURCES += black-yellow.qrc

target.path=/opt/board/plugins
INSTALLS += target
