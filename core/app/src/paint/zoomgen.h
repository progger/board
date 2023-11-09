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
  Q_DISABLE_COPY_MOVE(ZoomGen)
public:
  explicit ZoomGen(ISheetCanvas *canvas);
  ~ZoomGen() override = default;
  void begin(const QPointF &p) override;
  void move(const QPointF &p) override;
  void end(const QPointF &p) override;
private:
  int _last;
};

#endif // SCALEGEN_H
