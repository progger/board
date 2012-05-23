/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef PARAMARRAY_H
#define PARAMARRAY_H

#include <QVector>

class ParamArray : public QVector<qreal>
{
public:
  ParamArray() : QVector() {}
  ParamArray(int size) : QVector(size) {}
  ParamArray(int size, const qreal &value) : QVector(size, value) {}
  ParamArray(const ParamArray &other) : QVector(other) {}
};

#endif // PARAMARRAY_H
