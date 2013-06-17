/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "cell.h"

Cell::Cell(int x, int y, QObject *parent) :
  QObject(parent),
  x_(x),
  y_(y),
  type_(0),
  letter_(),
  highlight_(false),
  editing_(false),
  accepted_(false),
  error_(false)
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

void Cell::setError(bool error)
{
  if (error_ == error) return;
  error_ = error;
  emit updateError();
}

void Cell::setType(int type)
{
  if (type_ == type) return;
  type_ = type;
  emit updateType();
}
