/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BRDSTORE_H
#define BRDSTORE_H

#include <memory>
#include <map>
#include <QObject>

class BrdObject
{
public:
  BrdObject(const QString file_name, const QString &mime_type, const QByteArray &data);
  QString hash() const { return _hash; }
  QString fileName() const { return _file_name; }
  QString mimeType() const { return _mime_type; }
  QByteArray data() const { return _data; }
  QString urlString() const;
private:
  QString _hash;
  QString _file_name;
  QString _mime_type;
  QByteArray _data;
};

class BrdStore : public QObject
{
  Q_OBJECT
public:
  explicit BrdStore(QObject *parent = 0);
  std::shared_ptr<BrdObject> getObject(const QString &hash) const;
  void setObject(std::shared_ptr<BrdObject> obj);
  static std::shared_ptr<BrdObject> fromFile(const QString &file_name);
private:
  std::map<QString, std::shared_ptr<BrdObject>> _store;
};

#endif // BRDSTORE_H
