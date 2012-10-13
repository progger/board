#include <QFile>
#include "parser.h"
#include "cell.h"
#include "crossword.h"

Crossword::Crossword(QObject *parent) :
  QObject(parent),
  width_(0),
  height_(0),
  grid_(nullptr),
  rows_(),
  words_(),
  editing_word_(nullptr),
  editing_pos_(0)
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
  int grid_size = width_ * height_;
  grid_ = new QChar[grid_size];
  for (int y = 0; y < height_; y++)
  {
    if (!parser.read(str) || str.length() != width_) return false;
    str = str.toUpper();
    memcpy(grid_ + y * width_, str.data(), width_ * sizeof(QChar));
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
          words_.append(new Word(x - wrd.length(), y, false, wrd, str, this));
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
      words_.append(new Word(width_ - wrd.length(), y, false, wrd, str, this));
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
            words_.append(new Word(x, y, true, wrd, str, this));
          }
        }
      }
    }
  }

  bool change;
  do
  {
    change = false;
    for (int y = 0; y < height_; y++)
    {
      for (int x = 0; x < width_; x++)
      {
        if (grid(x, y) == '.' && (
              x == 0 || x == width_ - 1 || y == 0 || y == width_ -1 ||
              grid(x - 1, y) == ' ' || grid(x + 1, y) == ' ' ||
              grid(x, y - 1) == ' ' || grid(x, y + 1) == ' '))
        {
          grid_[y * width_ + x] = ' ';
          change = true;
        }
      }
    }
  }
  while (change);

  for (int y = 0; y < height_; y++)
  {
    auto row = new Row(this);
    for (int x = 0; x < width_; x++)
    {
      QChar chr = grid(x, y);
      auto cell = new Cell(x, y, chr == ' ' ? 0 : chr == '.' ? 1 : 2);
      row->addCell(cell);
    }
    rows_.append(row);
  }
  return true;
}

Cell *Crossword::getCell(int x, int y)
{
  Row *row = static_cast<Row*>(rows_.at(y));
  return static_cast<Cell*>(row->cells().at(x));
}

void Crossword::hideHighlight()
{
  foreach (QObject *rowObj, rows_)
  {
    Row *row = static_cast<Row*>(rowObj);
    foreach (QObject *cellObj, row->cells())
    {
      Cell *cell = static_cast<Cell*>(cellObj);
      cell->setHighlight(false);
      cell->setEditing(false);
    }
  }
  foreach (QObject *wordObj, words_)
  {
    Word *word = static_cast<Word*>(wordObj);
    word->setHighlight(false);
  }
  editing_word_ = nullptr;
  editing_pos_ = 0;
}

void Crossword::highlightWord(QObject *wordObj)
{
  Word *word = qobject_cast<Word*>(wordObj);
  if (!word || word->accepted()) return;
  hideHighlight();
  word->setHighlight(true);
  for (int i = 0; i < word->length(); i++)
  {
    int x = word->x() + (word->direction() ? 0 : i);
    int y = word->y() + (word->direction() ? i : 0);
    auto cell = getCell(x, y);
    cell->setHighlight(true);
  }
  editing_word_ = word;
  editing_pos_ = 0;
  auto cell = getCell(word->x(), word->y());
  cell->setEditing(true);
}

void Crossword::highlightCell(QObject *cellObj)
{
  Cell *cell = qobject_cast<Cell*>(cellObj);
  if (!cell || cell->type() != 2) return;
  foreach (QObject *wordObj, words_)
  {
    Word *word = static_cast<Word*>(wordObj);
    if (word->direction()
        ? cell->x() == word->x() && cell->y() >= word->y() && cell->y() < word->y() + word->length()
        : cell->y() == word->y() && cell->x() >= word->x() && cell->x() < word->x() + word->length())
    {
      highlightWord(word);
      break;
    }
  }
}

void Crossword::edit(QString key)
{
  if (key.isEmpty() || !editing_word_) return;
  key = key.toUpper();
  bool direction = editing_word_->direction();
  int length = editing_word_->length();
  int x = editing_word_->x() + (direction ? 0 : editing_pos_);
  int y = editing_word_->y() + (direction ? editing_pos_ : 0);
  auto cell = getCell(x, y);
  cell->setLetter(key);
  cell->setEditing(false);
  editing_pos_++;
  while (editing_pos_ < length)
  {
    if (direction)
      y++;
    else
      x++;
    cell = getCell(x, y);
    if (!cell->accepted()) break;
    editing_pos_++;
  }
  if (editing_pos_ >= length)
  {
    checkWord();
    hideHighlight();
  }
  else
  {
    cell->setEditing(true);
  }
}

void Crossword::checkWord()
{
  int count = editing_word_->length();
  for (int i = 0; i < count; i++)
  {
    int x = editing_word_->x() + (editing_word_->direction() ? 0 : i);
    int y = editing_word_->y() + (editing_word_->direction() ? i : 0);
    auto cell = getCell(x, y);
    if (cell->letter().length() != 1 || cell->letter().at(0) != editing_word_->word().at(i)) return;
  }
  editing_word_->setAccepted(true);
  for (int i = 0; i < count; i++)
  {
    int x = editing_word_->x() + (editing_word_->direction() ? 0 : i);
    int y = editing_word_->y() + (editing_word_->direction() ? i : 0);
    auto cell = getCell(x, y);
    cell->setAccepted(true);
  }
}
