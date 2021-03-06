/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PARSER_H
#define PARSER_H

#include "iparser.h"

class Parser : public QObject, public IParser
{
  Q_OBJECT
  Q_INTERFACES(IParser)
public:
  explicit Parser(QObject *parent, QObjectList *words);
  bool parse(QIODevice *device);
  void save(QIODevice *device, QIODevice *svg_device);
  int width() { return width_; }
  int height() { return height_; }
private:
  QObjectList *words_;
  int width_;
  int height_;
};

#endif // PARSER_H
