/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MACRO_H
#define MACRO_H

#include <qglobal.h>

#if defined Q_OS_LINUX
#define GET_LIB_NAME(file_name) ("lib" + (file_name) + ".so")
#elif defined Q_OS_WIN32
#define GET_LIB_NAME(file_name) ((file_name) + ".dll")
#else
#define GET_LIB_NAME(file_name) ((file_name))
#endif

#endif // MACRO_H
