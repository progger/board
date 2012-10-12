#include "cell.h"

Cell::Cell(int x, int y, int type, QObject *parent) :
  QObject(parent),
  x_(x),
  y_(y),
  type_(type),
  letter_(),
  highlight_(false)
{
}

void Cell::setLetter(const QString &letter)
{
  letter_ = letter;
  emit updateLetter();
}

void Cell::setHighlight(bool highlight)
{
  highlight_ = highlight;
  emit updateHighlight();
}
