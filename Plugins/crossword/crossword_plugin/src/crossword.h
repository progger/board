#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <QObject>
#include "word.h"

class Crossword : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int width READ width)
  Q_PROPERTY(int height READ height)
  Q_PROPERTY(int acrossCount READ acrossCount)
  Q_PROPERTY(int downCount READ downCount)
public:
  explicit Crossword(QObject *parent = 0);
  virtual ~Crossword();
  bool init(const QString &file_name);
  int width() { return width_; }
  int height() { return height_; }
  int acrossCount() { return across_.length(); }
  int downCount() { return down_.length(); }
  Q_INVOKABLE QChar grid(int x, int y) { return grid_[y * width_ + x]; }
  Q_INVOKABLE QObject * across(int index) { return across_.at(index); }
  Q_INVOKABLE QObject * down(int index) { return down_.at(index); }
private:
  int width_;
  int height_;
  QChar *grid_;
  QList<Word*> across_;
  QList<Word*> down_;
};

#endif // CROSSWORD_H
