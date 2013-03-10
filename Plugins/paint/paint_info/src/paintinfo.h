/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINTINFO_H
#define PAINTINFO_H

#include "iplugininfo.h"

class PaintInfo : public QObject, IPluginInfo
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Board.IPluginInfo/1.0")
  Q_INTERFACES(IPluginInfo)
public:
  virtual ~PaintInfo() {}
  virtual void init(ICore *core, QString menu_path);
};

#endif // PAINTINFO_H
