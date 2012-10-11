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
