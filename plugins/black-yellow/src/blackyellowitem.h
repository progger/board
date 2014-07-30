/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef BLACKYELLOWITEM_H
#define BLACKYELLOWITEM_H

#include <QObject>

class BlackYellowItem : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
  Q_PROPERTY(QString answer READ answer WRITE setAnswer NOTIFY answerChanged)
public:
  explicit BlackYellowItem(QObject *parent = 0);
  QString question() const { return _question; }
  QString answer() const { return _answer; }
signals:
  void questionChanged();
  void answerChanged();
public slots:
  void setQuestion(const QString &question);
  void setAnswer(const QString &answer);
private:
  QString _question;
  QString _answer;
};

#endif // BLACKYELLOWITEM_H
