/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include "shape.h"

class ImageWrapper : public Shape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(ImageWrapper)
  Q_PROPERTY(QString hash READ hash WRITE setHash NOTIFY hashChanged)
  Q_PROPERTY(QString source READ source NOTIFY hashChanged)
public:
  explicit ImageWrapper(QQuickItem *parent = nullptr);
  ~ImageWrapper() override = default;
  QString hash() const { return _hash; }
  QString source() const;
public slots:
  void setHash(const QString &hash);
signals:
  void hashChanged();
protected:
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QString _hash;
};

#endif // IMAGEWRAPPER_H
