/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TEXTGEN_H
#define TEXTGEN_H

#include "shapegen.h"

class TextGen : public ShapeGen
{
public:
  explicit TextGen(SheetCanvas *canvas);
  virtual ~TextGen() override;
  virtual void begin(const QPointF &);
  virtual void end(const QPointF &p);
  virtual void move(const QPointF &);
private:
  void endEdit();
};

#endif // TEXTGEN_H
