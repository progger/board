QT += core gui qml quick webkit

TARGET = mimio-shapes
TEMPLATE = lib
CONFIG += plugin
LIBS += -lhttp_parser
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/mimioshapesplugin.cpp \
    src/mimiotext.cpp \
    src/qhttpserver/qhttpconnection.cpp \
    src/qhttpserver/qhttprequest.cpp \
    src/qhttpserver/qhttpresponse.cpp \
    src/qhttpserver/qhttpserver.cpp \
    src/swfplayer.cpp \
    src/swfwebapp.cpp

HEADERS +=\
    src/mimioshapesplugin.h \
    src/mimiotext.h \
    src/qhttpserver/qhttpconnection.h \
    src/qhttpserver/qhttprequest.h \
    src/qhttpserver/qhttpresponse.h \
    src/qhttpserver/qhttpserverapi.h \
    src/qhttpserver/qhttpserverfwd.h \
    src/qhttpserver/qhttpserver.h \
    src/swfplayer.h \
    src/swfwebapp.h

RESOURCES += mimio-shapes.qrc

target.path=/opt/board/plugins
INSTALLS += target

OTHER_FILES +=
