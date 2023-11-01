VERSION = 2.4.0
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++latest
QMAKE_CXXFLAGS += -Werror -pedantic

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
