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
#include "const.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::MainWindow),
  core_(new BoardCore(this))
{
  ui_->setupUi(this);
  connect(ui_->actionPen, SIGNAL(toggled(bool)), SLOT(chageMode()));
  connect(ui_->actionMove, SIGNAL(toggled(bool)), SLOT(chageMode()));
  connect(ui_->actionColor, SIGNAL(triggered()), SLOT(chageColor()));

  QWebPage * page = ui_->browser->page();
  QWebFrame * frame = page->currentFrame();
  QDir dir(QString(WEB_DIR));
  QString page_file = dir.filePath(QString(PAGE_FILE_NAME));
  frame->addToJavaScriptWindowObject(QString(CORE_OBJECT), core_);
  frame->load(QUrl(page_file));
}

MainWindow::~MainWindow()
{
  delete ui_;
}

void MainWindow::chageMode()
{
  if (ui_->actionPen->isChecked())
    core_->setMode(QString(MODE_PEN));
  else if (ui_->actionMove->isChecked())
    core_->setMode(QString(MODE_MOVE));
}

void MainWindow::chageColor()
{
  if (core_->getColor() == QString("black"))
    core_->setColor(QString("red"));
  else if (core_->getColor() == QString("red"))
    core_->setColor(QString("green"));
  else if (core_->getColor() == QString("green"))
    core_->setColor(QString("blue"));
  else if (core_->getColor() == QString("blue"))
    core_->setColor(QString("black"));
}
