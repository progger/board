/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PENGEN_H
#define PENGEN_H

#include "shapegen.h"

class PenGen : public ShapeGen
{
public:
  explicit PenGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &) override;
  virtual void move(const QPointF &p) override;
};

#endif // PENGEN_H
