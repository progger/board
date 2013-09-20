/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINTUTILS_H
#define PAINTUTILS_H

#include "isheetcanvas.h"
#include "global.h"
#include "paint.h"

template <class T> T * createItem(ISheetCanvas *canvas, QPointF pos)
{
  T *t = new T(canvas->container(), g_core->paint()->thickness(), g_core->paint()->color());
  t->setPosition(pos);
  t->setZ(canvas->getZNext());
  return t;
}

int getSegCount(qreal r);

#endif // PAINTUTILS_H
