/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PEN_H
#define PEN_H

#include "commonshape.h"

using Points = QVector<QPointF>;

class Pen : public CommonShape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(Pen)
public:
  explicit Pen(QQuickItem *parent = nullptr, float thinkness = 0, QColor color = QColor(),
               QColor bgcolor = QColor(Qt::transparent));
  ~Pen() override = default;
  Points &points() { return _points; }
  void savePoints();
  bool checkIntersect(const QRectF &rect) override;
protected:
  bool hasBackgroundNode() override { return false; }
  void updateMainNode(QSGGeometryNode *node) override;
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  Points _points;
  QString _hash;
};

#endif // PEN_H
