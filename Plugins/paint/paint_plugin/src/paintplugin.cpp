/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paintplugin.h"
#include "pathprocessor.h"

void PaintPlugin::init(ICore *core, const QStringList &param __attribute__((__unused__)))
{
  auto paint = new Paint(this);
  core->addObject("Paint", paint);
  auto path_processor = new PathProcessor(this);
  core->addObject("PathProcessor", path_processor);
  core->addQml("qrc:/plugin/paint/qml/Sheet.qml");
  core->addQml("qrc:/plugin/paint/qml/ModeBar.qml");
  core->addQml("qrc:/plugin/paint/qml/ToolBar.qml");
}
