/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef RTFPARSER_H
#define RTFPARSER_H

#include <QByteArray>
#include <QList>
#include <QSharedPointer>

enum class NodeType {Tag, Group, Text};

class RtfNode;
class RtfTag;
class RtfGroup;
class RtfText;
typedef QSharedPointer<RtfNode> RtfNodePtr;
typedef QList<RtfNodePtr> RtfNodeList;
typedef QSharedPointer<RtfTag> RtfTagPtr;
typedef QSharedPointer<RtfGroup> RtfGroupPtr;
typedef QSharedPointer<RtfText> RtfTextPtr;

class RtfNode
{
public:
  RtfNode(NodeType type) : _type(type) {}
  NodeType type() const { return _type; }
private:
  NodeType _type;
};

class RtfTag : public RtfNode
{
public:
  RtfTag(const QByteArray &tag, bool has_param, int param) : RtfNode(NodeType::Tag), _tag(tag), _has_param(has_param), _param(param) {}
  QByteArray tag() const { return _tag; }
  bool hasParam() const { return _has_param; }
  int param() const { return _param; }
  static RtfTagPtr FromNode(RtfNodePtr node) { return node->type() == NodeType::Tag ? node.staticCast<RtfTag>() : RtfTagPtr(); }
private:
  QByteArray _tag;
  bool _has_param;
  int _param;
};

class RtfGroup : public RtfNode
{
public:
  RtfGroup(const RtfNodeList &nodes) : RtfNode(NodeType::Group), _nodes(nodes) {}
  RtfNodeList nodes() const { return _nodes; }
  static RtfGroupPtr FromNode(RtfNodePtr node) { return node->type() == NodeType::Group ? node.staticCast<RtfGroup>() : RtfGroupPtr(); }
private:
  RtfNodeList _nodes;
};

class RtfText : public RtfNode
{
public:
  RtfText(const QByteArray &text) : RtfNode(NodeType::Text), _text(text) {}
  QByteArray text() const { return _text; }
  static RtfTextPtr FromNode(RtfNodePtr node) { return node->type() == NodeType::Text ? node.staticCast<RtfText>() : RtfTextPtr(); }
private:
  QByteArray _text;
};

class RtfParser
{
public:
  RtfParser(const QByteArray &data);
  RtfGroupPtr parse();
private:
  QByteArray _data;
  int _pos;
  char _cur;
  RtfNodePtr readNode();
  RtfNodePtr readGroup();
  bool read();
  bool read2();
  bool readTag(QByteArray &tag, bool &has_param, int &param);
  char hexToChar(char c);
};

#endif // RTFPARSER_H
