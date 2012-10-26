/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "paintplugin.h"
#include "pathprocessor.h"
#include "iwebview.h"

void PaintPlugin::init(ICore *core, const QStringList &param __attribute__((__unused__)))
{
  core->loadLib("webview");
  IWebView *webView = qobject_cast<IWebView*>(core->getLib("webview"));
  if (!webView) return;
  auto webViewObject = webView->createWebViewObject("WebViewObject", this);
  QWidget *view = qobject_cast<QWidget*>(core->mainView());
  if (!view) return;
  auto paint = new Paint(view, this);
  core->addObject("Paint", paint);
  auto path_processor = new PathProcessor(this);

  core->addQml(":/plugin/qml/Draw.qml");
  core->addQml(":/plugin/qml/ModeBar.qml");
  core->addQml(":/plugin/qml/ToolBar.qml");

  webViewObject->addWebObject("paint", paint);
  webViewObject->addWebObject("path", path_processor);
}

Q_EXPORT_PLUGIN2(IPlugin, PaintPlugin)
