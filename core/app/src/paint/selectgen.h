/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SELECTGEN_H
#define SELECTGEN_H

#include "shapegen.h"

class SheetCanvas;

class SelectGen : public QObject, public ShapeGen
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(SelectGen)
public:
  explicit SelectGen(ISheetCanvas *canvas);
  ~SelectGen() override;
  void begin(const QPointF &p) override;
  void end(const QPointF &p) override;
  void move(const QPointF &p) override;
public slots:
  void onMoveBegin(int x, int y);
  void onMoveEnd();
  void onMove(int x, int y);
  void onScaleBegin(int x, int y, int mx1, int my1, int mx2, int my2);
  void onScaleEnd();
  void onScale(int x, int y);
  void onNeedUpdate();
  void onDel();
  void onDuplicate();
  void onToFront();
  void onToBack();
  void onColorChanged();
  void onBgcolorChanged();
private:
  SheetCanvas *_canvas_obj;
  QQuickItem *_container;
  QQuickItem *_select_rect;
  QList<Shape*> _selected;
  int _mx1;
  int _my1;
  int _mx2;
  int _my2;
  void updateRoundRect();
  void sortSelected();
};

#endif // SELECTGEN_H
