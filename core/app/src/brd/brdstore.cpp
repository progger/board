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
  _store(),
  _tmp_store(),
  _tmp_free(),
  _tmp_used(),
  _tmp_next(1)
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
  return !hash.isEmpty() ? "brd:" + hash : hash;
}

int BrdStore::addTempObject(const QByteArray &data)
{
  int id;
  if (_tmp_free.empty())
  {
    id = _tmp_next++;
  }
  else
  {
    id = *(_tmp_free.erase(_tmp_free.cbegin()));
  }
  _tmp_store[id] = data;
  _tmp_used.insert(id);
  return id;
}

void BrdStore::removeTempObject(int id)
{
  _tmp_store[id] = QByteArray();
  _tmp_used.erase(id);
  _tmp_free.insert(id);
}

QByteArray BrdStore::getTempObject(int id)
{
  auto it = _tmp_store.find(id);
  if (it == _tmp_store.cend())
  {
    return QByteArray();
  }
  return (*it).second;
}

QString BrdStore::getTempUrl(int id)
{
  return "tmp:" + QString::number(id);
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

QString BrdStore::addFromUrl(const QUrl &url)
{
  if (url.isLocalFile())
  {
    QString file_name = url.toLocalFile();
    return addFromFile(file_name);
  }
  //TODO
  return QString();
}

void BrdStore::clear()
{
  _store.clear();
}
