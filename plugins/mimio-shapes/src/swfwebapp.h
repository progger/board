/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SWFWEBAPP_H
#define SWFWEBAPP_H

#include <QObject>
#include <QWeakPointer>
#include "qhttpserver/qhttpserverfwd.h"

class SwfWebApp : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(SwfWebApp)
public:
  explicit SwfWebApp(QObject *parent = nullptr);
  ~SwfWebApp() override = default;
  int port() const { return _port; }
private slots:
  void handleRequest(QHttpRequest *req, QHttpResponse *resp);
private:
  QHttpServer *_server;
  int _port;
};

extern QWeakPointer<SwfWebApp> g_swf_web_app;

#endif // SWFWEBAPP_H
