/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINTINFO_H
#define PAINTINFO_H

#include <QObject>
#include "iplugininfo.h"

class PaintInfo : public QObject, public IPluginInfo
{
  Q_OBJECT
  Q_INTERFACES(IPluginInfo)
public:
  virtual ~PaintInfo() {}
};

#endif // PAINTINFO_H
