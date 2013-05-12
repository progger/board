/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paint.h"

Paint::Paint(QObject *parent) :
  QObject(parent),
  _mode("pen"),
  _thickness(3),
  _color("#000000"),
  _font_size(24),
  _selected(false),
  _can_undo(false),
  _can_redo(false)
{
}

void Paint::setMode(const QString &mode)
{
  _mode = mode;
  emit modeChanged();
}

void Paint::setThickness(float thickness)
{
  _thickness = thickness;
  emit thicknessChanged();
}

void Paint::setColor(const QColor &color)
{
  _color = color;
  emit colorChanged();
}

void Paint::setFontSize(int font_size)
{
  _font_size = font_size;
  emit fontSizeChanged();
}

void Paint::setSelected(bool selected)
{
  _selected = selected;
  emit selectedChanged();
}

void Paint::setCanUndo(bool can_undo)
{
  _can_undo = can_undo;
  emit canUndoChanged();
}

void Paint::setCanRedo(bool can_redo)
{
  _can_redo = can_redo;
  emit canRedoChanged();
}
