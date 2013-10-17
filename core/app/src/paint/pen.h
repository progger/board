/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PEN_H
#define PEN_H

#include <memory>
#include <vector>
#include "shape.h"

typedef std::vector<QPointF> Points;

class Pen : public Shape
{
  Q_OBJECT
public:
  explicit Pen(QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor(),
               QColor background = QColor(Qt::transparent));
  Points &points() { return _points; }
  void savePoints();
  virtual bool checkIntersect(const QRectF &rect) override;
protected:
  virtual QSGNode *updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *) override;
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *) override;
private:
  Points _points;
  QString _hash;
};

#endif // PEN_H
