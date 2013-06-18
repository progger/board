/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTDOC_H
#define IMPORTDOC_H

#include <QObject>

class ImportDoc : public QObject
{
  Q_OBJECT
public:
  explicit ImportDoc(QObject *parent = 0);
public slots:
  void importDoc();
};

#endif // IMPORTDOC_H
