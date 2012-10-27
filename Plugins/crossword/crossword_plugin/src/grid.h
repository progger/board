/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef GRID_H
#define GRID_H

#include "cell.h"

class Grid : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QObjectList rows READ rows CONSTANT FINAL)
  Q_PROPERTY(int width READ width NOTIFY updateGrid FINAL)
  Q_PROPERTY(int height READ height NOTIFY updateGrid FINAL)
public:
  explicit Grid(QObject *parent = 0);
  void fill(int width, int height);
  QObjectList rows() { return rows_; }
  int width() { return width_; }
  int height() { return height_; }
  Cell *getCell(int x, int y);
signals:
  void updateGrid();
public slots:
  void hideHighlight();
private:
  QObjectList rows_;
  int width_;
  int height_;
};

#endif // GRID_H
