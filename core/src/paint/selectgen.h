/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SELECTGEN_H
#define SELECTGEN_H

#include "shapegen.h"
#include "vector"

class SelectGen : public QObject, public ShapeGen
{
  Q_OBJECT
public:
  explicit SelectGen(SheetCanvas *canvas);
  virtual ~SelectGen() override;
  virtual void begin(const QPointF &p) override;
  virtual void end(const QPointF &p) override;
  virtual void move(const QPointF &p) override;
public slots:
  void onMoveBegin(int x, int y);
  void onMoveEnd();
  void onMove(int x, int y);
  void onScaleBegin(int x, int y, int mx1, int my1, int mx2, int my2);
  void onScaleEnd();
  void onScale(int x, int y);
  void onSheetPointChanged();
  void onDel();
  void onDuplicate();
private:
  QQuickItem *_select_rect;
  std::vector<Shape*> _selected;
  int _mx1;
  int _my1;
  int _mx2;
  int _my2;
  void updateRoundRect();
  QPointF getRectPoint(const QPointF &p);
};

#endif // SELECTGEN_H
