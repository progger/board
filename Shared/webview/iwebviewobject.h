/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IWEBVIEWOBJECT_H
#define IWEBVIEWOBJECT_H

#include <QObject>

class IWebViewObject {
public:
  virtual ~IWebViewObject() {}
  virtual void addWebObject(const QString &name, QObject *obj) = 0;
};

Q_DECLARE_INTERFACE(IWebViewObject, "Board.webview.IWebViewObject/1.0")

#endif // IWEBVIEWOBJECT_H
