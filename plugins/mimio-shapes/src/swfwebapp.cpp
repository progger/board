/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "qhttpserver/qhttpserver.h"
#include "qhttpserver/qhttprequest.h"
#include "qhttpserver/qhttpresponse.h"
#include "global.h"
#include "swfwebapp.h"

const QString HtmlPrefix = "/html:";
const QString BrdPrefix = "/brd:";
const QString HtmlFmt = "<html><head></head><body topmargin=\"0\" bottommargin=\"0\" leftmargin=\"0\" rightmargin=\"0\"><object width=\"100%\" height=\"100%\" data=\"http://127.0.0.1:%0/brd:%1\" type=\"application/x-shockwave-flash\"></object></body></html>";

QWeakPointer<SwfWebApp> g_swf_web_app;

SwfWebApp::SwfWebApp(QObject *parent) :
  QObject(parent),
  _port(10000)
{
  QHttpServer *_server = new QHttpServer(this);
  connect(_server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
          this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

  while (_port < 20000 && !_server->listen(QHostAddress::LocalHost, _port));
}

void SwfWebApp::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
  QString path = req->path();
  QByteArray body;
  if (path.startsWith(HtmlPrefix))
  {
    QString hash = path.mid(HtmlPrefix.size());
    body = HtmlFmt.arg(_port).arg(hash).toUtf8();
  }
  else if (path.startsWith(BrdPrefix))
  {
    QString hash = path.mid(BrdPrefix.size());
    body = g_core->brdStore()->getObject(hash);
  }
  resp->setHeader("Content-Length", QString::number(body.size()));
  resp->writeHead(200);
  resp->end(body);
}
