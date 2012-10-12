#ifndef WORD_H
#define WORD_H

#include <QObject>

class Word : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool state READ state WRITE setState NOTIFY updateState)
  Q_PROPERTY(bool highlight READ highlight WRITE setHighlight NOTIFY updateHighlight)
public:
  explicit Word(int x, int y, bool direction, const QString &word, const QString &question, QObject *parent = 0);
  int x() { return x_; }
  int y() { return y_; }
  bool direction() { return direction_; }
  int length() { return length_; }
  QString word() { return word_; }
  Q_INVOKABLE QString question() { return question_; }
  bool state() { return state_; }
  bool highlight() { return highlight_; }
signals:
  void updateState();
  void updateHighlight();
public slots:
  void setState(bool state);
  void setHighlight(bool highlight);
private:
  int x_;
  int y_;
  bool direction_;
  int length_;
  QString word_;
  QString question_;
  bool state_;
  bool highlight_;
};

#endif // WORD_H