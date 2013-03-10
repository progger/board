/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "parser.h"
#include "word.h"
#include "grid.h"
#include "cross.h"

Cross::Cross(QObject *parent) :
  QObject(parent)
{
}

void Cross::init(ICore *core  __attribute__((__unused__)))
{
}

IParser *Cross::createParser(QObject *parent, QObjectList *words)
{
  return new Parser(parent, words);
}

IWord *Cross::createWord(QObject *parent)
{
  return new Word(parent);
}

IGrid *Cross::createGrid(QObject *parent)
{
  return new Grid(parent);
}
