/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QRandomGenerator>
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
  auto *rng = QRandomGenerator::global();
  switch (rng->bounded(4))
  {
  case 0:
    _operation = "+";
    _left = rng->bounded(10) + 1;
    _right = rng->bounded(10) + 1;
    break;
  case 1:
    _operation = "-";
    _right = rng->bounded(9) + 1;
    _left = 10 - rng->bounded(10 - _right);
    break;
  case 2:
    _operation = "*";
    _left = rng->bounded(10) + 1;
    _right = rng->bounded(10) + 1;
    break;
  case 3:
    _operation = "/";
    _right = rng->bounded(10) + 1;
    _left = _right * (rng->bounded(10) + 1);
    break;
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
  else if (_operation == "/" && _right != 0)
    _result = _left / _right;
  else
    _result = 0;
}
