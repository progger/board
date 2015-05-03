/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "commonshape.h"

class Ellipse : public CommonShape
{
  Q_OBJECT
public:
  explicit Ellipse(QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor(),
                   QColor bgcolor = QColor(Qt::transparent));
  virtual void init(ISheetCanvas *canvas) override;
  virtual bool checkIntersect(const QRectF &rect) override;
protected:
  virtual void updateMainNode(QSGGeometryNode *node) override;
  virtual void updateBackgroundNode(QSGGeometryNode *node) override;
  virtual QString elementName() const override;
};

#endif // ELLIPSE_H
