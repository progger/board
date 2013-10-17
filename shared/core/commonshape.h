/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef COMMONSHAPE_H
#define COMMONSHAPE_H

#include <QSGNode>
#include "shape.h"

class CommonShape : public Shape
{
  Q_OBJECT
public:
  explicit CommonShape(QQuickItem *parent = 0, float thickness = 0, QColor color = QColor(),
                       QColor background = QColor(Qt::transparent));
protected:
  virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;
  virtual void updateMainNode(QSGGeometryNode *node) = 0;
  virtual void updateBackgroundNode(QSGGeometryNode *node) = 0;
private:
  QSGGeometryNode *_main_node;
  QSGGeometryNode *_background_node;
};

#endif // COMMONSHAPE_H
