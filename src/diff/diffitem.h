/*
 * Copyright (C) 2011 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef DIFFITEM_H
#define DIFFITEM_H

#include <QObject>

class DiffItem
{
public:
  DiffItem(const QString &str1, const QString &str2);
  QString apply(const QString &str);

private:
  int begin_;
  int size_;
  QString str_;
};

#endif // DIFFITEM_H
