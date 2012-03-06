/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "diffstack.h"

DiffStack::DiffStack(int capacity) :
  capacity_(capacity),
  list_()
{
}

DiffStack::~DiffStack()
{
  clear();
}

void DiffStack::push(DiffItem *item)
{
  list_.append(item);
  if (list_.size() > capacity_)
  {
    DiffItem *item = list_.takeFirst();
    delete item;
  }
}

DiffItem *DiffStack::pop()
{
  if (list_.isEmpty()) return NULL;
  return list_.takeLast();
}

void DiffStack::clear()
{
  while (!list_.isEmpty())
  {
    delete list_.takeLast();
  }
}
