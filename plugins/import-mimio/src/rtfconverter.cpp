/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "rtfconverter.h"

const QString HtmlFmt = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                        "p, li { white-space: pre-wrap; }\n"
                        "</style></head><body>"
                        "%0"
                        "</body></html>";
const QString ParFmt = "<p align=\"%1\" style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">%0</p>";
const QString SpanFmt = "<span style=\"%1%2%3%4%5%6\">%0</span>";
const QString FontFmt = " font-family:'%0';";
const QString FontSizeFmt = " font-size:%0pt;";
const QString FontBold = " font-weight:bold;";
const QString FontItalic = " font-style:italic;";
const QString FontUnderline = " text-decoration:underline;";
const QString ColorFmt = " color:%0;";
const QString NewLine = "<br/>";

RtfConverter::RtfConverter()
{
  clear();
}

QString RtfConverter::convert(const QByteArray &data)
{
  clear();
  RtfGroupPtr root = RtfParser(data).parse();
  if (!root) return QString();
  processRoot(root);
  QString pars = _pars.join('\n');
  clear();
  return HtmlFmt.arg(pars);
}

void RtfConverter::clear()
{
  _codec = nullptr;
  _fonts.clear();
  _colors.clear();
  _def_font = 0;
  _pars.clear();
  _align = "left";
  _text.clear();
  reset();
}

void RtfConverter::reset()
{
  _font = _def_font;
  _font_size = 24;
  _bold = false;
  _italic = false;
  _underline = false;
  _color = 0;
}

void RtfConverter::processRoot(RtfGroupPtr root)
{
  for (RtfNodePtr node : root->nodes())
  {
    switch (node->type())
    {
    case NodeType::Tag:
      {
        RtfTagPtr tag = RtfTag::FromNode(node);
        processTag(tag);
        break;
      }
    case NodeType::Group:
      {
        RtfGroupPtr group = RtfGroup::FromNode(node);
        processGroup(group);
        break;
      }
    case NodeType::Text:
      {
        RtfTextPtr text = RtfText::FromNode(node);
        processText(text);
        break;
      }
    }
  }
  appendPar();
}

void RtfConverter::processTag(RtfTagPtr tag)
{
  if (tag->tag() == "ansicpg" && tag->param() >= 1250 && tag->param() <= 1258)
  {
    _codec = QTextCodec::codecForName("windows-" + QByteArray::number(tag->param()));
  }
  else if (tag->tag() == "b")
  {
    _bold = tag->hasParam() ? tag->param() > 0 : true;
  }
  else if (tag->tag() == "cf")
  {
    _color = tag->param();
  }
  else if (tag->tag() == "f")
  {
    _font = tag->param();
  }
  else if (tag->tag() == "fs")
  {
    _font_size = tag->param();
  }
  else if (tag->tag() == "i")
  {
    _italic = tag->hasParam() ? tag->param() > 0 : true;
  }
  else if (tag->tag() == "line")
  {
    _text.append(NewLine);
  }
  else if (tag->tag() == "par")
  {
    appendPar();
  }
  else if (tag->tag() == "pard")
  {
    reset();
  }
  else if (tag->tag() == "qc")
  {
    _align = "center";
  }
  else if (tag->tag() == "qj")
  {
    _align = "justify";
  }
  else if (tag->tag() == "ql")
  {
    _align = "left";
  }
  else if (tag->tag() == "qr")
  {
    _align = "right";
  }
  else if (tag->tag() == "ul")
  {
    _underline = tag->hasParam() ? tag->param() > 0 : true;
  }
  else if (tag->tag() == "ulnone")
  {
    _underline = false;
  }
}

void RtfConverter::processGroup(RtfGroupPtr group)
{
  if (group->nodes().isEmpty()) return;
  RtfTagPtr tag = RtfTag::FromNode(group->nodes()[0]);
  if (tag->tag() == "fonttbl")
  {
    processFontTbl(group);
  }
  else if (tag->tag() == "colortbl")
  {
    processColorTbl(group);
  }
}

void RtfConverter::processText(RtfTextPtr text)
{
  QByteArray data = text->text();
  QString txt = _codec ? _codec->toUnicode(data) : QString::fromUtf8(data);
  QString font_size_arg = FontSizeFmt.arg(_font_size / 2);
  QString color = _colors[_color];
  if (color.isEmpty())
  {
    color = "#000000";
  }
  QString color_arg = ColorFmt.arg(color);
  _text.append(SpanFmt
               .arg(txt)
               .arg(_fonts[_font])
               .arg(font_size_arg)
               .arg(_bold ? FontBold : "")
               .arg(_italic ? FontItalic : "")
               .arg(_underline ? FontUnderline : "")
               .arg(color_arg));
}

void RtfConverter::processFontTbl(RtfGroupPtr group)
{
  int count = group->nodes().size();
  int pos = 1;
  while (pos < count)
  {
    RtfNodePtr node = group->nodes()[pos];
    switch (node->type())
    {
    case NodeType::Tag:
      {
        processFontInfo(group, pos);
        break;
      }
    case NodeType::Group:
      {
        RtfGroupPtr grp = RtfGroup::FromNode(node);
        int tmp = 0;
        processFontInfo(grp, tmp);
        ++pos;
        break;
      }
    default:
      {
        ++pos;
        break;
      }
    }
  }
}

void RtfConverter::processColorTbl(RtfGroupPtr group)
{
  int count = group->nodes().size();
  int pos = 1;
  int index = 0;
  int r = -1;
  int g = -1;
  int b = -1;
  while (pos < count)
  {
    RtfNodePtr node = group->nodes()[pos];
    if (node->type() == NodeType::Tag)
    {
      RtfTagPtr tag = RtfTag::FromNode(node);
      if (tag->tag() == "red")
      {
        r = tag->param();
      }
      else if (tag->tag() == "green")
      {
        g = tag->param();
      }
      else if (tag->tag() == "blue")
      {
        b = tag->param();
      }
    }
    else if (node->type() == NodeType::Text && RtfText::FromNode(node)->text() == ";")
    {
      if (r >= 0 && g >= 0 && b >= 0)
      {
        QString color = QString("#%0%1%2").arg(r, 2, 16, QChar('0')).arg(g, 2, 16, QChar('0')).arg(b, 2, 16, QChar('0'));
        _colors[index] = color;
      }
      ++index;
    }
    ++pos;
  }
}

void RtfConverter::processFontInfo(RtfGroupPtr group, int &pos)
{
  int count = group->nodes().size();
  int num = -1;
  QByteArray font_name;
  while (pos < count)
  {
    RtfNodePtr node = group->nodes()[pos];
    if (node->type() == NodeType::Tag)
    {
      RtfTagPtr tag = RtfTag::FromNode(node);
      if (tag->tag() == "f")
      {
        num = tag->param();
      }
    }
    else if (node->type() == NodeType::Text)
    {
      QByteArray text = RtfText::FromNode(node)->text();
      bool semicolon = text.endsWith(';');
      if (font_name.isEmpty())
      {
        font_name = semicolon ? text.mid(0, text.size() - 1) : text;
        if (font_name.endsWith(" CYR"))
        {
          font_name = font_name.mid(0, font_name.size() - 4);
        }
      }
      if (semicolon)
      {
        if (num >= 0 && !font_name.isEmpty())
        {
          _fonts[num] = FontFmt.arg(QString::fromLatin1(font_name));
        }
        ++pos;
        return;
      }
    }
    ++pos;
  }
}

void RtfConverter::appendPar()
{
  if (_text.isEmpty()) return;
  _pars.append(ParFmt
               .arg(_text)
               .arg(_align));
  _text.clear();
}
