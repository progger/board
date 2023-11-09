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
  Q_DISABLE_COPY_MOVE(PenGen)
public:
  explicit PenGen(ISheetCanvas *canvas);
  ~PenGen() override = default;
  void begin(const QPointF &p) override;
  void end(const QPointF &) override;
  void move(const QPointF &p) override;
};

#endif // PENGEN_H
