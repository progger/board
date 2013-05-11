QT       -= gui

TARGET = cross
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0
QMAKE_CXXFLAGS += -std=c++11

DESTDIR = ../../bin/libs
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../Shared
INCLUDEPATH += ../../Shared/cross

SOURCES += \
    src/cross.cpp \
    src/word.cpp \
    src/row.cpp \
    src/parser.cpp \
    src/grid.cpp \
    src/cell.cpp

HEADERS += \
    icore.h \
    iexternal.h \
    iparser.h \
    iword.h \
    icell.h \
    igrid.h \
    icross.h \
    src/cross.h \
    src/word.h \
    src/row.h \
    src/parser.h \
    src/grid.h \
    src/cell.h

OTHER_FILES += \
    qml/CrossGrid.qml

RESOURCES += cross.qrc
