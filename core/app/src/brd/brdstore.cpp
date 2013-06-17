/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFile>
#include <QCryptographicHash>
#include "brdstore.h"

using namespace std;

BrdObject::BrdObject(const QByteArray &data) :
  _data(data)
{
  QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Md5);
  _hash = QString::fromLatin1(hash.toHex());
}

BrdStore::BrdStore(QObject *parent) :
  QObject(parent),
  _store()
{
}

QByteArray BrdStore::getObject(const QString &hash)
{
  auto it = _store.find(hash);
  if (it == _store.cend())
  {
    return QByteArray();
  }
  return (*it).second->data();
}

QString BrdStore::getUrlString(const QString &hash)
{
  return "brd:" + hash;
}

QString BrdStore::addObject(const QByteArray &data)
{
  shared_ptr<BrdObject> obj = make_shared<BrdObject>(data);
  _store[obj->hash()] = obj;
  return obj->hash();
}

QString BrdStore::addFromFile(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly))
  {
    return QString();
  }
  QByteArray data = file.readAll();
  return addObject(data);
}

void BrdStore::clear()
{
  _store.clear();
}
