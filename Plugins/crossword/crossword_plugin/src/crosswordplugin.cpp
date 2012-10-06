#include <QtPlugin>
#include "crosswordplugin.h"

void CrosswordPlugin::init(ICore *core, const QStringList &param)
{
  core->loadWebPage("qrc:/plugin/web/page.html");
}

Q_EXPORT_PLUGIN2(IPlugin, CrosswordPlugin)
