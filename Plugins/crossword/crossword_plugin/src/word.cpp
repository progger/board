#include "word.h"

Word::Word(int x, int y, bool direction, const QString &word, const QString &question, QObject *parent) :
  QObject(parent),
  x_(x),
  y_(y),
  direction_(direction),
  length_(word.length()),
  word_(word),
  question_(question),
  state_(false),
  highlight_(false),
  accepted_(false)
{
}

void Word::setState(bool state)
{
  if (state_ == state) return;
  state_ = state;
  emit updateState();
}

void Word::setHighlight(bool highlight)
{
  if (highlight_ == highlight) return;
  highlight_ = highlight;
  emit updateHighlight();
}

void Word::setAccepted(bool accepted)
{
  if (accepted_ == accepted) return;
  accepted_ = accepted;
  emit updateAccepted();
}
