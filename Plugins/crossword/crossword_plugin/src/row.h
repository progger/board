#ifndef ROW_H
#define ROW_H

#include <QObject>

class Row : public QObject
{
  Q_OBJECT
public:
  explicit Row(QObject *parent = 0);
  void addCell(QObject *cell);
  Q_INVOKABLE QList<QObject*> cells() { return cells_; }
private:
  QList<QObject*> cells_;
};

#endif // ROW_H
