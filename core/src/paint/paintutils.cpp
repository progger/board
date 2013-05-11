/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "paintutils.h"

int getSegCount(qreal r)
{
  const qreal z = 0.5;  // Коэффициент гладкости
  qreal a = acos(1 - z / r);  // Половина сектора
  return int(ceil(M_PI / a / 4) + 0.1) * 4; // Количество сегментов кратно 4
}

