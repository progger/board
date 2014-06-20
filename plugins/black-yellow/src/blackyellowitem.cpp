/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "blackyellowitem.h"

BlackYellowItem::BlackYellowItem(QObject *parent) :
  QObject(parent),
  _question(),
  _answer()
{
}

void BlackYellowItem::setQuestion(const QString &question)
{
  _question = question;
  emit questionChanged();
}

void BlackYellowItem::setAnswer(const QString &answer)
{
  _answer = answer;
  emit answerChanged();
}
