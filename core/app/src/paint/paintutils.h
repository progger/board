/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINTUTILS_H
#define PAINTUTILS_H

#include "isheetcanvas.h"
#include "global.h"

template <class T> T * createItem(ISheetCanvas *canvas, QPointF pos)
{
  T *t = new T(canvas->container(), g_core->paint()->thickness(), g_core->paint()->color(),
               g_core->paint()->bgcolor());
  t->init(canvas);
  t->setPosition(pos);
  t->setZ(canvas->getZNext());
  return t;
}

int getSegCount(qreal r);

#endif // PAINTUTILS_H
