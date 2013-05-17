/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include "brdstore.h"

using namespace std;

BrdObject::BrdObject(const QString file_name, const QString &mime_type, const QByteArray &data) :
  _file_name(file_name),
  _mime_type(mime_type),
  _data(data)
{
  QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Md5);
  _hash = QString::fromLatin1(hash.toHex());
}

QString BrdObject::urlString() const
{
  return "brd:" + _hash;
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

std::shared_ptr<BrdObject> BrdStore::fromFile(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly))
  {
    return nullptr;
  }
  QByteArray data = file.readAll();

  QFileInfo file_info(file_name);
  QString ext = file_info.suffix();
  QString mime_type;
  if (ext == "png" || ext == "jpeg" || ext == "tiff" ||
      ext == "gif" || ext == "svg") {
    mime_type = ext;
  }
  else if (ext == "jpg") {
    mime_type = "jpg";
  }
  else if (ext == "tif") {
    mime_type = "tiff";
  }

  return make_shared<BrdObject>(file_info.fileName(), mime_type, data);
}
