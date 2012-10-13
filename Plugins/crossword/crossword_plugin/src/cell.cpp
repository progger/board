#include "cell.h"

Cell::Cell(int x, int y, int type, QObject *parent) :
  QObject(parent),
  x_(x),
  y_(y),
  type_(type),
  letter_(),
  highlight_(false),
  editing_(false),
  accepted_(false)
{
}

void Cell::setLetter(const QString &letter)
{
  if (letter_ == letter) return;
  letter_ = letter;
  emit updateLetter();
}

void Cell::setHighlight(bool highlight)
{
  if (highlight_ == highlight) return;
  highlight_ = highlight;
  emit updateHighlight();
}

void Cell::setEditing(bool editing)
{
  if (editing_ == editing) return;
  editing_ = editing;
  emit updateEditing();
}

void Cell::setAccepted(bool accepted)
{
  if (accepted_ == accepted) return;
  accepted_ = accepted;
  emit updateAccepted();
}
