/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QWebFrame>
#include "boardcore.h"
#include "boarddraw.h"
#include "const.h"

BoardCore::BoardCore(QObject *parent, QWebFrame *frame) :
  QObject(parent),
  frame_(frame)
{
  frame_->addToJavaScriptWindowObject(QString(CORE_OBJECT), this);
}

void BoardCore::readyToWork()
{
  QWebElement drawElement = frame_->findFirstElement(QString(DRAW_SELECTOR));
  draw_ = new BoardDraw(this, drawElement);
  frame_->addToJavaScriptWindowObject(QString(DRAW_OBJECT), draw_);
  draw_->setMode(QString(MODE_PEN));
  draw_->setColor(QString("black"));
}
