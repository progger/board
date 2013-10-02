/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ISHEET_H
#define ISHEET_H

#include "isheetcanvas.h"

class ISheet {
public:
  virtual ~ISheet() {}
  virtual ISheetCanvas *canvas() = 0;
};

Q_DECLARE_INTERFACE(ISheet, "board.core.ISheet")

#endif // ISHEET_H
