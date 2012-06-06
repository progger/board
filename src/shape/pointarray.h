/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef POINTARRAY_H
#define POINTARRAY_H

#include <QVector>
#include <QVector2D>

class PointArray : public QVector<QVector2D>
{
public:
  PointArray() : QVector() {}
  PointArray(int size) : QVector(size) {}
  PointArray(int size, const QVector2D &value) : QVector(size, value) {}
  PointArray(const PointArray &other) : QVector(other) {}
};

#endif // POINTARRAY_H
