/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef WEBVIEWOBJECT_H
#define WEBVIEWOBJECT_H

#include "iwebviewobject.h"

class WebViewObject : public QObject, public IWebViewObject
{
  Q_OBJECT
  Q_INTERFACES(IWebViewObject)
public:
  explicit WebViewObject(QObject *parent = 0);
  void addWebObject(const QString &name, QObject *obj);
signals:
  void addObject(QString name, QObject *obj);
};

#endif // WEBVIEWOBJECT_H
