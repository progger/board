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
  Q_PROPERTY(QString hash READ hash WRITE setHash NOTIFY hashChanged)
  Q_PROPERTY(QString source READ source NOTIFY hashChanged)
public:
  explicit ImageWrapper(QQuickItem *parent = 0);
  QString hash() const { return _hash; }
  QString source() const;
public slots:
  void setHash(const QString &hash);
signals:
  void hashChanged();
protected:
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *) override;
private:
  QString _hash;
};

#endif // IMAGEWRAPPER_H
