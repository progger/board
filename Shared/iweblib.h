/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IWEBLIB_H
#define IWEBLIB_H

#include <QObject>
#include "iwebviewobject.h"

class IWebLib {
public:
  virtual ~IWebLib() {}
  virtual void init(IWebViewObject *web_view_object) = 0;
};

Q_DECLARE_INTERFACE(IWebLib, "Board.IWebLib/1.0")

#endif // IWEBLIB_H
