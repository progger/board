/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class BoardCore;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void chageMode(bool toggled);
  void chageColor(bool toggled);
  void undo();
  void redo();

private:
  Ui::MainWindow *ui_;
  BoardCore *core_;
};

#endif // MAINWINDOW_H
