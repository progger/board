/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "icore.h"

class IPlugin {
public:
  virtual ~IPlugin() {}
  virtual void init() = 0;
};

Q_DECLARE_INTERFACE(IPlugin, "Board.IPlugin")

#endif // IPLUGIN_H
