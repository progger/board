/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICROSS_H
#define ICROSS_H

#include <QObjectList>
#include "iparser.h"
#include "iword.h"
#include "igrid.h"

class ICross {
public:
  virtual ~ICross() {}
  virtual IParser *createParser(QObject *parent, QObjectList *words) = 0;
  virtual IWord *createWord(QObject *parent) = 0;
  virtual IGrid *createGrid(QObject *parent) = 0;
};

Q_DECLARE_INTERFACE(ICross, "Board.cross.ICross/1.0")

#endif // ICROSS_H
