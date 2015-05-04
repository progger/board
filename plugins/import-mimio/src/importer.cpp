/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <quazip/quazipfile.h>
#include "global.h"
#include "importer.h"

Importer::Importer() :
  _files(),
  _reader(nullptr),
  _sheet(nullptr),
  _canvas(nullptr),
  _group()
{
}

bool Importer::import(const QString &file_name)
{
  QuaZip zip(file_name);
  if (!zip.open(QuaZip::mdUnzip))
  {
    g_core->showError(QString("Не удалось открыть %1: error %2").arg(file_name).arg(zip.getZipError()));
    return false;
  }
  for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile())
  {
    QuaZipFile zip_file(&zip);
    if (!zip_file.open(QIODevice::ReadOnly))
    {
      g_core->showError(QString("Не удалось открыть файл Mimio: %1").arg(zip_file.getZipError()));
      return false;
    }
    QByteArray data = zip_file.readAll();
    _files[zip.getCurrentFileName()] = data;
  }
  if (!openBookFiles())
  {
    g_core->showError("Файл Mimio имеет неверный формат");
    return false;
  }
  return true;
}

bool Importer::openBookFiles()
{
  QByteArray data = _files["objects.xml"];
  if (data.isEmpty()) return false;
  QXmlStreamReader reader(data);
  reader.readNextStartElement();
  if (reader.name() != "MIMIO") return false;
  reader.readNextStartElement();
  if (reader.name() != "DOCUMENT") return false;
  _reader = &reader;
  while (reader.readNextStartElement())
  {
    if (reader.name() != "PAGE") return false;
    _sheet = g_core->addSheet();
    _sheet->setScrollable(false);
    _canvas = _sheet->canvas();
    if (!readPage()) return false;
  }
  return true;
}

bool Importer::readPage()
{
  QXmlStreamAttributes attrs = _reader->attributes();
  if (attrs.hasAttribute("FILL"))
  {
    _sheet->setColor(convertColor(attrs.value("FILL").toString()));
  }
  if (attrs.hasAttribute("BACKGROUND"))
  {
    QString hash = importFile(attrs.value("BACKGROUND").toString());
    _sheet->setImageHash(hash);
    _sheet->setImageMode(0); //TODO: BACKGROUNDMODE
  }
  if (attrs.hasAttribute("WIDTH") && attrs.hasAttribute("HEIGHT"))
  {
    qreal view_width = attrs.value("WIDTH").toDouble();
    qreal view_height = attrs.value("HEIGHT").toDouble();
    QQuickItem *canvas_obj = dynamic_cast<QQuickItem*>(_canvas);
    Q_ASSERT(canvas_obj);
    qreal zoom = view_height > 0 ? canvas_obj->height() / view_height : 1;
    qreal dx = (canvas_obj->width() / zoom - view_width) / 2;
    _canvas->setSheetPoint(dx, 0);
    _canvas->setZoom(zoom);
  }

  while (_reader->readNextStartElement())
  {
    QStringRef name = _reader->name();
    if (name == "LAYER")
    {
      _group.clear();
      _group.push(QList<Shape*>());
      if (!readLayer()) return false;
    }
    else
    {
      if (!skipElement()) return false;
    }
  }
  return true;
}

bool Importer::readLayer()
{
  while (_reader->readNextStartElement())
  {
    QStringRef name = _reader->name();
    if (name == "ELLIPSE")
    {
      if (!readEllipse()) return false;
    }
    else if (name == "GROUP")
    {
      if (!readGroup()) return false;
    }
    else if (name == "IMAGE")
    {
      if (!readImage()) return false;
    }
    else if (name == "RECTANGLE")
    {
      if (!readRectangle()) return false;
    }
    else
    {
      if (!skipElement()) return false;
    }
  }
  return true;
}

bool Importer::readEllipse()
{
  Shape *shape = createShape("ellipse");
  if (!shape) return skipElement();
  fillShape(shape);
  return skipElement();
}

bool Importer::readGroup()
{
  QXmlStreamAttributes attrs = _reader->attributes();
  qreal gx = attrs.value("X").toDouble() + _canvas->sheetPoint().x();
  qreal gy = attrs.value("Y").toDouble() + _canvas->sheetPoint().y();
  _group.push(QList<Shape*>());
  bool result = readLayer();
  QList<Shape*> list = _group.pop();
  int count = list.size();
  if (count > 0)
  {
    Shape *shape = list[0];
    qreal mx = shape->x();
    qreal my = shape->y();
    for (int i = 1; i < count; ++i)
    {
      shape = list[i];
      if (shape->x() < mx) mx = shape->x();
      if (shape->y() < my) my = shape->y();
    }
    qreal dx = gx - mx;
    qreal dy = gy - my;
    for (int i = 0; i < count; ++i)
    {
      shape = list[i];
      shape->setX(shape->x() + dx);
      shape->setY(shape->y() + dy);
      _group.top().append(shape);
    }
  }
  return result;
}

bool Importer::readImage()
{
  QXmlStreamAttributes attrs = _reader->attributes();
  QString hash = importFile(attrs.value("FILE").toString());
  if (hash.isEmpty()) return skipElement();
  Shape *shape = createShape("image");
  if (!shape) return skipElement();
  fillShape(shape);
  shape->setProperty("hash", hash);
  return skipElement();
}

bool Importer::readRectangle()
{
  Shape *shape = createShape("rectangle");
  if (!shape) return skipElement();
  fillShape(shape);
  return skipElement();
}

bool Importer::skipElement()
{
  QStringRef name = _reader->name();
  while (true)
  {
    auto token = _reader->readNext();
    if (token == QXmlStreamReader::Invalid) return false;
    if (token == QXmlStreamReader::EndElement && _reader->name() == name) return true;
  }
}

QString Importer::convertColor(QString color)
{
  return color.replace("0x", "#");
}

QString Importer::importFile(const QString &file_name)
{
  QByteArray data = _files[file_name];
  if (data.isEmpty())
  {
    return QString();
  }
  return g_core->brdStore()->addObject(data);
}

Shape *Importer::createShape(const QString &name)
{
  Shape *shape = g_core->paint()->createShape(name, _canvas);
  if (shape)
  {
    _group.top().append(shape);
  }
  return shape;
}

void Importer::fillShape(Shape *shape)
{
  QXmlStreamAttributes attrs = _reader->attributes();
  shape->setX(attrs.value("X").toDouble() + _canvas->sheetPoint().x());
  shape->setY(attrs.value("Y").toDouble() + _canvas->sheetPoint().y());
  QSizeF size(attrs.value("WIDTH").toDouble(), attrs.value("HEIGHT").toDouble());
  shape->setSize(size);
  shape->setInnerSize(size);
  if (attrs.hasAttribute("LINEWIDTH"))
  {
    shape->setThickness(attrs.value("LINEWIDTH").toDouble());
  }
  if (attrs.hasAttribute("LINECOLOR"))
  {
    shape->setColor(convertColor(attrs.value("LINECOLOR").toString()));
  }
  if (attrs.hasAttribute("FILLCOLOR"))
  {
    shape->setBgcolor(convertColor(attrs.value("FILLCOLOR").toString()));
  }
}
