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

class Core;
typedef std::vector<QPointF> Points;

class Pen : public Shape
{
  Q_OBJECT
public:
  explicit Pen(Core *core, QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor());
  Points &points() { return _points; }
  void savePoints();
protected:
  virtual QSGNode *updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *) override;
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, SheetCanvas *, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader, SheetCanvas *) override;
private:
  Core *_core;
  Points _points;
  QString _hash;
};

#endif // PEN_H
