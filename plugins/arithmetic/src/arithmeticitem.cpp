/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "arithmeticitem.h"

ArithmeticItem::ArithmeticItem(QObject *parent) :
  QObject(parent),
  _left(0),
  _right(0),
  _operation(),
  _result(0)
{
}

void ArithmeticItem::setLeft(int left)
{
  _left = left;
  updateResult();
  emit leftChanged();
  emit resultChanged();
}

void ArithmeticItem::setRight(int right)
{
  _right = right;
  updateResult();
  emit rightChanged();
  emit resultChanged();
}

void ArithmeticItem::setOperation(const QString &operation)
{
  _operation = operation;
  updateResult();
  emit operationChanged();
  emit resultChanged();
}

void ArithmeticItem::generate()
{
  switch (qrand() % 4)
  {
  case 0:
    _operation = "+";
    _left = qrand() % 10 + 1;
    _right = qrand() % 10 + 1;
    break;
  case 1:
    _operation = "-";
    _right = qrand() % 9 + 1;
    _left = 10 - qrand() % (10 - _right);
    break;
  case 2:
    _operation = "*";
    _left = qrand() % 10 + 1;
    _right = qrand() % 10 + 1;
  case 3:
    _operation = "/";
    _right = qrand() % 10 + 1;
    _left = _right * (qrand() % 10 + 1);
  }
  updateResult();
  emit leftChanged();
  emit rightChanged();
  emit operationChanged();
  emit resultChanged();
}

void ArithmeticItem::updateResult()
{
  if (_operation == "+")
    _result = _left + _right;
  else if (_operation == "-")
    _result = _left - _right;
  else if (_operation == "*")
    _result = _left * _right;
  else if (_operation == "/")
    _result = _left / _right;
  else
    _result = 0;
}
