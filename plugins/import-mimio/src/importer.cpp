/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <quazip5/quazipfile.h>
#include <QDomDocument>
#include "global.h"
#include "importer.h"

Importer::Importer() :
  _files(),
  _sheet(nullptr),
  _canvas(nullptr),
  _group(),
  _rtf_converter()
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
  QDomDocument xml_doc;
  if (!xml_doc.setContent(data)) return false;
  QDomElement root = xml_doc.documentElement();
  if (root.tagName() != "MIMIO") return false;
  QDomNodeList nodes = root.elementsByTagName("DOCUMENT");
  if (nodes.size() != 1) return false;
  QDomElement document = nodes.at(0).toElement();
  nodes = document.elementsByTagName("PAGE");
  int count = nodes.size();
  for (int i = 0; i < count; ++i)
  {
    QDomElement page = nodes.at(i).toElement();
    _sheet = g_core->addSheet();
    _sheet->setScrollable(false);
    _canvas = _sheet->canvas();
    processPage(page);
  }
  return true;
}

void Importer::processPage(const QDomElement &page)
{
  QString fill = page.attribute("FILL");
  if (!fill.isEmpty())
  {
    _sheet->setColor(convertColor(fill));
  }
  QString background = page.attribute("BACKGROUND");
  if (!background.isEmpty())
  {
    QString hash = importFile(background);
    _sheet->setImageHash(hash);
    _sheet->setImageMode(0); //TODO: BACKGROUNDMODE
  }
  qreal view_width = page.attribute("WIDTH").toDouble();
  qreal view_height = page.attribute("HEIGHT").toDouble();
  if (view_width && view_height)
  {
    QQuickItem *canvas_obj = dynamic_cast<QQuickItem*>(_canvas);
    Q_ASSERT(canvas_obj);
    qreal zoom = view_height > 0 ? canvas_obj->height() / view_height : 1;
    qreal dx = (canvas_obj->width() / zoom - view_width) / 2;
    _canvas->setZoom(zoom);
    _canvas->setViewPoint(-dx, 0);
  }

  QDomNodeList nodes = page.elementsByTagName("LAYER");
  int count = nodes.size();
  for (int i = 0; i < count; ++i)
  {
    QDomElement layer = nodes.at(i).toElement();
    _group.clear();
    _group.push(QList<Shape*>());
    processLayer(layer);
  }
}

void Importer::processLayer(const QDomElement &layer)
{
  QDomNodeList nodes = layer.childNodes();
  int count = nodes.size();
  for (int i = 0; i < count; ++i)
  {
    QDomElement element = nodes.at(i).toElement();
    QString name = element.tagName();
    if (name == "ELLIPSE")
    {
      processEllipse(element);
    }
    else if (name == "GROUP")
    {
      processGroup(element);
    }
    else if (name == "IMAGE")
    {
      processImage(element);
    }
    else if (name == "MULTIMEDIA")
    {
      processMultimedia(element);
    }
    else if (name == "RECTANGLE")
    {
      processRectangle(element);
    }
    else if (name == "TEXT")
    {
      processText(element);
    }
  }
}

void Importer::processEllipse(const QDomElement &element)
{
  Shape *shape = createShape("ellipse");
  if (!shape) return;
  fillShape(element, shape);
}

void Importer::processGroup(const QDomElement &element)
{
  qreal gx = element.attribute("X").toDouble();
  qreal gy = element.attribute("Y").toDouble();
  _group.push(QList<Shape*>());
  processLayer(element);
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
}

void Importer::processImage(const QDomElement &element)
{
  QString hash = importFile(element.attribute("FILE"));
  if (hash.isEmpty()) return;
  Shape *shape = createShape("image");
  if (!shape) return;
  fillShape(element, shape);
  shape->setProperty("hash", hash);
}

void Importer::processMultimedia(const QDomElement &element)
{
  QString file = element.attribute("FILE");
  if (!file.isEmpty())
  {
    QFileInfo file_info(file);
    QString suffix = file_info.suffix();
    if (suffix == "swf")
    {
      QString hash = importFile(file);
      if (hash.isEmpty()) return;
      Shape *shape = createShape("swf-player");
      if (!shape) return;
      fillShape(element, shape);
      shape->setProperty("hash", hash);
      return;
    }
    //TODO
  }
  else
  {
    QString id = element.attribute("ID");
    if (!id.isEmpty())
    {
      QDir app_dir = QDir(QCoreApplication::applicationDirPath());
      QDir mimio_dir = QDir(app_dir.filePath("mimio"));
      if (mimio_dir.exists())
      {
        QString file_name = mimio_dir.filePath(id) + ".swf";
        QString hash = g_core->brdStore()->addFromFile(file_name);
        if (hash.isEmpty()) return;
        Shape *shape = createShape("swf-player");
        if (!shape) return;
        fillShape(element, shape);
        shape->setProperty("hash", hash);
      }
    }
  }
}

void Importer::processRectangle(const QDomElement &element)
{
  Shape *shape = createShape("rectangle");
  if (!shape) return;
  fillShape(element, shape);
}

void Importer::processText(const QDomElement &element)
{
  QByteArray data = getFile(element.attribute("FILE"));
  if (data.isEmpty()) return;
  QString text = _rtf_converter.convert(data);
  if (text.isEmpty()) return;
  Shape *shape = createShape("mimio-text");
  if (!shape) return;
  fillShape(element, shape);
  shape->setProperty("text", text);
}

QString Importer::convertColor(QString color)
{
  return color.replace("0x", "#");
}

QByteArray Importer::getFile(const QString &file_name)
{
  auto it = _files.constFind(file_name);
  if (it != _files.cend())
  {
    return it.value();
  }
  QString locale = QLocale::system().name().toLower();
  QFileInfo file_info(file_name);
  QString name = file_info.completeBaseName() + "[" + locale + "]." + file_info.suffix();
  it = _files.constFind(file_name);
  if (it != _files.cend())
  {
    return it.value();
  }
  name = file_info.completeBaseName() + "[";
  it = _files.cbegin();
  while (it != _files.cend())
  {
    if (it.key().startsWith(name))
    {
      return it.value();
    }
    ++it;
  }
  return QByteArray();
}

QString Importer::importFile(const QString &file_name)
{
  QByteArray data = getFile(file_name);
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

void Importer::fillShape(const QDomElement &element, Shape *shape)
{
  shape->setX(element.attribute("X").toDouble());
  shape->setY(element.attribute("Y").toDouble());
  QSizeF size(element.attribute("WIDTH").toDouble(), element.attribute("HEIGHT").toDouble());
  shape->setSize(size);
  shape->setInnerSize(size);
  if (element.hasAttribute("LINEWIDTH"))
  {
    shape->setThickness(element.attribute("LINEWIDTH").toDouble());
  }
  if (element.hasAttribute("LINECOLOR"))
  {
    shape->setColor(convertColor(element.attribute("LINECOLOR")));
  }
  if (element.hasAttribute("FILLCOLOR"))
  {
    shape->setBgcolor(convertColor(element.attribute("FILLCOLOR")));
  }

  QDomNodeList nodes = element.elementsByTagName("METADATA");
  int count = nodes.size();
  for (int i = 0; i < count; ++i)
  {
    QDomElement metadata = nodes.at(i).toElement();
    QDomNodeList data_nodes = metadata.elementsByTagName("DATA");
    int data_count = data_nodes.size();
    for (int j = 0; j < data_count; ++j)
    {
      QDomElement data = data_nodes.at(i).toElement();
      QString name = data.attribute("NAME");
      if (name == "LOCKED")
      {
        shape->setLocked(true);
      }
    }
  }
}
