/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MIMIOTEXT_H
#define MIMIOTEXT_H

#include "shape.h"

class MimioText : public Shape
{
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(QObject* textElement READ textElement CONSTANT)
public:
  explicit MimioText(QQuickItem *parent = 0);
  QString text() const;
  QObject *textElement() const;
public slots:
  void setHash(const QString &hash);
  void setText(const QString &text);
signals:
  void textChanged();
protected:
  virtual QString elementName() const override;
  virtual void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  virtual void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QString _hash;
};

#endif // MIMIOTEXT_H
