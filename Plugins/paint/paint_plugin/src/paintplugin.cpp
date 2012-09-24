/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "paintplugin.h"
#include "pathprocessor.h"

void PaintPlugin::init(ICore *core, const QStringList &param __attribute__((__unused__)))
{
  QWidget *view = qobject_cast<QWidget*>(core->mainView());
  Paint *paint = new Paint(view, this);
  PathProcessor *path_processor = new PathProcessor(this);
  core->addObject("Paint", paint);
  core->addWebObject("paint", paint);
  core->addWebObject("path", path_processor);
  core->addQml("qrc:/plugin/qml/ModeBar.qml");
  core->loadWebPage("qrc:/plugin/web/page.html");
}

Q_EXPORT_PLUGIN2(IPlugin, PaintPlugin)
