/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "rtfparser.h"

RtfParser::RtfParser(const QByteArray &data) :
  _data(data),
  _pos(0),
  _cur(0)
{
}

RtfGroupPtr RtfParser::parse()
{
  _pos = 0;
  _cur = 0;
  if (!read() || _cur != '{' || !read()) return RtfGroupPtr();
  RtfNodeList nodes;
  while (_cur != '}')
  {
    RtfNodePtr node = readNode();
    if (!node) return RtfGroupPtr();
    nodes.append(node);
  }
  return RtfGroupPtr::create(nodes);
}

RtfNodePtr RtfParser::readNode()
{
  if (_cur == '{')
  {
    if (!read()) return RtfNodePtr();
    return readGroup();
  }
  QByteArray text;
  while (true)
  {
    if (_cur == '\\')
    {
      if (_pos >= _data.size()) break;
      char next = _data[_pos];
      if (next == '\'')
      {
        if (!read()) break;
        if (!read()) break;
        char c1 = hexToChar(_cur);
        if (c1 < 0) break;
        if (!read()) break;
        char c2 = hexToChar(_cur);
        if (c2 < 0) break;
        if (!read()) break;
        text.append(c1 * 16 + c2);
      }
      else
      {
        if (text.isEmpty())
        {
          if (next == '*')
          {
            if (!read()) break;
            if (!read()) break;
            return RtfTagPtr::create("*", false, 0);
          }
          QByteArray tag;
          bool has_param;
          int param;
          if (!readTag(tag, has_param, param)) break;
          return RtfTagPtr::create(tag, has_param, param);
        }
        else
        {
          return RtfTextPtr::create(text);
        }
      }
    }
    else if (_cur == '}')
    {
      if (text.isEmpty()) break;
      return RtfTextPtr::create(text);
    }
    else
    {
      text.append(_cur);
      if (!read()) break;
    }
  }
  return RtfNodePtr();
}

RtfNodePtr RtfParser::readGroup()
{
  RtfNodeList nodes;
  while (_cur != '}')
  {
    RtfNodePtr node = readNode();
    if (!node) return RtfNodePtr();
    nodes.append(node);
  }
  if (!read()) return RtfNodePtr();
  return RtfGroupPtr::create(nodes);
}

bool RtfParser::read()
{
  while (true)
  {
    if (_pos >= _data.size()) return false;
    _cur = _data[_pos++];
    if (_cur >= 32) return true;
  }
}

bool RtfParser::read2()
{
  if (_pos >= _data.size()) return false;
  _cur = _data[_pos++];
  return true;
}

bool RtfParser::readTag(QByteArray &tag, bool &has_param, int &param)
{
  if (!read()) return false;
  tag = QByteArray();
  while ((_cur >= 'a' && _cur <= 'z') || (_cur >= 'A' && _cur <= 'Z'))
  {
    tag.append(_cur);
    if (!read2()) return false;
  }
  if (tag.isEmpty()) return false;
  QByteArray prm;
  if (_cur == '-')
  {
    prm.append(_cur);
    if (!read2()) return false;
  }
  while (_cur >= '0' && _cur <= '9')
  {
    prm.append(_cur);
    if (!read2()) return false;
  }
  if (!prm.isEmpty())
  {
    bool ok = true;
    param = prm.toInt(&ok);
    if (!ok) return false;
    has_param = true;
  }
  else
  {
    param = 0;
    has_param = false;
  }
  while (_cur == ' ')
  {
    if (!read2()) return false;
  }
  return true;
}

char RtfParser::hexToChar(char c)
{
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}
