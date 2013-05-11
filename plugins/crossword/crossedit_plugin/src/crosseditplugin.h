/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSEDITPLUGIN_H
#define CROSSEDITPLUGIN_H

#include <QObject>
#include "iplugin.h"

class CrosseditPlugin : public QObject, public IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Board.IPlugin/1.0")
  Q_INTERFACES(IPlugin)
public:
  virtual ~CrosseditPlugin() {}
  virtual void init(ICore *core, const QStringList &param);
};

#endif // CROSSEDITPLUGIN_H
