/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "menuitem.h"

MenuItem::MenuItem(QObject *parent, const QString &name, const QString &image,
                   const QString &plugin_name, const QStringList &plugin_param) :
  QObject(parent),
  name_(name),
  image_(image),
  plugin_name_(plugin_name),
  plugin_param_(plugin_param)
{
}
