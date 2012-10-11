#include <QFile>
#include "parser.h"
#include "crossword.h"

Crossword::Crossword(QObject *parent) :
  QObject(parent),
  width_(0),
  height_(0),
  grid_(nullptr),
  across_(),
  down_()
{
}

Crossword::~Crossword()
{
  delete[] grid_;
}

bool Crossword::init(const QString &file_name)
{
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly)) return false;
  QString data(file.readAll());
  Parser parser(data);
  QString str;
  if (!parser.read(str) || str !="<ACROSS PUZZLE>") return false;
  if (!parser.readTo("<SIZE>")) return false;
  if (!parser.read(str)) return false;
  auto size_parts = str.split('x');
  bool ok;
  width_ = size_parts[0].toInt(&ok);
  if (!ok) return false;
  height_ = size_parts[1].toInt(&ok);
  if (!ok) return false;
  if (!parser.readTo("<GRID>")) return false;
  grid_ = new QChar[width_ * height_];
  for (int i = 0; i < height_; i++)
  {
    if (!parser.read(str) || str.length() != width_) return false;
    memcpy(grid_ + i * width_, str.data(), width_ * sizeof(QChar));
  }
  if (!parser.readTo("<ACROSS>")) return false;
  for (int y = 0; y < height_; y++)
  {
    QString wrd = "";
    for (int x = 0; x < width_; x++)
    {
      QChar chr = grid(x, y);
      if (chr == '.')
      {
        if (wrd.length() > 1)
        {
          if (!parser.read(str)) return false;
          across_.append(new Word(x - wrd.length(), y, wrd, str, this));
          wrd = "";
        }
      }
      else
      {
        wrd.append(chr);
      }
    }
    if (wrd.length() > 1)
    {
      if (!parser.read(str)) return false;
      across_.append(new Word(width_ - wrd.length(), y, wrd, str, this));
    }
  }
  if (!parser.readTo("<DOWN>")) return false;
  for (int y = 0; y < height_ - 1; y++)
  {
    for (int x = 0; x < width_; x++)
    {
      QChar chr = grid(x, y);
      if (chr != '.')
      {
        if (y == 0 || grid(x, y - 1) == '.')
        {
          QString wrd = chr;
          for (int i = y + 1; i < height_; i++)
          {
            chr = grid(x, i);
            if (chr != '.')
            {
              wrd.append(chr);
            }
            else
            {
              break;
            }
          }
          if (wrd.length() > 1)
          {
            if (!parser.read(str)) return false;
            down_.append(new Word(x, y, wrd, str, this));
          }
        }
      }
    }
  }
  return true;
}
