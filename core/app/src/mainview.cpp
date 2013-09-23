/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QMessageBox>
#include "global.h"
#include "core.h"
#include "mainview.h"

MainView::MainView(QWindow *parent) :
  QQuickView(parent)
{
  g_core = new Core(this);
  setResizeMode(QQuickView::SizeRootObjectToView);
  setSource(QUrl("qrc:/core/qml/Board.qml"));
}

bool MainView::event(QEvent *ev)
{
  Core *core = static_cast<Core*>(g_core);
  if (ev->type() == QEvent::Close && core->hasChanges())
  {
    int ret = QMessageBox::question(nullptr, "Имеются несохранённые изменения", "Сохранить изменения?",
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                    QMessageBox::Save);
    switch (ret)
    {
      case QMessageBox::Save:
        core->saveBook();
        ev->accept();
        return true;
      case QMessageBox::Cancel:
        ev->accept();
        return true;
    }
  }
  return QQuickView::event(ev);
}
