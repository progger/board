/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSSEDIT_H
#define CROSSEDIT_H

#include "icore.h"
#include "icross.h"

class Crossedit : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int width READ width NOTIFY updateWidth FINAL)
  Q_PROPERTY(int height READ height NOTIFY updateHeight FINAL)
  Q_PROPERTY(QObject *grid READ grid CONSTANT FINAL)
  Q_PROPERTY(QObjectList words READ words NOTIFY updateWords FINAL)
  Q_PROPERTY(int editingWordIndex READ editingWordIndex NOTIFY updateEditingWord FINAL)
  Q_PROPERTY(QString crossName READ crossName NOTIFY updateCrossName FINAL)
  Q_PROPERTY(QStringList fileList READ fileList NOTIFY updateFileList FINAL)
  Q_PROPERTY(bool fileListVisible READ fileListVisible NOTIFY updateFileList FINAL)
public:
  explicit Crossedit(QObject *parent, ICore *core, ICross *cross);
  int width() { return width_; }
  int height() { return height_; }
  QObject *grid() { return grid_->toQObject(); }
  QObjectList words() { return words_; }
  int editingWordIndex() { return editing_word_index_; }
  QString crossName() { return cross_name_; }
  QStringList fileList() { return file_list_; }
  bool fileListVisible() { return file_list_visible_; }
signals:
  void updateWidth();
  void updateHeight();
  void updateWords();
  void updateEditingWord();
  void updateCrossName();
  void updateFileList();
public slots:
  void hideHighlight();
  void highlightWord(QObject *word_obj);
  void highlightCell(QObject *cell_obj);
  void editWord(QObject *word_obj, QString text);
  void editCrossName(QString text);
  void rotateWord();
  void save();
  void open();
  void openFile(QString name);
private:
  ICore *core_;
  ICross *cross_;
  IParser *parser_;
  int width_;
  int height_;
  IGrid *grid_;
  QObjectList words_;
  IWord* editing_word_;
  int editing_word_index_;
  QString cross_name_;
  QDir cross_dir_;
  QStringList file_list_;
  bool file_list_visible_;
  void removeEmptyWords();
  void fillGrid();
  void normalize();
};

#endif // CROSSEDIT_H
