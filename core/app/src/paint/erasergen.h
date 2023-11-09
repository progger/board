/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ERASERGEN_H
#define ERASERGEN_H

#include <QSet>
#include "commonshape.h"
#include "shapegen.h"

class EraserGen : public ShapeGen
{
  Q_DISABLE_COPY_MOVE(EraserGen)
public:
  explicit EraserGen(ISheetCanvas *canvas);
  ~EraserGen() override = default;
  void begin(const QPointF &p) override;
  void end(const QPointF &p) override;
  void move(const QPointF &p) override;
private:
  QSet<CommonShape*> _shape_set;
};

#endif // ERASERGEN_H
