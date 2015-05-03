/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "shape.h"

Shape::Shape(QQuickItem *parent, float thickness, QColor color, QColor bgcolor) :
  QQuickItem(parent),
  _thickness(thickness),
  _color(color),
  _bgcolor(bgcolor)
{
  setFlag(QQuickItem::ItemHasContents);
  connect(this, SIGNAL(widthChanged()), SLOT(onWidthChanged()));
  connect(this, SIGNAL(heightChanged()), SLOT(onHeightChanged()));
}

void Shape::init(ISheetCanvas *canvas)
{
  _canvas = canvas;
  setParent(canvas->container());
  setParentItem(canvas->container());
}

void Shape::serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  writer->writeStartElement(elementName());
  writer->writeAttribute("shape_version", QString::number(1));
  writer->writeAttribute("x", QString::number(x() + _canvas->sheetPoint().x()));
  writer->writeAttribute("y", QString::number(y() + _canvas->sheetPoint().y()));
  writer->writeAttribute("z", QString::number(z()));
  writer->writeAttribute("width", QString::number(width()));
  writer->writeAttribute("height", QString::number(height()));
  writer->writeAttribute("innerWidth", QString::number(_inner_size.width()));
  writer->writeAttribute("innerHeight", QString::number(_inner_size.height()));
  writer->writeAttribute("thickness", QString::number(_thickness));
  writer->writeAttribute("color", QString("#%1").arg(_color.rgba(), 8, 16, QLatin1Char('0')));
  writer->writeAttribute("bgcolor", QString("#%1").arg(_bgcolor.rgba(), 8, 16, QLatin1Char('0')));
  innerSerialize(writer, brd_objects);
  writer->writeEndElement();
}

void Shape::deserialize(QXmlStreamReader *reader)
{
  auto attrs = reader->attributes();
  setX(attrs.value("x").toString().toDouble() - _canvas->sheetPoint().x());
  setY(attrs.value("y").toString().toDouble() - _canvas->sheetPoint().y());
  setZ(attrs.value("z").toString().toDouble());
  setSize(QSizeF(attrs.value("width").toString().toDouble(),
                 attrs.value("height").toString().toDouble()));
  setInnerSize(QSizeF(attrs.value("innerWidth").toString().toDouble(),
                      attrs.value("innerHeight").toString().toDouble()));
  setThickness(attrs.value("thickness").toString().toDouble());
  setColor(attrs.value("color").toString());
  QString bgcolor = attrs.value("bgcolor").toString();
  if (!bgcolor.isEmpty())
  {
    setBgcolor(bgcolor);
  }
  innerDeserialize(reader);
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
#include <QDebug>
void Shape::setColor(const QColor &color)
{
  _color = color;
  update();
  emit colorChanged();
}

void Shape::setBgcolor(const QColor &bgcolor)
{
  _bgcolor = bgcolor;
  update();
  emit bgcolorChanged();
}

void Shape::innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const
{
  Q_UNUSED(writer);
  Q_UNUSED(brd_objects);
}

void Shape::innerDeserialize(QXmlStreamReader *reader)
{
  Q_UNUSED(reader);
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
  return !(rect.right() < x() ||
           rect.left() > x() + width() ||
           rect.bottom() < y() ||
           rect.top() > y() + height());
}
