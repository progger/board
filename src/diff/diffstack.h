/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef DIFFSTACK_H
#define DIFFSTACK_H

#include <QList>
#include "diffitem.h"

class DiffStack
{
public:
  DiffStack(int capacity);
  ~DiffStack();
  void push(DiffItem *item);
  DiffItem *pop();
  void clear();

private:
  int capacity_;
  QList<DiffItem*> list_;
};

#endif // DIFFSTACK_H
