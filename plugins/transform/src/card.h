/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString leftHash READ leftHash WRITE setLeftHash NOTIFY leftHashChanged)
  Q_PROPERTY(QString leftSource READ leftSource NOTIFY leftHashChanged)
  Q_PROPERTY(QString rightHash READ rightHash WRITE setRightHash NOTIFY rightHashChanged)
  Q_PROPERTY(QString rightSource READ rightSource NOTIFY rightHashChanged)
public:
  explicit Card(QObject *parent = 0);
  QString leftHash() const { return _left_hash; }
  QString leftSource() const;
  QString rightHash() const { return _right_hash; }
  QString rightSource() const;
signals:
  void leftHashChanged();
  void rightHashChanged();
public slots:
  void setLeftHash(const QString &hash);
  void setRightHash(const QString &hash);
private:
  QString _left_hash;
  QString _right_hash;
};

#endif // CARD_H
