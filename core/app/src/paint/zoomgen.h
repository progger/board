/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SCALEGEN_H
#define SCALEGEN_H

#include "shapegen.h"

class ZoomGen : public ShapeGen
{
public:
  explicit ZoomGen(ISheetCanvas *canvas);
  virtual void begin(const QPointF &p);
  virtual void move(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
private:
  float _last;
};

#endif // SCALEGEN_H
