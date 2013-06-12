/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
  Q_OBJECT
public:
  explicit Line(QQuickItem *parent = 0, float thinkness = 0, QColor color = QColor());
  bool modeLtrb() const { return _mode_ltrb; }
public slots:
  void setModeLtrb(bool ltrb);
protected:
  virtual QSGNode *updatePaintNode(QSGNode *old_node, UpdatePaintNodeData *) override;
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *) override;
private:
  bool _mode_ltrb;
};

#endif // LINE_H
