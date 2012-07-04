/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINTINFO_H
#define PAINTINFO_H

#include "iexternal.h"

class PaintInfo : public QObject, IExternal
{
  Q_OBJECT
  Q_INTERFACES(IExternal)
public:
  virtual ~PaintInfo() {}
  virtual void init(ICore *core);
};

#endif // PAINTINFO_H