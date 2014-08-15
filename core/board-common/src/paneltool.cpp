/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paneltool.h"

PanelTool::PanelTool(QQuickItem *parent) :
  QQuickItem(parent),
  _tool_width(1),
  _tool_height(1)
{
}

void PanelTool::setToolWidth(int width)
{
  _tool_width = width;
  emit toolWidthChanged();
}

void PanelTool::setToolHeight(int height)
{
  _tool_height = height;
  emit toolHeightChanged();
}
