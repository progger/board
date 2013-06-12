/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "shapegen.h"

class SheetCanvas;

class MoveGen : public ShapeGen
{
public:
  explicit MoveGen(ISheetCanvas *canvas);
  virtual void move(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
};

#endif // MOVEGEN_H
