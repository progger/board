/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paintplugin.h"
#include "pathprocessor.h"
#include "iwebview.h"

void PaintPlugin::init(ICore *core, const QStringList &param __attribute__((__unused__)))
{
  QObject *obj = core->loadLib("webview");
  IWebView *webView = qobject_cast<IWebView*>(obj);
  if (!webView) return;
  auto webViewObject = webView->createWebViewObject("WebViewObject", this);
  auto paint = new Paint(this);
  core->addObject("Paint", paint);
  auto path_processor = new PathProcessor(this);

  core->addQml("qrc:/plugin/paint/qml/Draw.qml");
  core->addQml("qrc:/plugin/paint/qml/ModeBar.qml");
  core->addQml("qrc:/plugin/paint/qml/ToolBar.qml");

  webViewObject->addWebObject("paint", paint);
  webViewObject->addWebObject("path", path_processor);
}
