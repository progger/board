/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ELLIPSEGEN_H
#define ELLIPSEGEN_H

#include "shapegen.h"

class EllipseGen : public ShapeGen
{
public:
  explicit EllipseGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
};

#endif // ELLIPSEGEN_H
