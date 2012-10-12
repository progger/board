#ifndef WORD_H
#define WORD_H

#include <QObject>

class Word : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool state READ state NOTIFY updateState)
public:
  explicit Word(int x, int y, const QString &word, const QString &question, QObject *parent = 0);
  Q_INVOKABLE int x() { return x_; }
  Q_INVOKABLE int y() { return y_; }
  Q_INVOKABLE int length() { return length_; }
  Q_INVOKABLE QString word() { return word_; }
  Q_INVOKABLE QString question() { return question_; }
  bool state() { return state_; }
signals:
  void updateState();
private:
  int x_;
  int y_;
  int length_;
  QString word_;
  QString question_;
  bool state_;
};

#endif // WORD_H
