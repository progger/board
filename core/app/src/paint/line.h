/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef LINE_H
#define LINE_H

#include "commonshape.h"

class Line : public CommonShape
{
  Q_OBJECT
public:
  explicit Line(QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor(),
                QColor bgcolor = QColor(Qt::transparent));
  QPointF p1() { return _p1; }
  QPointF p2() { return _p2; }
  virtual bool checkIntersect(const QRectF &rect) override;
  static int computeCohenOutcode(const QPointF &p, const QRectF &rect);
  static bool isLineIntersectRect(const QPointF &p1, const QPointF &p2, const QRectF &rect);
public slots:
  void setP1(const QPointF &p);
  void setP2(const QPointF &p);
protected:
  virtual bool hasBackgroundNode() override { return false; }
  virtual void updateMainNode(QSGGeometryNode *node) override;
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *) override;
private:
  QPointF _p1;
  QPointF _p2;
};

#endif // LINE_H
