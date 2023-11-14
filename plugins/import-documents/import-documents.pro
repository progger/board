QT += core gui qml quick

TARGET = import-documents
TEMPLATE = lib
CONFIG += plugin
win32: LIBS += C:/lib/poppler/qt5/src/libpoppler-qt5.dll
linux: LIBS += -lpoppler-qt5
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

win32: INCLUDEPATH += C:/lib/poppler/qt5/src/

SOURCES += \
    src/importdocplugin.cpp \
    src/pdfviewer.cpp \
    src/importdoc.cpp

HEADERS += \
    src/importdocplugin.h \
    src/pdfviewer.h \
    src/importdoc.h

RESOURCES += import-documents.qrc

target.path=/opt/board/plugins
INSTALLS += target
