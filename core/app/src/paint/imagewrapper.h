/*
 * Copyright (C) 2013 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include "shape.h"

class ImageWrapper : public Shape
{
  Q_OBJECT
  Q_PROPERTY(QString source READ source NOTIFY sourceChanged)
public:
  explicit ImageWrapper(QQuickItem *parent = 0);
  QString source() const;
public slots:
  void setHash(const QString &hash);
signals:
  void sourceChanged();
protected:
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, ISheetCanvas *, std::set<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader, ISheetCanvas *) override;
private:
  QString _hash;
};

#endif // IMAGEWRAPPER_H
