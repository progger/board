/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "word.h"

Word::Word(QObject *parent) :
  QObject(parent),
  x_(0),
  y_(0),
  direction_(false),
  word_(QString::null),
  question_(QString::null),
  state_(false),
  highlight_(false),
  accepted_(false)
{
}

void Word::setX(int x)
{
  if (x_ == x) return;
  x_ = x;
  emit updateX();
}

void Word::setY(int y)
{
  if (y_ == y) return;
  y_ = y;
  emit updateY();
}

void Word::setDirection(bool direction)
{
  if (direction_ == direction) return;
  direction_ = direction;
  emit updateDirection();
}

void Word::setWord(QString word)
{
  if (word_ == word) return;
  word_ = word;
  emit updateWord();
}

void Word::setQuestion(QString question)
{
  if (question_ == question) return;
  question_ = question;
  emit updateQuestion();
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
