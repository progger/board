/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SWFPLAYER_H
#define SWFPLAYER_H

#include "swfwebapp.h"
#include "shape.h"

class SwfPlayer : public Shape
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(SwfPlayer)
  Q_PROPERTY(int port READ port CONSTANT)
  Q_PROPERTY(QString hash READ hash WRITE setHash NOTIFY hashChanged)
public:
  explicit SwfPlayer(QQuickItem *parent = nullptr);
  ~SwfPlayer() override = default;
  int port() const;
  QString hash() const { return _hash; }
public slots:
  void setHash(const QString &hash);
signals:
  void hashChanged();
protected:
  QString elementName() const override;
  void innerSerialize(QXmlStreamWriter *writer, QSet<QString> *brd_objects) const override;
  void innerDeserialize(QXmlStreamReader *reader) override;
private:
  QSharedPointer<SwfWebApp> _swf_web_app;
  QString _hash;
};

#endif // SWFPLAYER_H
