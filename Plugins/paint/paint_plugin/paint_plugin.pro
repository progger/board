#-------------------------------------------------
#
# Project created by QtCreator 2012-06-26T23:06:05
#
#-------------------------------------------------

QT       -= gui

TARGET = paint
TEMPLATE = lib
CONFIG += plugin
VERSION = 1.0.0

DESTDIR = ../../../bin/plugins
OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

INCLUDEPATH += ../../../Shared

SOURCES += src/paintplugin.cpp

HEADERS += src/paintplugin.h \
    iplugininfo.h
