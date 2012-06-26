/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IPLUGIN_H
#define IPLUGIN_H

class IPlugin {
public:
  virtual ~IPlugin() {}
};

Q_DECLARE_INTERFACE(IPlugin, "Board.IPlugin/1.0")

#endif // IPLUGIN_H
