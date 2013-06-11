/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
  Q_OBJECT
public:
  explicit Ellipse(QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor());
protected:
  virtual QSGNode *updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *) override;
  virtual QString elementName() const override;
};

#endif // ELLIPSE_H
