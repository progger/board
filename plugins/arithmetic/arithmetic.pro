QT += core gui qml quick

TARGET = arithmetic
TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/plugin.cpp \
    src/arithmetic.cpp \
    src/arithmeticbutton.cpp \
    src/arithmeticitem.cpp

HEADERS +=\
    src/plugin.h \
    src/arithmetic.h \
    src/arithmeticbutton.h \
    src/arithmeticitem.h

RESOURCES += arithmetic.qrc

target.path=/opt/board/plugins
INSTALLS += target
