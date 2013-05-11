/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSWORDINFO_H
#define CROSSWORDINFO_H

#include "iplugininfo.h"

class CrosswordInfo : public QObject, IPluginInfo
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Board.IPluginInfo/1.0")
  Q_INTERFACES(IPluginInfo)
public:
  virtual ~CrosswordInfo() {}
  virtual void init(ICore *core, QString menu_path);
};

#endif // CROSSWORDINFO_H
