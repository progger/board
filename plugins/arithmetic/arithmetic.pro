QT += core gui qml quick

TARGET = arithmetic
TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/arithmetic.cpp \
    src/arithmeticbutton.cpp \
    src/arithmeticitem.cpp \
    src/arithmeticplugin.cpp

HEADERS +=\
    src/arithmetic.h \
    src/arithmeticbutton.h \
    src/arithmeticitem.h \
    src/arithmeticplugin.h

RESOURCES += arithmetic.qrc

target.path=/opt/board/plugins
INSTALLS += target
