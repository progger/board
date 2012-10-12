#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString letter READ letter WRITE setLetter NOTIFY updateLetter)
  Q_PROPERTY(bool highlight READ highlight WRITE setHighlight NOTIFY updateHighlight)
public:
  explicit Cell(int type, QObject *parent = 0);
  Q_INVOKABLE int type() { return type_; }
  QString letter() { return letter_; }
  bool highlight() { return highlight_; }
signals:
  void updateLetter();
  void updateHighlight();
public slots:
  void setLetter(const QString &letter);
  void setHighlight(bool highlight);
private:
  int type_;
  QString letter_;
  bool highlight_;
};

#endif // CELL_H
