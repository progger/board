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
  Q_DISABLE_COPY_MOVE(Ellipse)
public:
  explicit Ellipse(QQuickItem *parent = nullptr, float thinkness = 0, QColor color = QColor(),
                   QColor bgcolor = QColor(Qt::transparent));
  ~Ellipse() override = default;
  void init(ISheetCanvas *canvas) override;
  bool checkIntersect(const QRectF &rect) override;
protected:
  void updateMainNode(QSGGeometryNode *node) override;
  void updateBackgroundNode(QSGGeometryNode *node) override;
  QString elementName() const override;
};

#endif // ELLIPSE_H
