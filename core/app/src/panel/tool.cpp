/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "tool.h"

Tool::Tool(ToolInfo *tool_info, QObject *parent) :
  ToolInfo(tool_info->name(), tool_info->section(), tool_info->component(), tool_info->width(), tool_info->height(), parent),
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
