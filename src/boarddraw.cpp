/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "boarddraw.h"

BoardDraw::BoardDraw(QObject *parent, const QWebElement &drawElement) :
  QObject(parent),
  drawElement_(drawElement),
  state_(false),
  mode_(),
  undoStack_(256),
  redoStack_(256)
{
  lastDraw_ = drawElement_.toInnerXml();
}

void BoardDraw::setMode(const QString &mode)
{
  mode_ = mode;
  modeChanged();
}

void BoardDraw::pushUndoStack()
{
  QString str = drawElement_.toInnerXml();
  if (str == lastDraw_) return;
  DiffItem *diff = new DiffItem(str, lastDraw_);
  undoStack_.push(diff);
  redoStack_.clear();
  lastDraw_ = str;
}

void BoardDraw::undoRedo(DiffStack *stack1, DiffStack *stack2)
{
  DiffItem *item1 = stack1->pop();
  if (item1 == NULL) return;
  QString str = item1->apply(lastDraw_);
  DiffItem *item2 = new DiffItem(str, lastDraw_);
  stack2->push(item2);
  lastDraw_ = str;
  drawElement_.setInnerXml(lastDraw_);
  delete item1;
}

void BoardDraw::setState(bool state)
{
  state_ = state;
  if (!state)
  {
    pushUndoStack();
  }
}

void BoardDraw::undo()
{
  undoRedo(&undoStack_, &redoStack_);
}

void BoardDraw::redo()
{
  undoRedo(&redoStack_, &undoStack_);
}
