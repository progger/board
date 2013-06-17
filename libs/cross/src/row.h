/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ROW_H
#define ROW_H

#include <QObject>

class Row : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QObjectList cells READ cells NOTIFY updateCells FINAL)
public:
  explicit Row(QObject *parent = 0);
  ~Row();
  void fill(int y, int width);
  QObjectList cells() { return cells_; }
signals:
  void updateCells();
public slots:
  void hideHighlight();
private:
  QObjectList cells_;
};

#endif // ROW_H
