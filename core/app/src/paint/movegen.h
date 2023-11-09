/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "shapegen.h"

class SheetCanvas;

class MoveGen : public ShapeGen
{
  Q_DISABLE_COPY_MOVE(MoveGen)
public:
  explicit MoveGen(ISheetCanvas *canvas);
  ~MoveGen() override = default;
  void move(const QPointF &p) override;
  void end(const QPointF &p) override;
};

#endif // MOVEGEN_H
