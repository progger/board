/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <QObject>
#include "icross.h"
#include "igrid.h"
#include "iword.h"

class Crossword : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int width READ width NOTIFY updateWidth FINAL)
  Q_PROPERTY(int height READ height NOTIFY updateHeight FINAL)
  Q_PROPERTY(QObject *grid READ grid CONSTANT FINAL)
  Q_PROPERTY(QObjectList words READ words CONSTANT FINAL)
public:
  explicit Crossword(QObject *parent, ICross *cross);
  bool init(const QString &file_name);
  int width() { return width_; }
  int height() { return height_; }
  QObject *grid() { return grid_->toQObject(); }
  QObjectList words() { return words_; }
signals:
  void updateWidth();
  void updateHeight();
public slots:
  void hideHighlight();
  void highlightWord(QObject *word_obj);
  void highlightCell(QObject *cell_obj);
  void edit(QString key);
private:
  ICross *cross_;
  int width_;
  int height_;
  IGrid *grid_;
  QObjectList words_;
  IWord* editing_word_;
  int editing_pos_;
  void checkWord();
};

#endif // CROSSWORD_H
