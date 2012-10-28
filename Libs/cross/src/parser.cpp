/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QStringList>
#include "word.h"
#include "parser.h"

Parser::Parser(QObject *parent, QObjectList *words) :
  QObject(parent),
  words_(words),
  width_(0),
  height_(0)
{
}

bool Parser::parse(QTextStream *stream)
{
  width_ = 0;
  height_ = 0;
  while (!stream->atEnd())
  {
    auto line = stream->readLine();
    if (line.isEmpty() || line.startsWith("#")) continue;
    auto parts = line.split("\t");
    if (parts.length() != 5) return false;
    auto word = new Word(parent());
    bool ok = false;
    word->setX(parts.at(0).toInt(&ok));
    if (!ok) return false;
    word->setY(parts.at(1).toInt(&ok));
    if (!ok) return false;
    word->setDirection(parts.at(2).toInt(&ok));
    if (!ok) return false;
    word->setWord(parts.at(3));
    word->setQuestion(parts.at(4));
    words_->append(word);
    int end = word->x() + (word->direction() ? 0 : word->length()) + 1;
    if (width_ < end) width_ = end;
    end = word->y() + (word->direction() ? word->length() : 0) + 1;
    if (height_ < end) height_ = end;
  }
  return true;
}

void Parser::save(QTextStream *stream)
{
  for (auto word_obj : *words_)
  {
    Word *word = qobject_cast<Word*>(word_obj);
    *stream << word->x() << "\t" << word->y() << "\t" << word->direction() << "\t"
            << word->word() << "\t" << word->question() << endl;
  }
}
