/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CIRCLEGEN_H
#define CIRCLEGEN_H

#include "shapegen.h"

class CircleGen : public ShapeGen
{
  Q_DISABLE_COPY_MOVE(CircleGen)
public:
  explicit CircleGen(ISheetCanvas *canvas);
  ~CircleGen() override = default;
  void begin(const QPointF &p) override;
  void move(const QPointF &p) override;
};

#endif // CIRCLEGEN_H
