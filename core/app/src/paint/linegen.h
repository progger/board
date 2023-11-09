/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef LINEGEN_H
#define LINEGEN_H

#include "shapegen.h"

class LineGen : public ShapeGen
{
  Q_DISABLE_COPY_MOVE(LineGen)
public:
  explicit LineGen(ISheetCanvas *canvas);
  ~LineGen() override = default;
  void begin(const QPointF &p) override;
  void move(const QPointF &p) override;
};

#endif // LINEGEN_H
