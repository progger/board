/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef TEXTEDITTOOL_H
#define TEXTEDITTOOL_H

#include <QQuickTextDocument>

class TextEditTool : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int selectionStart READ selectionStart WRITE setSelectionStart NOTIFY selectionStartChanged)
  Q_PROPERTY(int selectionEnd READ selectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged)
  Q_PROPERTY(bool bold READ bold WRITE setBold NOTIFY boldChanged)
  Q_PROPERTY(bool italic READ italic WRITE setItalic NOTIFY italicChanged)
  Q_PROPERTY(bool underline READ underline WRITE setUnderline NOTIFY underlineChanged)
public:
  explicit TextEditTool(QObject *parent = 0);
  int selectionStart() const { return _selection_start; }
  int selectionEnd() const { return _selection_end; }
  bool bold() const { return _bold; }
  bool italic() const { return _italic; }
  bool underline() const { return _underline; }
signals:
  void selectionStartChanged();
  void selectionEndChanged();
  void boldChanged();
  void italicChanged();
  void underlineChanged();
public slots:
  void init(QQuickTextDocument *doc);
  void setSelectionStart(int selection_start);
  void setSelectionEnd(int selection_end);
  void setBold(bool bold);
  void setItalic(bool italic);
  void setUnderline(bool underline);
  void onContentChange(int position, int chars_removed, int chars_added);
private:
  void applyFormat();
  QTextDocument *_doc;
  int _selection_start;
  int _selection_end;
  bool _bold;
  bool _italic;
  bool _underline;
};

#endif // TEXTEDITTOOL_H
