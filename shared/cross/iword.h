/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICROSSWORD_H
#define ICROSSWORD_H

#include <QObject>

class IWord {
public:
  virtual ~IWord() {}
  virtual int x() = 0;
  virtual int y() = 0;
  virtual bool direction() = 0;
  virtual int length() = 0;
  virtual QString word() = 0;
  virtual QString question() = 0;
  virtual bool highlight() = 0;
  virtual bool accepted() = 0;
  virtual void setX(int x) = 0;
  virtual void setY(int y) = 0;
  virtual void setDirection(bool direction) = 0;
  virtual void setWord(QString word) = 0;
  virtual void setQuestion(QString question) = 0;
  virtual void setHighlight(bool highlight) = 0;
  virtual void setAccepted(bool accepted) = 0;
  virtual QObject *toObject() = 0;
};

Q_DECLARE_INTERFACE(IWord, "Board.cross.IWord/1.0")

#endif // ICROSSWORD_H
