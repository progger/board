/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "panelaction.h"

PanelAction::PanelAction(QQuickItem *parent) :
  QQuickItem(parent),
  _button_width(1),
  _button_height(1)
{
}

void PanelAction::setButtonX(int x)
{
  _button_x = x;
  emit buttonXChanged();
}

void PanelAction::setButtonY(int y)
{
  _button_y = y;
  emit buttonYChanged();
}

void PanelAction::setButtonWidth(int width)
{
  _button_width = width;
  emit buttonWidthChanged();
}

void PanelAction::setButtonHeight(int height)
{
  _button_height = height;
  emit buttonHeightChanged();
}
