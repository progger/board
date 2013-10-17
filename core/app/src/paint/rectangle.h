/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "commonshape.h"

class Rectangle : public CommonShape
{
  Q_OBJECT
public:
  explicit Rectangle(QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor(),
                     QColor background = QColor(Qt::transparent));
protected:
  virtual void updateMainNode(QSGGeometryNode *node) override;
  virtual void updateBackgroundNode(QSGGeometryNode *node) override;
  virtual QString elementName() const override;
};

#endif // RECTANGLE_H
