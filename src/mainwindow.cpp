/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QDir>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "const.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QWebPage * page = ui->browser->page();
  QWebFrame * frame = page->currentFrame();
  QDir dir(QString(WEB_DIR));
  QString page_file = dir.filePath(QString(PAGE_FILE_NAME));
  frame->load(QUrl(page_file));
}

MainWindow::~MainWindow()
{
  delete ui;
}
