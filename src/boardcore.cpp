/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "boardcore.h"
#include "const.h"

BoardCore::BoardCore(QObject *parent) :
  QObject(parent),
  state_(false),
  mode_()
{
}

void BoardCore::readyToWork()
{
  setMode(QString(MODE_PEN));
  setColor(QString("black"));
}

void BoardCore::setMode(const QString &mode)
{
  mode_ = mode;
  modeChanged();
}
