/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef QPOINTFLIST_H
#define QPOINTFLIST_H

#include <QVector>
#include <QPointF>

class PointArray : public QVector<QPointF>
{
public:
  PointArray() : QVector() {}
  PointArray(int size) : QVector(size) {}
  PointArray(int size, const QPointF &value) : QVector(size, value) {}
  PointArray(const PointArray &other) : QVector(other) {}
};

#endif // QPOINTFLIST_H
