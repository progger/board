#include <QtPlugin>
#include "crossword.h"
#include "crosswordplugin.h"

void CrosswordPlugin::init(ICore *core, const QStringList &param)
{
  auto crossword = new Crossword(this);
  if (!crossword->init(param[0])) return;
  core->addObject("Crossword", crossword);
  core->addQml("qrc:/plugin/qml/Field.qml");
}

Q_EXPORT_PLUGIN2(IPlugin, CrosswordPlugin)
