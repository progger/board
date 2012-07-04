/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IEXTERNAL_H
#define IEXTERNAL_H

#include "icore.h"

class IExternal {
public:
  virtual ~IExternal() {}
  virtual void init(ICore *core) = 0;
};

Q_DECLARE_INTERFACE(IExternal, "Board.IExternal/1.0")

#endif // IEXTERNAL_H
