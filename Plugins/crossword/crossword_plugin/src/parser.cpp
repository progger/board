/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "parser.h"

Parser::Parser(QString data)
{
  lines_ = data.split("\n");
  iter_ = lines_.constBegin();
  end_ = lines_.end();
}

bool Parser::read(QString &str)
{
  if (!checkEnd()) return false;
  str = (*iter_++).trimmed();
  return true;
}

bool Parser::readTo(QString str)
{
  if (!checkEnd()) return false;
  while ((*iter_++).trimmed() != str)
  {
    if (!checkEnd()) return false;
  }
  return true;
}
