/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PEN_H
#define PEN_H

#include <memory>
#include <vector>
#include "commonshape.h"

typedef std::vector<QPointF> Points;

class Pen : public CommonShape
{
  Q_OBJECT
public:
  explicit Pen(QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor(),
               QColor bgcolor = QColor(Qt::transparent));
  Points &points() { return _points; }
  void savePoints();
  virtual bool checkIntersect(const QRectF &rect) override;
protected:
  virtual bool hasBackgroundNode() override { return false; }
  virtual void updateMainNode(QSGGeometryNode *node) override;
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader) override;
private:
  Points _points;
  QString _hash;
};

#endif // PEN_H
