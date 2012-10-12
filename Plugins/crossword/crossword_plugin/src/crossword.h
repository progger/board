#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <QObject>
#include "word.h"
#include "row.h"

class Crossword : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int width READ width NOTIFY updateWidth)
  Q_PROPERTY(int height READ height NOTIFY updateHeight)
public:
  explicit Crossword(QObject *parent = 0);
  virtual ~Crossword();
  bool init(const QString &file_name);
  int width() { return width_; }
  int height() { return height_; }
  QChar grid(int x, int y) { return grid_[y * width_ + x]; }
  Q_INVOKABLE QList<QObject*> rows() { return rows_; }
  Q_INVOKABLE QList<QObject*> across() { return across_; }
  Q_INVOKABLE QList<QObject*> down() { return down_; }
signals:
  void updateWidth();
  void updateHeight();
private:
  int width_;
  int height_;
  QChar *grid_;
  QList<QObject*> rows_;
  QList<QObject*> across_;
  QList<QObject*> down_;
};

#endif // CROSSWORD_H
