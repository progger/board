/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "sheet.h"

Sheet::Sheet(QQuickItem *parent) :
  QQuickItem(parent),
  _canvas(nullptr),
  _scrollable(true),
  _color(Qt::white),
  _image_hash(),
  _image_mode(0)
{
}

void Sheet::setScrollable(bool scrollable)
{
  _scrollable = scrollable;
  emit scrollableChanged();
}

void Sheet::setColor(QColor color)
{
  _color = color;
  emit colorChanged();
}

QString Sheet::imageSource() const
{
  return g_core->brdStore()->getUrlString(_image_hash);
}

void Sheet::setImageHash(const QString &image_hash)
{
  _image_hash = image_hash;
  emit imageSourceChanged();
}

void Sheet::setImageMode(int image_mode)
{
  _image_mode = image_mode;
  emit imageModeChanged();
}

void Sheet::serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects)
{
  writer->writeStartElement("sheet");
  writer->writeAttribute("version", QString::number(1));
  writer->writeAttribute("scrollable", QString::number(_scrollable));
  writer->writeAttribute("color", QString("#%1").arg(_color.rgba(), 8, 16, QLatin1Char('0')));
  if (!_image_hash.isEmpty())
  {
    writer->writeAttribute("imageHash", _image_hash);
  }
  writer->writeAttribute("imageMode", QString::number(_image_mode));
  writer->writeAttribute("view_x", QString::number(_canvas->sheetPoint().x()));
  writer->writeAttribute("view_y", QString::number(_canvas->sheetPoint().y()));
  writer->writeAttribute("view_width", QString::number(_canvas->width() / _canvas->zoom()));
  writer->writeAttribute("view_height", QString::number(_canvas->height() / _canvas->zoom()));
  _canvas->serialize(writer, brd_objects);
  writer->writeEndElement();
  if (!_image_hash.isEmpty() && brd_objects)
  {
    brd_objects->insert(_image_hash);
  }
}

void Sheet::deserialize(QXmlStreamReader *reader)
{
  if (reader->tokenType() != QXmlStreamReader::StartElement || reader->name() != "sheet") return;
  auto attrs = reader->attributes();
  int version = attrs.value("version").toInt();
  if (version >= 1)
  {
    setScrollable(attrs.value("scrollable").toInt());
    setColor(attrs.value("color").toString());
    _canvas->setSheetPoint(attrs.value("view_x").toDouble(), attrs.value("view_y").toDouble());
    qreal view_height = attrs.value("view_height").toDouble();
    qreal zoom = view_height > 0 ? _canvas->height() / view_height : 1;
    _canvas->setZoom(zoom);
  }
  setImageHash(attrs.value("imageHash").toString());
  setImageMode(attrs.value("imageMode").toInt());
  _canvas->deserialize(reader);
}

void Sheet::copySettings(Sheet *sheet)
{
  if (sheet == this) return;
  setScrollable(sheet->scrollable());
  setColor(sheet->color());
  setImageHash(sheet->imageHash());
  setImageMode(sheet->imageMode());
}

void Sheet::selectImage(const QUrl &file_url)
{
  QString file_name = file_url.toLocalFile();
  _image_hash = g_core->brdStore()->addFromFile(file_name);
  emit imageSourceChanged();
}

void Sheet::deleteImage()
{
  _image_hash = QString();
  emit imageSourceChanged();
}

ISheetCanvas *Sheet::canvas()
{
  return _canvas;
}

void Sheet::componentComplete()
{
  QQuickItem::componentComplete();
  _canvas = findChild<SheetCanvas*>("sheetCanvas");
  Q_ASSERT(_canvas);
}
