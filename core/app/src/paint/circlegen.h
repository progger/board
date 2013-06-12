/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CIRCLEGEN_H
#define CIRCLEGEN_H

#include "shapegen.h"

class CircleGen : public ShapeGen
{
public:
  explicit CircleGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
};

#endif // CIRCLEGEN_H
