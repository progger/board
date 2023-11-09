/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QTextCursor>
#include "textedittool.h"

TextEditTool::TextEditTool(Paint *paint, QObject *parent) :
  QObject(parent),
  _paint(paint),
  _doc(nullptr),
  _selection_start(0),
  _selection_end(0),
  _lock(false),
  _bold(false),
  _italic(false),
  _underline(false)
{
}

void TextEditTool::init(QQuickTextDocument *doc)
{
  if (doc)
  {
    _doc = doc->textDocument();
    connect(_doc, SIGNAL(contentsChange(int,int,int)), SLOT(onContentChange(int,int,int)));
    connect(_paint, SIGNAL(colorChanged()), SLOT(onColorChanged()));
    connect(_paint, SIGNAL(fontSizeChanged()), SLOT(onFontSizeChanged()));
  }
  else
  {
    if (_doc)
    {
      disconnect(_doc, SIGNAL(contentsChange(int,int,int)));
    }
    disconnect(_paint, SIGNAL(colorChanged()));
    disconnect(_paint, SIGNAL(fontSizeChanged()));
    _doc = nullptr;
  }
}

void TextEditTool::setSelectionStart(int selection_start)
{
  _selection_start = selection_start;
  emit selectionStartChanged();
}

void TextEditTool::setSelectionEnd(int selection_end)
{
  _selection_end = selection_end;
  emit selectionEndChanged();
}

void TextEditTool::setBold(bool bold)
{
  _bold = bold;
  _lock = true;
  QTextCursor cursor(_doc);
  for (int i = _selection_start; i < _selection_end; ++i)
  {
    cursor.setPosition(i);
    cursor.setPosition(i + 1, QTextCursor::KeepAnchor);
    QTextCharFormat fmt = cursor.charFormat();
    QFont font = fmt.font();
    font.setBold(_bold);
    fmt.setFont(font);
    cursor.setCharFormat(fmt);
  }
  _lock = false;
  emit boldChanged();
}

void TextEditTool::setItalic(bool italic)
{
  _italic = italic;
  _lock = true;
  QTextCursor cursor(_doc);
  for (int i = _selection_start; i < _selection_end; ++i)
  {
    cursor.setPosition(i);
    cursor.setPosition(i + 1, QTextCursor::KeepAnchor);
    QTextCharFormat fmt = cursor.charFormat();
    QFont font = fmt.font();
    font.setItalic(_italic);
    fmt.setFont(font);
    cursor.setCharFormat(fmt);
  }
  _lock = false;
  emit italicChanged();
}

void TextEditTool::setUnderline(bool underline)
{
  _underline = underline;
  _lock = true;
  QTextCursor cursor(_doc);
  for (int i = _selection_start; i < _selection_end; ++i)
  {
    cursor.setPosition(i);
    cursor.setPosition(i + 1, QTextCursor::KeepAnchor);
    QTextCharFormat fmt = cursor.charFormat();
    QFont font = fmt.font();
    font.setUnderline(_underline);
    fmt.setFont(font);
    cursor.setCharFormat(fmt);
  }
  _lock = false;
  emit underlineChanged();
}

void TextEditTool::onContentChange(int position, int chars_removed, int chars_added)
{
  Q_UNUSED(chars_removed);
  if (_lock) return;
  if (!_doc) return;
  if (!chars_added) return;
  if (position == 0 && chars_added >= _doc->characterCount()) return;
  QTextCursor cursor(_doc);
  cursor.setPosition(position);
  cursor.setPosition(position + chars_added, QTextCursor::KeepAnchor);
  QTextCharFormat fmt = cursor.charFormat();
  QFont font = fmt.font();
  font.setBold(_bold);
  font.setItalic(_italic);
  font.setUnderline(_underline);
  font.setPixelSize(_paint->fontSize());
  fmt.setFont(font);
  fmt.setForeground(QBrush(_paint->color()));
  cursor.mergeCharFormat(fmt);
}

void TextEditTool::onColorChanged()
{
  if (!_doc) return;
  _lock = true;
  QTextCursor cursor(_doc);
  for (int i = _selection_start; i < _selection_end; ++i)
  {
    cursor.setPosition(i);
    cursor.setPosition(i + 1, QTextCursor::KeepAnchor);
    QTextCharFormat fmt = cursor.charFormat();
    fmt.setForeground(QBrush(_paint->color()));
    cursor.setCharFormat(fmt);
  }
  _lock = false;
}

void TextEditTool::onFontSizeChanged()
{
  if (!_doc) return;
  _lock = true;
  QTextCursor cursor(_doc);
  for (int i = _selection_start; i < _selection_end; ++i)
  {
    cursor.setPosition(i);
    cursor.setPosition(i + 1, QTextCursor::KeepAnchor);
    QTextCharFormat fmt = cursor.charFormat();
    QFont font = fmt.font();
    font.setPixelSize(_paint->fontSize());
    fmt.setFont(font);
    cursor.setCharFormat(fmt);
  }
  _lock = false;
}
