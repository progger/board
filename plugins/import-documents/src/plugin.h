/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>
#include "iplugin.h"

class Plugin : public QObject, IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "board.import-documents")
  Q_INTERFACES(IPlugin)
public:
  explicit Plugin(QObject *parent = 0);
  virtual void init() override;
};

#endif // PLUGIN_H
