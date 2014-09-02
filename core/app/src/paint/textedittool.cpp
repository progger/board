/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QTextCursor>
#include "global.h"
#include "textedittool.h"

TextEditTool::TextEditTool(QObject *parent) :
  QObject(parent),
  _selection_start(0),
  _selection_end(0),
  _bold(false),
  _italic(false),
  _underline(false)
{
}

void TextEditTool::init(QQuickTextDocument *doc)
{
  _doc = doc->textDocument();
  connect(_doc, SIGNAL(contentsChange(int,int,int)), SLOT(onContentChange(int,int,int)));
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
  applyFormat();
  emit boldChanged();
}

void TextEditTool::setItalic(bool italic)
{
  _italic = italic;
  applyFormat();
  emit italicChanged();
}

void TextEditTool::setUnderline(bool underline)
{
  _underline = underline;
  applyFormat();
  emit underlineChanged();
}

void TextEditTool::onContentChange(int position, int chars_removed, int chars_added)
{
  Q_UNUSED(chars_removed);
  if (!chars_added) return;
  QTextCursor cursor(_doc);
  cursor.setPosition(position);
  cursor.setPosition(position + chars_added, QTextCursor::KeepAnchor);
  QTextCharFormat fmt = cursor.charFormat();
  QFont font = fmt.font();
  font.setBold(_bold);
  font.setItalic(_italic);
  font.setUnderline(_underline);
  font.setPixelSize(g_core->paint()->fontSize());
  fmt.setFont(font);
  fmt.setForeground(QBrush(g_core->paint()->color()));
  cursor.mergeCharFormat(fmt);
}

void TextEditTool::applyFormat()
{
  onContentChange(_selection_start, 0, _selection_end - _selection_start);
}
