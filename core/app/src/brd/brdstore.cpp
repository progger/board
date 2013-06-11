/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
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

QString BrdObject::urlString(const QString &hash)
{
  return "brd:" + hash;
}

BrdStore::BrdStore(QObject *parent) :
  QObject(parent),
  _store()
{
}

shared_ptr<BrdObject> BrdStore::getObject(const QString &hash) const
{
  auto it = _store.find(hash);
  if (it == _store.cend())
  {
    return nullptr;
  }
  return (*it).second;
}

void BrdStore::setObject(std::shared_ptr<BrdObject> obj)
{
  _store[obj->hash()] = obj;
}

QString BrdStore::addObject(QByteArray data)
{
  shared_ptr<BrdObject> obj = make_shared<BrdObject>(data);
  setObject(obj);
  return obj->hash();
}

void BrdStore::clear()
{
  _store.clear();
}

std::shared_ptr<BrdObject> BrdStore::fromFile(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly))
  {
    return nullptr;
  }
  QByteArray data = file.readAll();
  return make_shared<BrdObject>(data);
}
