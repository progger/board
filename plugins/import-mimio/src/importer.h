/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTER_H
#define IMPORTER_H

#include <QStack>
#include <QDomElement>
#include "shape.h"
#include "isheet.h"
#include "rtfconverter.h"

class Importer
{
public:
  Importer();
  bool import(const QString &file_name);
private:
  QMap<QString, QByteArray> _files;
  ISheet *_sheet;
  ISheetCanvas *_canvas;
  QStack<QList<Shape*>> _group;
  RtfConverter _rtf_converter;

  bool openBookFiles();
  void processPage(const QDomElement &page);
  void processLayer(const QDomElement &layer);

  void processEllipse(const QDomElement &element);
  void processGroup(const QDomElement &element);
  void processImage(const QDomElement &element);
  void processMultimedia(const QDomElement &element);
  void processRectangle(const QDomElement &element);
  void processText(const QDomElement &element);

  QString convertColor(QString color);
  QByteArray getFile(const QString &file_name);
  QString importFile(const QString &file_name);
  Shape *createShape(const QString &name);
  void fillShape(const QDomElement &element, Shape *shape);
};

#endif // IMPORTER_H
