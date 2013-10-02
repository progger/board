QT += core gui widgets qml quick

TARGET = import-documents
TEMPLATE = lib
CONFIG += plugin
VERSION = 2.0.0
QMAKE_CXXFLAGS += -std=c++11
win32: LIBS += C:/lib/poppler/qt5/src/libpoppler-qt5.dll
linux: LIBS += -lpoppler-qt5
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

win32: INCLUDEPATH += C:/lib/poppler/qt5/src/

SOURCES += \
    src/plugin.cpp \
    src/pdfviewer.cpp \
    src/importdoc.cpp

HEADERS += \
    src/plugin.h \
    src/pdfviewer.h \
    src/importdoc.h

RESOURCES += import-documents.qrc

target.path=$$PREFIX/lib/board
INSTALLS += target

OTHER_FILES += \
    qml/ImportDocumentsButton.qml \
    qml/PdfViewer.qml \
    res/import.svg
