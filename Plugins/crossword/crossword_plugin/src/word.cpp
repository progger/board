#include "word.h"

Word::Word(int x, int y, const QString &word, const QString &question, QObject *parent) :
  QObject(parent),
  x_(x),
  y_(y),
  length_(word.length()),
  word_(word),
  question_(question),
  state_(false)
{
}
