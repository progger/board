/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PAINTUTILS_H
#define PAINTUTILS_H

#include "sheetcanvas.h"
#include "paint.h"

template <class T> T * createItem(SheetCanvas *canvas, QPointF pos)
{
  T *t = new T(canvas->container(), canvas->paint()->thickness(), canvas->paint()->color());
  t->setPosition(pos);
  return t;
}

int getSegCount(qreal r);

#endif // PAINTUTILS_H
