/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "iweblib.h"
#include "webviewobject.h"

WebViewObject::WebViewObject(QObject *parent) :
  QObject(parent)
{
}

void WebViewObject::addWebObject(const QString &name, QObject *obj)
{
  emit addObject(name, obj);
}

void WebViewObject::addWebLib(QObject *libObj)
{
  IWebLib * lib = qobject_cast<IWebLib*>(libObj);
  lib->init(this);
}
