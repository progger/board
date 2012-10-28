/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IGRID_H
#define IGRID_H

#include "icell.h"

class IGrid {
public:
  virtual ~IGrid() {}
  virtual void fill(int width, int height) = 0;
  virtual QObjectList rows() = 0;
  virtual int width() = 0;
  virtual int height() = 0;
  virtual ICell *getCell(int x, int y) = 0;
  virtual void hideHighlight() = 0;
  virtual void paintGrid() = 0;
  virtual QObject *toQObject() = 0;
};

Q_DECLARE_INTERFACE(IGrid, "Board.cross.IGrid/1.0")

#endif // IGRID_H
