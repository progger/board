/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "tool.h"

Tool::Tool(const QString &name, const QString &section, const QString &url_string, QObject *parent) :
  QObject(parent),
  _name(name),
  _section(section),
  _url_string(url_string),
  _x(0),
  _y(0)
{
}

Tool::Tool(Tool *tool, QObject *parent) :
  QObject(parent),
  _name(tool->name()),
  _section(tool->section()),
  _url_string(tool->urlString()),
  _x(0),
  _y(0)
{
}

void Tool::setX(int x)
{
  _x = x;
  emit xChanged();
}

void Tool::setY(int y)
{
  _y = y;
  emit yChanged();
}
