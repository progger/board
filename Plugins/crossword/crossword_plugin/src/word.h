/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef WORD_H
#define WORD_H

#include <QObject>

class Word : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int x READ x WRITE setX NOTIFY updateX)
  Q_PROPERTY(int y READ y WRITE setY NOTIFY updateY)
  Q_PROPERTY(bool direction READ direction WRITE setDirection NOTIFY updateDirection)
  Q_PROPERTY(QString word READ word WRITE setWord NOTIFY updateWord)
  Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY updateQuestion)
  Q_PROPERTY(bool highlight READ highlight WRITE setHighlight NOTIFY updateHighlight FINAL)
  Q_PROPERTY(bool accepted READ accepted WRITE setAccepted NOTIFY updateAccepted FINAL)
public:
  explicit Word(int x, int y, bool direction, const QString &word, const QString &question, QObject *parent = 0);
  int x() { return x_; }
  int y() { return y_; }
  bool direction() { return direction_; }
  int length() { return word_.length(); }
  QString word() { return word_; }
  QString question() { return question_; }
  bool state() { return state_; }
  bool highlight() { return highlight_; }
  bool accepted() { return accepted_; }
signals:
  void updateX();
  void updateY();
  void updateDirection();
  void updateWord();
  void updateQuestion();
  void updateHighlight();
  void updateAccepted();
public slots:
  void setX(int x);
  void setY(int y);
  void setDirection(bool direction);
  void setWord(QString word);
  void setQuestion(QString question);
  void setHighlight(bool highlight);
  void setAccepted(bool accepted);
private:
  int x_;
  int y_;
  bool direction_;
  QString word_;
  QString question_;
  bool state_;
  bool highlight_;
  bool accepted_;
};

#endif // WORD_H
