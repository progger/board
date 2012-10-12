#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString letter READ letter WRITE setLetter NOTIFY updateLetter)
  Q_PROPERTY(bool highlight READ highlight WRITE setHighlight NOTIFY updateHighlight)
  Q_PROPERTY(bool editing READ editint WRITE setEditing NOTIFY updateEditing)
public:
  explicit Cell(int x, int y, int type, QObject *parent = 0);
  int x() { return x_; }
  int y() { return y_; }
  Q_INVOKABLE int type() { return type_; }
  QString letter() { return letter_; }
  bool highlight() { return highlight_; }
  bool editint() { return editing_; }
signals:
  void updateLetter();
  void updateHighlight();
  void updateEditing();
public slots:
  void setLetter(const QString &letter);
  void setHighlight(bool highlight);
  void setEditing(bool editing);
private:
  int x_;
  int y_;
  int type_;
  QString letter_;
  bool highlight_;
  bool editing_;
};

#endif // CELL_H