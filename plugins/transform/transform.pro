QT += core gui qml quick

TARGET = transform
TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/card.cpp \
    src/cardtransform.cpp \
    src/transformbutton.cpp \
    src/transformplugin.cpp

HEADERS +=\
    src/card.h \
    src/cardtransform.h \
    src/transformbutton.h \
    src/transformplugin.h

RESOURCES += transform.qrc

target.path=/opt/board/plugins
INSTALLS += target
