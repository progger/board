/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "pathprocessor.h"

PathProcessor::PathProcessor(QObject *parent) :
  QObject(parent),
  arx_(),
  ary_()
{
}

bool PathProcessor::process(QVariantList arx, QVariantList ary)
{
  clear();
  return false;
}

void PathProcessor::clear()
{
  arx_.clear();
  ary_.clear();
}
