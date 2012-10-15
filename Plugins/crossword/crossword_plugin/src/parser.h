/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PARSER_H
#define PARSER_H

#include <QStringList>

class Parser
{
public:
  Parser(QString data);
  bool checkEnd() { return iter_ != end_; }
  bool read(QString &str);
  bool readTo(QString str);
private:
  QStringList lines_;
  QStringList::const_iterator iter_;
  QStringList::const_iterator end_;
};

#endif // PARSER_H
