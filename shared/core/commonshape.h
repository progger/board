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
  Q_DISABLE_COPY_MOVE(CommonShape)
public:
  explicit CommonShape(QQuickItem *parent = nullptr, float thickness = 0, QColor color = QColor(),
                       QColor bgcolor = QColor(Qt::transparent));
  ~CommonShape() override = default;
  bool erase(const QRectF &beg, const QRectF &end);
  void updateClipHash();
protected:
  QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;
  virtual bool hasMainNode() { return true; }
  virtual bool hasBackgroundNode() { return true; }
  virtual void updateMainNode(QSGGeometryNode *) {}
  virtual void updateBackgroundNode(QSGGeometryNode *) {}
  virtual QRectF getFullInnerRect() const;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
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
