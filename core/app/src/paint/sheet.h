/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SHEET_H
#define SHEET_H

#include <QQuickItem>
#include "sheetcanvas.h"
#include "isheet.h"

class Sheet : public QQuickItem, public ISheet
{
  Q_OBJECT
  Q_INTERFACES(ISheet)
  Q_PROPERTY(bool scrollable READ scrollable WRITE setScrollable NOTIFY scrollableChanged)
public:
  explicit Sheet(QQuickItem *parent = 0);

  // ISheet
  virtual ISheetCanvas *canvas() override;

  SheetCanvas *canvasObj() { return _canvas; }
  bool scrollable() const { return _scrollable; }
  void setScrollable(bool scrollable);
  void serialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects = nullptr);
  void deserialize(QXmlStreamReader *reader);
signals:
  void scrollableChanged();
protected:
  virtual void componentComplete() override;
private:
  SheetCanvas *_canvas;
  bool _scrollable;
};

#endif // SHEET_H
