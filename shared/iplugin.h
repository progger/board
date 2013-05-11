/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "icore.h"

class IPlugin {
public:
  virtual ~IPlugin() {}
  virtual void init(ICore *core, const QStringList &param) = 0;
};

Q_DECLARE_INTERFACE(IPlugin, "Board.IPlugin/1.0")

#endif // IPLUGIN_H
