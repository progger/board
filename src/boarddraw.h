/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BOARDDRAW_H
#define BOARDDRAW_H

#include <QObject>
#include "diff/diffstack.h"

class BoardDraw : public QObject
{
  Q_OBJECT
public:
  explicit BoardDraw(QObject *parent);

public slots:
  void undo();
  void redo();

private:
  DiffStack undoStack_;
  DiffStack redoStack_;
  QString lastDraw_;
  void pushUndoStack();
  void undoRedo(DiffStack *stack1, DiffStack *stack2);
};

#endif // BOARDDRAW_H
