#include <QtPlugin>
#include "crossword.h"
#include "crosswordplugin.h"

void CrosswordPlugin::init(ICore *core, const QStringList &param)
{
  auto crossword = new Crossword(this);
  crossword->init(param[0]);
  core->loadWebPage("qrc:/plugin/web/page.html");
  core->addObject("Crossword", crossword);
  core->addWebObject("crossword", crossword);
}

Q_EXPORT_PLUGIN2(IPlugin, CrosswordPlugin)
