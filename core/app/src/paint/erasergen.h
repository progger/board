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
public:
  explicit EraserGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
private:
  QSet<CommonShape*> _shape_set;
};

#endif // ERASERGEN_H
