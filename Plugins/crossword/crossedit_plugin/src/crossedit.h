/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSEDIT_H
#define CROSSEDIT_H

#include "icross.h"

class Crossedit : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int width READ width NOTIFY updateWidth FINAL)
  Q_PROPERTY(int height READ height NOTIFY updateHeight FINAL)
  Q_PROPERTY(QObject *grid READ grid CONSTANT FINAL)
  Q_PROPERTY(QObjectList words READ words NOTIFY updateWords FINAL)
  Q_PROPERTY(int editingWordIndex READ editingWordIndex NOTIFY updateEditingWord FINAL)
public:
  explicit Crossedit(QObject *parent, ICross *cross);
  int width() { return width_; }
  int height() { return height_; }
  QObject *grid() { return grid_->toQObject(); }
  QObjectList words() { return words_; }
  int editingWordIndex() { return editing_word_index_; }
signals:
  void updateWidth();
  void updateHeight();
  void updateWords();
  void updateEditingWord();
public slots:
  void hideHighlight();
  void highlightWord(QObject *word_obj);
  void highlightCell(QObject *cell_obj);
  void editWord(QObject *word_obj, QString text);
  void rotateWord();
private:
  ICross *cross_;
  int width_;
  int height_;
  IGrid *grid_;
  QObjectList words_;
  IWord* editing_word_;
  int editing_word_index_;
  void removeEmptyWords();
  void fillGrid();
};

#endif // CROSSEDIT_H
