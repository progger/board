/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IWEBVIEW_H
#define IWEBVIEW_H

#include <QObject>
#include "iwebviewobject.h"

class IWebView {
public:
  virtual ~IWebView() {}
  virtual IWebViewObject * createWebViewObject(const QString &name, QObject *parent) = 0;
};

Q_DECLARE_INTERFACE(IWebView, "Board.webview.IWebView/1.0")

#endif // IWEBVIEW_H
