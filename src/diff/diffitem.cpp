/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <algorithm>
#include "diffitem.h"

DiffItem::DiffItem(const QString &str1, const QString &str2)
{
  QString::const_iterator beg_iter1 = str1.begin();
  QString::const_iterator beg_iter2 = str2.begin();
  QString::const_iterator end_iter1 = str1.end();
  QString::const_iterator end_iter2 = str2.end();
  while ((beg_iter1 < end_iter1) &&
         (beg_iter2 < end_iter2) &&
         (*beg_iter1 == *beg_iter2))
  {
    beg_iter1++;
    beg_iter2++;
  }
  while ((end_iter1 > beg_iter1) &&
         (end_iter2 > beg_iter2) &&
         (*--end_iter1 == *--end_iter2));
  begin_ = beg_iter1 - str1.begin();
  size_ = end_iter1 - beg_iter1;
  int size2 = end_iter2 - beg_iter2;
  str_ = QString(beg_iter2, size2);
}

QString DiffItem::apply(const QString &str)
{
  QString::const_iterator iter = str.begin();
  QString result(iter, begin_);
  result += str_;
  iter += begin_ + size_;
  QString tail(iter, str.end() - iter);
  result += tail;
  return result;
}
