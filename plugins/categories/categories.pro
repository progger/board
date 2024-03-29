QT += core gui qml quick

TARGET = categories
TEMPLATE = lib
CONFIG += plugin
QMAKE_CXXFLAGS += -std=c++11
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/categories.cpp \
    src/categoriesbutton.cpp \
    src/categoriesplugin.cpp \
    src/category.cpp \
    src/categoryitem.cpp

HEADERS +=\
    src/categories.h \
    src/categoriesbutton.h \
    src/categoriesplugin.h \
    src/category.h \
    src/categoryitem.h

RESOURCES += categories.qrc

target.path=/opt/board/plugins
INSTALLS += target
