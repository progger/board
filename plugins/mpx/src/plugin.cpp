/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include "mpxeventfilter.h"
#include "global.h"
#include "plugin.h"
#include <X11/X.h>
#include <X11/extensions/XInput2.h>

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  QGuiApplication *app = qobject_cast<QGuiApplication*>(QCoreApplication::instance());
  Display *display = static_cast<Display *>(app->platformNativeInterface()->nativeResourceForWindow("display", g_main_window));
  app->installNativeEventFilter(new MpxEventFilter(g_main_window));
  XIEventMask eventmask;
  unsigned char mask[1] = { 0 };
  eventmask.deviceid = XIAllMasterDevices;
  eventmask.mask_len = sizeof(mask);
  eventmask.mask = mask;
  XISetMask(mask, XI_Motion);
  XISetMask(mask, XI_ButtonPress);
  XISetMask(mask, XI_ButtonRelease);
  XISelectEvents(display, g_main_window->winId(), &eventmask, 1);
}
