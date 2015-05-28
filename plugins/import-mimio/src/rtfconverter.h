/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef RTFCONVERTER_H
#define RTFCONVERTER_H

#include <QStringList>
#include <QTextCodec>
#include <QMap>
#include "rtfparser.h"

class RtfConverter
{
public:
  RtfConverter();
  QString convert(const QByteArray &data);
private:
  QTextCodec *_codec;
  QMap<int, QString> _fonts;
  int _def_font;

  QStringList _pars;
  QString _text;
  int _font;
  int _font_size;
  bool _bold;
  bool _italic;
  bool _underline;
  QString _color;

  void clear();
  void reset();
  void processRoot(RtfGroupPtr root);
  void processTag(RtfTagPtr tag);
  void processGroup(RtfGroupPtr group);
  void processText(RtfTextPtr text);
  void processFontTbl(RtfGroupPtr group);
  void processFontInfo(RtfGroupPtr group, int &pos);
  void appendPar();
};

#endif // RTFCONVERTER_H
