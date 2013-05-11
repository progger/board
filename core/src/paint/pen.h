/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
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
  explicit Pen(QQuickItem *parent, float thinkness, QColor color);
  Points &points() { return _points; }
protected:
  virtual QSGNode *updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *) override;
private:
  Points _points;
};

#endif // PEN_H
