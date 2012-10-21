/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef WEBVIEW_H
#define WEBVIEW_H

#include "iexternal.h"
#include "iwebview.h"

class Webview : public QObject, public IExternal, public IWebView
{
  Q_OBJECT
  Q_INTERFACES(IExternal)
  Q_INTERFACES(IWebView)
public:
  explicit Webview(QObject *parent = 0);
  virtual ~Webview() {}
  virtual void init(ICore *core);
  virtual IWebViewObject * createWebViewObject(const QString &name, QObject *parent);
private:
  ICore *core_;
};

#endif // WEBVIEW_H
