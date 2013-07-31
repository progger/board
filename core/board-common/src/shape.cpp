/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "shape.h"

Shape::Shape(QQuickItem *parent, float thickness, QColor color) :
  QQuickItem(parent),
  _thickness(thickness),
  _color(color)
{
  connect(this, SIGNAL(widthChanged()), SLOT(onWidthChanged()));
  connect(this, SIGNAL(heightChanged()), SLOT(onHeightChanged()));
}

void Shape::serialize(QXmlStreamWriter *writer, ISheetCanvas *canvas, std::set<QString> *brd_objects) const
{
  writer->writeStartElement(elementName());
  writer->writeAttribute("x", QString::number(x() + canvas->sheetPoint().x()));
  writer->writeAttribute("y", QString::number(y() + canvas->sheetPoint().y()));
  writer->writeAttribute("width", QString::number(width()));
  writer->writeAttribute("height", QString::number(height()));
  writer->writeAttribute("innerWidth", QString::number(_inner_size.width()));
  writer->writeAttribute("innerHeight", QString::number(_inner_size.height()));
  writer->writeAttribute("thickness", QString::number(_thickness));
  writer->writeAttribute("color", _color.name());
  innerSerialize(writer, canvas, brd_objects);
  writer->writeEndElement();
}

void Shape::deserialize(QXmlStreamReader *reader, ISheetCanvas *canvas)
{
  auto attrs = reader->attributes();
  setX(attrs.value("x").toString().toDouble() - canvas->sheetPoint().x());
  setY(attrs.value("y").toString().toDouble() - canvas->sheetPoint().y());
  setSize(QSizeF(attrs.value("width").toString().toDouble(),
                 attrs.value("height").toString().toDouble()));
  setInnerSize(QSizeF(attrs.value("innerWidth").toString().toDouble(),
                      attrs.value("innerHeight").toString().toDouble()));
  setThickness(attrs.value("thickness").toString().toDouble());
  setColor(attrs.value("color").toString());
  innerDeserialize(reader, canvas);
  reader->readNext();
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

bool Shape::checkIntersect(const QRectF &rect)
{
  return !(rect.x() + rect.width() < x() ||
           rect.x() > x() + width() ||
           rect.y() + rect.height() < y() ||
           rect.y() > y() + height());
}
