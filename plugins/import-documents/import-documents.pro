QT += core gui widgets qml quick

TARGET = import-documents
TEMPLATE = lib
CONFIG += plugin
VERSION = 2.0.0
QMAKE_CXXFLAGS += -std=c++11
LIBS += -lpoppler-cpp
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/plugin.cpp \
    src/importdoc.cpp

HEADERS += \
    src/plugin.h \
    src/importdoc.h

RESOURCES += import-documents.qrc

target.path=$$PREFIX/lib/board
INSTALLS += target

OTHER_FILES += \
    qml/ImportDocumentsButton.qml \
    res/import.svg
