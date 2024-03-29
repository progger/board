/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef RECTANGLEGEN_H
#define RECTANGLEGEN_H

#include "shapegen.h"

class RectangleGen : public ShapeGen
{
  Q_DISABLE_COPY_MOVE(RectangleGen)
public:
  explicit RectangleGen(ISheetCanvas *canvas);
  ~RectangleGen() override = default;
  void begin(const QPointF &p) override;
};

#endif // RECTANGLEGEN_H
