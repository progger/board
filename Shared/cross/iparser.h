/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICROSSPARSER_H
#define ICROSSPARSER_H

#include <QObject>
#include <QTextStream>

class IParser {
public:
  virtual ~IParser() {}
  virtual bool parse(QTextStream *stream) = 0;
  virtual void save(QTextStream *stream) = 0;
  virtual int width() = 0;
  virtual int height() = 0;
};

Q_DECLARE_INTERFACE(IParser, "Board.cross.IParser/1.0")

#endif // ICROSSPARSER_H
