/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BOARDDRAW_H
#define BOARDDRAW_H

#include <QObject>
#include <QWebElement>
#include "diff/diffstack.h"

class BoardDraw : public QObject
{
  Q_OBJECT
public:
  explicit BoardDraw(QObject *parent, const QWebElement &drawElement);
  bool getState() { return state_; }
  QString getMode() { return mode_; }
  QString getColor() { return color_; }
  Q_PROPERTY(bool state READ getState WRITE setState)
  Q_PROPERTY(QString mode READ getMode WRITE setMode)
  Q_PROPERTY(QString color READ getColor WRITE setColor)

signals:
  void modeChanged();

public slots:
  void undo();
  void redo();
  void setState(bool state);
  void setMode(const QString &mode);
  void setColor(const QString &color) { color_ = color; }

private:
  QWebElement drawElement_;
  bool state_;
  QString mode_;
  QString color_;
  DiffStack undoStack_;
  DiffStack redoStack_;
  QString lastDraw_;
  void pushUndoStack();
  void undoRedo(DiffStack *stack1, DiffStack *stack2);
};

#endif // BOARDDRAW_H
