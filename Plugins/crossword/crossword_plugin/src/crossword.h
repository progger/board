#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <QObject>
#include "word.h"
#include "row.h"
#include "cell.h"

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
  Q_INVOKABLE QList<QObject*> words() { return words_; }
  Cell * getCell(int x, int y);
signals:
  void updateWidth();
  void updateHeight();
public slots:
  void hideHighlight();
  void highlightWord(QObject *wordObj);
  void highlightCell(QObject *cellObj);
  void edit(QString key);
private:
  int width_;
  int height_;
  QChar *grid_;
  QList<QObject*> rows_;
  QList<QObject*> words_;
  Word* editing_word_;
  int editing_pos_;
  void checkWord();
};

#endif // CROSSWORD_H
