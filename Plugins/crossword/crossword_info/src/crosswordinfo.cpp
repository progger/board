/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include <QtPlugin>
#include "crosswordinfo.h"

const QString CrosswordPlugin = "crossword";
const QString CrosswordName = "Кроссворд";
const QString CrosswordLogo = ":/plugin_info/crossword/res/logo.svg";
const QString CrosseditPlugin = "crossedit";
const QString CrosseditName = "Редактор";
const QString CrosseditLogo = ":/plugin_info/crossword/res/edit_logo.svg";

void CrosswordInfo::init(ICore *core, QString menu_path)
{
  if (menu_path.isEmpty())
  {
    core->addPlugin(CrosswordName, CrosswordLogo);
  }
  else if (menu_path == CrosswordName)
  {
    core->addPlugin("Зима", CrosswordLogo, CrosswordPlugin, QStringList(":/plugin/crossword/res/winter.txt"));
    QDir dir = core->rootDir();
    dir.cd(CrosswordPlugin);
    if (!dir.exists()) return;
    auto files = dir.entryInfoList(QStringList("*.txt"), QDir::Files);
    for (QFileInfo file : files)
    {
      auto name = file.completeBaseName();
      QFileInfo svg_file(dir, name + ".svg");
      auto image = svg_file.exists() ? "file:" + svg_file.filePath() : CrosswordLogo;
      core->addPlugin(name, image, CrosswordPlugin, QStringList(file.filePath()));
    }
    core->addPlugin(CrosseditName, CrosseditLogo, CrosseditPlugin);
  }
}

Q_EXPORT_PLUGIN2(IPluginInfo, CrosswordInfo)
