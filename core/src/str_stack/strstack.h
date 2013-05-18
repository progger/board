/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef STRSTACK_H
#define STRSTACK_H

#include <stack>
#include <QByteArray>

class StrStack
{
public:
  StrStack();
  void push(const QByteArray &str);
  QByteArray top() const;
  QByteArray pop();
  void clear();
  bool empty() const;
private:
  std::stack<QByteArray> _stack;
};

#endif // STRSTACK_H
