/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ARITHMETICITEM_H
#define ARITHMETICITEM_H

#include <QObject>

class ArithmeticItem : public QObject
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(ArithmeticItem)
  Q_PROPERTY(int left READ left WRITE setLeft NOTIFY leftChanged)
  Q_PROPERTY(int right READ right WRITE setRight NOTIFY rightChanged)
  Q_PROPERTY(QString operation READ operation WRITE setOperation NOTIFY operationChanged)
  Q_PROPERTY(int result READ result NOTIFY resultChanged)
public:
  explicit ArithmeticItem(QObject *parent = nullptr);
  ~ArithmeticItem() override = default;
  int left() const { return _left; }
  int right() const { return _right; }
  QString operation() const { return _operation; }
  int result() const { return _result; }
signals:
  void leftChanged();
  void rightChanged();
  void operationChanged();
  void resultChanged();
public slots:
  void setLeft(int left);
  void setRight(int right);
  void setOperation(const QString &operation);
  void generate();
private:
  int _left;
  int _right;
  QString _operation;
  int _result;
  void updateResult();
};

#endif // ARITHMETICITEM_H
