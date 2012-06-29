/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "paintplugin.h"

void PaintPlugin::init(ICore *core)
{
  QWidget *view = qobject_cast<QWidget*>(core->mainView());
  paint_ = new Paint(view, this);
  core->addObject("Paint", paint_);
  core->addWebObject("paint", paint_);
}

Q_EXPORT_PLUGIN2(IPlugin, PaintPlugin)
