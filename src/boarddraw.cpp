/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "boarddraw.h"

BoardDraw::BoardDraw(QObject *parent) :
  QObject(parent),
  state_(false),
  mode_()
{
}

void BoardDraw::setMode(const QString &mode)
{
  mode_ = mode;
  modeChanged();
}
