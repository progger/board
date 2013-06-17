/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QTextStream>
#include <QXmlStreamWriter>
#include <QStringList>
#include <QVector>
#include "word.h"
#include "parser.h"

Parser::Parser(QObject *parent, QObjectList *words) :
  QObject(parent),
  words_(words),
  width_(0),
  height_(0)
{
}

bool Parser::parse(QIODevice *device)
{
  QTextStream stream(device);
  width_ = 0;
  height_ = 0;
  while (!stream.atEnd())
  {
    auto line = stream.readLine();
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

void Parser::save(QIODevice *device, QIODevice *svg_device)
{
  width_ = 0;
  height_ = 0;
  QTextStream stream(device);
  for (auto word_obj : *words_)
  {
    Word *word = qobject_cast<Word*>(word_obj);
    int x = word->x();
    int y = word->y();
    bool direction = word->direction();
    int length = word->length();
    stream << x << "\t" << y << "\t" << direction << "\t"
           << word->word() << "\t" << word->question() << endl;
    if (direction)
      y += length;
    else
      x += length;
    if (x > width_) width_ = x;
    if (y > height_) height_ = y;
  }

  QVector<QVector<bool>> grid(height_, QVector<bool>(width_, false));
  for (auto word_obj : *words_)
  {
    Word *word = qobject_cast<Word*>(word_obj);
    int x = word->x();
    int y = word->y();
    bool direction = word->direction();
    int length = word->length();
    for (int i = 0; i < length; i++)
    {
      grid[y][x] = true;
      if (direction)
        y++;
      else
        x++;
    }
  }

  int size = (qMax(width_, height_) + 2) * 16;
  int dx = (size - width_ * 16) / 2;
  int dy = (size - height_ * 16) / 2;
  QXmlStreamWriter writer(svg_device);
  writer.setAutoFormatting(true);
  writer.writeStartDocument();
  writer.writeDTD("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">");
  writer.writeStartElement("svg");
  writer.writeAttribute("version", "1.1");
  writer.writeDefaultNamespace("http://www.w3.org/2000/svg");
  writer.writeNamespace("http://www.w3.org/1999/xlink", "xlink");
  writer.writeAttribute("width", QString::number(size));
  writer.writeAttribute("height", QString::number(size));
  for (int y = 0; y < height_; y++)
    for (int x = 0; x < width_; x++)
    {
      if (!grid[y][x]) continue;
      writer.writeStartElement("rect");
      writer.writeAttribute("x", QString::number(x * 16 + dx));
      writer.writeAttribute("y", QString::number(y * 16 + dy));
      writer.writeAttribute("width", "16");
      writer.writeAttribute("height", "16");
      writer.writeAttribute("style", "fill:white;stroke:black;stroke-width:3px");
      writer.writeEndElement();
    }
  writer.writeEndElement();
  writer.writeEndDocument();
}
