/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSWORDINFO_H
#define CROSSWORDINFO_H

#include "iexternal.h"

class CrosswordInfo : public QObject, IExternal
{
  Q_OBJECT
  Q_INTERFACES(IExternal)
public:
  virtual ~CrosswordInfo() {}
  virtual void init(ICore *core);
};

#endif // CROSSWORDINFO_H
