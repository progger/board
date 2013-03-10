/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "webviewobject.h"
#include "webview.h"

Webview::Webview(QObject *parent) :
  QObject(parent)
{
}

void Webview::init(ICore *core)
{
  core_ = core;
}

IWebViewObject *Webview::createWebViewObject(const QString &name, QObject *parent)
{
  auto obj = new WebViewObject(parent);
  core_->addObject(name, obj);
  return obj;
}
