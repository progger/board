/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IPLUGININFO_H
#define IPLUGININFO_H

#include <QString>

class IPluginInfo {
public:
  virtual ~IPluginInfo() {}
  virtual QString name() = 0;
  virtual QString image() = 0;
};

Q_DECLARE_INTERFACE(IPluginInfo, "Board.IPluginInfo/1.0")

#endif // IPLUGININFO_H
