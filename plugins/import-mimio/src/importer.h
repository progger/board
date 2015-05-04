/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTER_H
#define IMPORTER_H

#include <QStack>
#include <QXmlStreamReader>
#include "shape.h"
#include "isheet.h"

class Importer
{
public:
  Importer();
  bool import(const QString &file_name);
private:
  QMap<QString, QByteArray> _files;
  QXmlStreamReader *_reader;
  ISheet *_sheet;
  ISheetCanvas *_canvas;
  QStack<QList<Shape*>> _group;
  bool openBookFiles();
  bool readPage();
  bool readLayer();

  bool readEllipse();
  bool readGroup();
  bool readImage();
  bool readRectangle();

  bool skipElement();
  QString convertColor(QString color);
  QString importFile(const QString &file_name);
  Shape *createShape(const QString &name);
  void fillShape(Shape *shape);
};

#endif // IMPORTER_H
