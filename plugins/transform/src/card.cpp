/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "card.h"

Card::Card(QObject *parent) :
  QObject(parent),
  _left_hash(),
  _right_hash()
{
}

QString Card::leftSource() const
{
  return g_core->brdStore()->getUrlString(_left_hash);
}

QString Card::rightSource() const
{
  return g_core->brdStore()->getUrlString(_right_hash);
}

void Card::setLeftHash(const QString &hash)
{
  _left_hash = hash;
  emit leftHashChanged();
}

void Card::setRightHash(const QString &hash)
{
  _right_hash = hash;
  emit rightHashChanged();
}
