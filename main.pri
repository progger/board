VERSION = 2.2.0
QMAKE_CXXFLAGS += -std=c++11

OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += \
    $$PWD/shared \
    $$PWD/shared/core

win32: {
  LIBPOSTFIX=2
  SONAME=dll
}
linux: {
  LIBPREFIX=lib
  SONAME=so
}

for(dep, DEPENDENCY_LIBRARIES) {
    LIBS += $${LIBSDIR}/$${LIBPREFIX}$${dep}$${LIBPOSTFIX}.$${SONAME}
    PRE_TARGETDEPS += $${LIBSDIR}/$${LIBPREFIX}$${dep}$${LIBPOSTFIX}.$${SONAME}
}
