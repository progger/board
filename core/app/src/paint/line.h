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
  Q_DISABLE_COPY_MOVE(Line)
public:
  explicit Line(QQuickItem *parent = nullptr, float thinkness = 0, QColor color = QColor(),
                QColor bgcolor = QColor(Qt::transparent));
  ~Line() override = default;
  QPointF p1() { return _p1; }
  QPointF p2() { return _p2; }
  bool checkIntersect(const QRectF &rect) override;
  static int computeCohenOutcode(const QPointF &p, const QRectF &rect);
  static bool isLineIntersectRect(const QPointF &p1, const QPointF &p2, const QRectF &rect);
public slots:
  void setP1(const QPointF &p);
  void setP2(const QPointF &p);
protected:
  bool hasBackgroundNode() override { return false; }
  void updateMainNode(QSGGeometryNode *node) override;
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QPointF _p1;
  QPointF _p2;
};

#endif // LINE_H
