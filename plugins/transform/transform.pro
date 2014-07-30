QT += core gui qml quick

TARGET = transform
TEMPLATE = lib
CONFIG += plugin
QMAKE_CXXFLAGS += -std=c++11
DESTDIR = ../../bin/plugins
LIBSDIR = ../../bin
DEPENDENCY_LIBRARIES = board-common

include(../../main.pri)

SOURCES += \
    src/plugin.cpp \
    src/card.cpp \
    src/cardtransform.cpp \
    src/transformbutton.cpp

HEADERS +=\
    src/plugin.h \
    src/card.h \
    src/cardtransform.h \
    src/transformbutton.h

OTHER_FILES += \
    qml/CardTransform.qml \
    qml/TransformButton.qml \
    res/cardQ.svg \
    res/cardX.svg \
    res/cardY.svg \
    res/transform.svg

RESOURCES += \
    transform.qrc

target.path=/opt/board/plugins
INSTALLS += target
