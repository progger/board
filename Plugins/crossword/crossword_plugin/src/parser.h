/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QTextStream>

class Parser : public QObject
{
  Q_OBJECT
public:
  explicit Parser(QObject *parent, QObjectList *words);
  bool parse(QTextStream *stream);
  void save(QTextStream *stream);
  int width() { return width_; }
  int height() { return height_; }
private:
  QObjectList *words_;
  int width_;
  int height_;
};

#endif // PARSER_H
