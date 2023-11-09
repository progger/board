/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QObject>

class IPlugin {
  Q_DISABLE_COPY_MOVE(IPlugin)
public:
  IPlugin() = default;
  virtual ~IPlugin() = default;
  virtual void init() = 0;
};

Q_DECLARE_INTERFACE(IPlugin, "Board.IPlugin")

#endif // IPLUGIN_H
