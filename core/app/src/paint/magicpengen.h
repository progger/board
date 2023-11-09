/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MAGICPENGEN_H
#define MAGICPENGEN_H

#include "pengen.h"

class MagicPenGen : public PenGen
{
  Q_DISABLE_COPY_MOVE(MagicPenGen)
public:
  explicit MagicPenGen(ISheetCanvas *canvas);
  ~MagicPenGen() override = default;
  void end(const QPointF &p) override;
};

#endif // MAGICPENGEN_H
