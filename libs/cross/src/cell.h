/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CELL_H
#define CELL_H

#include "icell.h"

class Cell : public QObject, public ICell
{
  Q_OBJECT
  Q_INTERFACES(ICell)
  Q_PROPERTY(int type READ type NOTIFY updateType FINAL)
  Q_PROPERTY(QString letter READ letter WRITE setLetter NOTIFY updateLetter FINAL)
  Q_PROPERTY(bool highlight READ highlight WRITE setHighlight NOTIFY updateHighlight FINAL)
  Q_PROPERTY(bool editing READ editing WRITE setEditing NOTIFY updateEditing FINAL)
  Q_PROPERTY(bool accepted READ accepted WRITE setAccepted NOTIFY updateAccepted FINAL)
  Q_PROPERTY(bool error READ error WRITE setError NOTIFY updateError FINAL)
public:
  explicit Cell(int x, int y, QObject *parent = 0);
  int x() { return x_; }
  int y() { return y_; }
  int type() { return type_; }
  QString letter() { return letter_; }
  bool highlight() { return highlight_; }
  bool editing() { return editing_; }
  bool accepted() { return accepted_; }
  bool error() { return error_; }
signals:
  void updateType();
  void updateLetter();
  void updateHighlight();
  void updateEditing();
  void updateAccepted();
  void updateError();
public slots:
  void setType(int type);
  void setLetter(const QString &letter);
  void setHighlight(bool highlight);
  void setEditing(bool editing);
  void setAccepted(bool accepted);
  void setError(bool error);
private:
  int x_;
  int y_;
  int type_;
  QString letter_;
  bool highlight_;
  bool editing_;
  bool accepted_;
  bool error_;
};

#endif // CELL_H
