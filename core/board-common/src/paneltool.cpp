/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paneltool.h"

PanelTool::PanelTool(QQuickItem *parent) :
  QQuickItem(parent),
  _button_width(1),
  _button_height(1)
{
}

void PanelTool::setButtonX(int x)
{
  _button_x = x;
  emit buttonXChanged();
}

void PanelTool::setButtonY(int y)
{
  _button_y = y;
  emit buttonYChanged();
}

void PanelTool::setButtonWidth(int width)
{
  _button_width = width;
  emit buttonWidthChanged();
}

void PanelTool::setButtonHeight(int height)
{
  _button_height = height;
  emit buttonHeightChanged();
}
