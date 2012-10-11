#ifndef WORD_H
#define WORD_H

#include <QObject>

class Word : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int x READ x)
  Q_PROPERTY(int y READ y)
  Q_PROPERTY(int length READ length)
  Q_PROPERTY(QString word READ word)
  Q_PROPERTY(QString question READ question)
  Q_PROPERTY(bool state READ state)
public:
  explicit Word(int x, int y, const QString &word, const QString &question, QObject *parent = 0);
  int x() { return x_; }
  int y() { return y_; }
  int length() { return length_; }
  QString word() { return word_; }
  QString question() { return question_; }
  bool state() { return state_; }
private:
  int x_;
  int y_;
  int length_;
  QString word_;
  QString question_;
  bool state_;
};

#endif // WORD_H
