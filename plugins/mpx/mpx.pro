QT += core gui quick

TARGET = mpx
TEMPLATE = lib
CONFIG += plugin
QMAKE_CXXFLAGS += -std=c++11
LIBS += -lX11 -lXi -lxcb -lxcb-xinput
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

INCLUDEPATH += /opt/qt52/include/QtGui/5.2.1/QtGui

SOURCES += \
    src/mpxeventfilter.cpp \
    src/plugin.cpp

HEADERS += \
    src/mpxeventfilter.h \
    src/plugin.h

target.path=/opt/board/plugins
INSTALLS += target
