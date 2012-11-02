/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef ICELL_H
#define ICELL_H

#include <QObject>

class ICell {
public:
  virtual ~ICell() {}
  virtual int x() = 0;
  virtual int y() = 0;
  virtual int type() = 0;
  virtual QString letter() = 0;
  virtual bool highlight() = 0;
  virtual bool editing() = 0;
  virtual bool accepted() = 0;
  virtual bool error() = 0;
  virtual void setType(int type) = 0;
  virtual void setLetter(const QString &letter) = 0;
  virtual void setHighlight(bool highlight) = 0;
  virtual void setEditing(bool editing) = 0;
  virtual void setAccepted(bool accepted) = 0;
  virtual void setError(bool error) = 0;
};

Q_DECLARE_INTERFACE(ICell, "Board.cross.ICell/1.0")

#endif // ICELL_H
