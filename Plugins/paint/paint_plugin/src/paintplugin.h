/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINTPLUGIN_H
#define PAINTPLUGIN_H

#include <QObject>
#include "iplugin.h"

class PaintPlugin : public QObject, public IPlugin
{
  Q_OBJECT
  Q_INTERFACES(IPlugin)
public:
  virtual ~PaintPlugin() {}
};

#endif // PAINTPLUGIN_H
