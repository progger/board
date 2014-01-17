/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QWindow>
#include "icore.h"

extern bool g_window_mode;
extern QString g_brd_file;
extern ICore *g_core;
extern QWindow *g_main_window;

#endif // GLOBAL_H
