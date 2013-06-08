/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef LINEGEN_H
#define LINEGEN_H

#include "shapegen.h"

class LineGen : public ShapeGen
{
public:
  explicit LineGen(SheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
};

#endif // LINEGEN_H