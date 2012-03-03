/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BOARDCORE_H
#define BOARDCORE_H

#include <QObject>

class BoardDraw;

class BoardCore : public QObject
{
  Q_OBJECT
public:
  explicit BoardCore(QObject *parent = 0);
  BoardDraw *getDraw() { return draw_; }
  Q_PROPERTY(BoardDraw *draw READ getDraw)

signals:

public slots:
  void readyToWork();

private:
  BoardDraw *draw_;
};

#endif // BOARDCORE_H
