QMAKE_CXXFLAGS += -std=c++11

OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += \
    $$PWD/shared \
    $$PWD/shared/core

win32: SONAME=dll
linux: SONAME=so

for(dep, DEPENDENCY_LIBRARIES) {
    LIBS += $${DESTDIR}/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${DESTDIR}/lib$${dep}.$${SONAME}
}
