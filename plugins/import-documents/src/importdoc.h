/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTDOC_H
#define IMPORTDOC_H

#include <QObject>
#include <QTemporaryDir>

class ImportDoc : public QObject
{
  Q_OBJECT
public:
  explicit ImportDoc(QObject *parent = 0);
public slots:
  void importDoc();
private:
  QString convert(const QString &file_name, QTemporaryDir *dir);
};

#endif // IMPORTDOC_H
