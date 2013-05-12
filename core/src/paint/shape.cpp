/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "shape.h"

Shape::Shape(QQuickItem *parent) :
  QQuickItem(parent),
  _thickness(),
  _color()
{
  connect(this, SIGNAL(widthChanged()), SLOT(onWidthChanged()));
  connect(this, SIGNAL(heightChanged()), SLOT(onHeightChanged()));
}

Shape::Shape(QQuickItem *parent, float thickness, QColor color) :
  Shape(parent)
{
  _thickness = thickness;
  _color = color;
}

qreal Shape::scalex() const
{
  return _inner_size.width() ? width() / _inner_size.width() : 1;
}

qreal Shape::scaley() const
{
  return _inner_size.height() ? height() / _inner_size.height() : 1;
}

void Shape::setInnerSize(const QSizeF &size)
{
  _inner_size = size;
  emit innerSizeChanged();
  emit scalexChanged();
  emit scaleyChanged();
}

void Shape::setThickness(int thickness)
{
  _thickness = thickness;
  emit thicknessChanged();
}

void Shape::setColor(const QColor &color)
{
  _color = color;
  emit colorChanged();
}

void Shape::onWidthChanged()
{
  emit scalexChanged();
}

void Shape::onHeightChanged()
{
  emit scaleyChanged();
}
