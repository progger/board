/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "crossedit.h"

const int min_size = 10;

Crossedit::Crossedit(QObject *parent, ICross *cross) :
  QObject(parent),
  cross_(cross),
  width_(min_size),
  height_(min_size),
  words_()
{
  grid_ = cross->createGrid(this);
  grid_->fill(width_, height_);
}
