/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMPORTDOC_H
#define IMPORTDOC_H

#include <QSharedPointer>
#include <QObject>
#include <QTemporaryDir>

class ImportDoc : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(ImportDoc)
public:
  explicit ImportDoc(QObject *parent = nullptr);
  ~ImportDoc() override = default;
public slots:
  void importDoc(const QUrl &file_url);
private:
  static QString convert(const QString &file_name, const QSharedPointer<QTemporaryDir> &dir);
};

#endif // IMPORTDOC_H
