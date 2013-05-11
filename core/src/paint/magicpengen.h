/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MAGICPENGEN_H
#define MAGICPENGEN_H

#include "pengen.h"

class MagicPenGen : public PenGen
{
public:
  explicit MagicPenGen(SheetCanvas *canvas);
  virtual void end(const QPointF &p) override;
};

#endif // MAGICPENGEN_H
