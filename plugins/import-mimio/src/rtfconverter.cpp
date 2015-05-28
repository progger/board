/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "rtfconverter.h"

const QString HtmlFmt = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                        "p, li { white-space: pre-wrap; }\n"
                        "</style></head><body>%0</body></html>";
const QString ParFmt = "<p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">%0</p>";
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
  if (!root)
  {
    clear();
    return QString();
  }
  processRoot(root);
  QString pars_text;
  for (QString par : _pars)
  {
    pars_text.append(ParFmt.arg(par));
  }
  clear();
  return HtmlFmt.arg(pars_text);
}

void RtfConverter::clear()
{
  _codec = nullptr;
  _fonts.clear();
  _def_font = 0;
  _pars.clear();
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
  _color = "#000000";
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
  if (tag->tag() == "b")
  {
    _bold = tag->hasParam() ? tag->param() > 0 : true;
  }
  if (tag->tag() == "f")
  {
    _font = tag->param();
  }
  if (tag->tag() == "fs")
  {
    _font_size = tag->param();
  }
  if (tag->tag() == "line")
  {
    _text.append(NewLine);
  }
  if (tag->tag() == "par")
  {
    appendPar();
  }
  if (tag->tag() == "pard")
  {
    reset();
  }
  if (tag->tag() == "qc")
  {
    //TODO
  }
  if (tag->tag() == "qj")
  {
    //TODO
  }
  if (tag->tag() == "ql")
  {
    //TODO
  }
  if (tag->tag() == "qr")
  {
    //TODO
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
}

void RtfConverter::processText(RtfTextPtr text)
{
  QByteArray data = text->text();
  QString txt = _codec ? _codec->toUnicode(data) : QString::fromUtf8(data);
  QString font_size = FontSizeFmt.arg(_font_size / 2);
  QString color = ColorFmt.arg(_color);
  _text.append(SpanFmt
               .arg(txt)
               .arg(_fonts[_font])
               .arg(font_size)
               .arg(_bold ? FontBold : "")
               .arg(_italic ? FontItalic : "")
               .arg(_underline ? FontUnderline : "")
               .arg(color));
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
  _pars.append(_text);
  _text.clear();
}
