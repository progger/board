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
  Q_DISABLE_COPY_MOVE(EllipseGen)
public:
  explicit EllipseGen(ISheetCanvas *canvas);
  ~EllipseGen() override = default;
  void begin(const QPointF &p) override;
};

#endif // ELLIPSEGEN_H
