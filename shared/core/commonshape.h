/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef COMMONSHAPE_H
#define COMMONSHAPE_H

#include <list>
#include <QSGNode>
#include "shape.h"

class CommonShape : public Shape
{
  Q_OBJECT
public:
  explicit CommonShape(QQuickItem *parent = 0, float thickness = 0, QColor color = QColor(),
                       QColor bgcolor = QColor(Qt::transparent));
  void erase(const QRectF &beg, const QRectF &end);
protected:
  virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;
  virtual void updateMainNode(QSGGeometryNode *node) = 0;
  virtual void updateBackgroundNode(QSGGeometryNode *node) = 0;
  virtual QRectF getFullInnerRect() const;
  virtual void innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *) override;
private slots:
  void onInnerRectChanged();
private:
  QSGGeometryNode *_main_node;
  QSGGeometryNode *_background_node;
  std::list<QRectF> _clips;
  QString _clips_hash;
  bool eraseRect(const QRectF &rect);
  void updateClipNode(QSGClipNode *node);
};

#endif // COMMONSHAPE_H
