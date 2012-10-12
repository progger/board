#include "row.h"

Row::Row(QObject *parent) :
  QObject(parent),
  cells_()
{
}

void Row::addCell(QObject *cell)
{
  cells_.append(cell);
}
