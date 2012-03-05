/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QDir>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtWebKit/QWebElement>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardcore.h"
#include "boarddraw.h"
#include "const.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow),
  core_(new BoardCore(this))
{
  ui_->setupUi(this);
  QWebPage * page = ui_->browser->page();
  QWebFrame * frame = page->currentFrame();
  frame->addToJavaScriptWindowObject(QString(CORE_OBJECT), core_);
  frame->addToJavaScriptWindowObject(QString(DRAW_OBJECT), core_->getDraw());
  frame->load(QUrl("qrc:/web/page.html"));
}

MainWindow::~MainWindow()
{
  delete ui_;
}

void MainWindow::chageMode(bool toggled)
{
  if (!toggled) return;
  QAction *mode = qobject_cast<QAction*>(sender());
  if (!mode) return;
  BoardDraw *draw = core_->getDraw();
  draw->setMode(mode->text());
}

void MainWindow::chageColor(bool toggled)
{
  if (!toggled) return;
  QAction *color = qobject_cast<QAction*>(sender());
  if (!color) return;
  BoardDraw *draw = core_->getDraw();
  draw->setColor(color->text());
}
