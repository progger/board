/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFile>
#include <QCryptographicHash>
#include "brdstore.h"

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
  return _store.value(hash);
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
    id = *(_tmp_free.erase(_tmp_free.begin()));
  }
  _tmp_store[id] = data;
  _tmp_used.insert(id);
  return id;
}

void BrdStore::removeTempObject(int id)
{
  _tmp_store[id] = QByteArray();
  _tmp_used.remove(id);
  _tmp_free.insert(id);
}

QByteArray BrdStore::getTempObject(int id)
{
  return _tmp_store.value(id);
}

QString BrdStore::getTempUrl(int id)
{
  return "tmp:" + QString::number(id);
}

QString BrdStore::addObject(const QByteArray &data)
{
  QByteArray bin_hash = QCryptographicHash::hash(data, QCryptographicHash::Md5);
  QString hash = QString::fromLatin1(bin_hash.toHex());
  _store[hash] = data;
  return hash;
}

QString BrdStore::addFromFile(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly))
  {
    return {};
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
  return {};
}

void BrdStore::clear()
{
  _store.clear();
  _tmp_store.clear();
  _tmp_free.clear();
  _tmp_used.clear();
  _tmp_next = 1;
}
