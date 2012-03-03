/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "boardcore.h"
#include "boarddraw.h"
#include "const.h"

BoardCore::BoardCore(QObject *parent) :
  QObject(parent),
  draw_(new BoardDraw(this))
{
}

void BoardCore::readyToWork()
{
  draw_->setMode(QString(MODE_PEN));
  draw_->setColor(QString("black"));
}
