/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "strstack.h"

StrStack::StrStack() :
  _stack()
{
}

void StrStack::push(const QByteArray &str)
{
  _stack.push(str);
}

QByteArray StrStack::top() const
{
  if (_stack.empty()) return QByteArray();
  return _stack.top();
}

QByteArray StrStack::pop()
{
  if (_stack.empty()) return QByteArray();
  QByteArray result = _stack.top();
  _stack.pop();
  return result;
}

void StrStack::clear()
{
  while (!_stack.empty()) _stack.pop();
}

bool StrStack::empty() const
{
  return _stack.empty();
}
