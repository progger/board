/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CROSS_H
#define CROSS_H

#include "iexternal.h"
#include "icross.h"

class Cross : public QObject, public IExternal, public ICross
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Board.IExternal/1.0")
  Q_INTERFACES(IExternal ICross)
public:
  explicit Cross(QObject *parent = 0);
  void init(ICore *core);
  IParser *createParser(QObject *parent, QObjectList *words);
  IWord *createWord(QObject *parent);
  IGrid *createGrid(QObject *parent);
};

#endif // CROSS_H
