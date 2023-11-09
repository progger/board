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
  Q_DISABLE_COPY_MOVE(Rectangle)
public:
  explicit Rectangle(QQuickItem *parent = nullptr, float thinkness = 0, QColor color = QColor(),
                     QColor bgcolor = QColor(Qt::transparent));
  ~Rectangle() override = default;
protected:
  void updateMainNode(QSGGeometryNode *node) override;
  void updateBackgroundNode(QSGGeometryNode *node) override;
  QString elementName() const override;
};

#endif // RECTANGLE_H
