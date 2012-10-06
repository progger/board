#ifndef CROSSWORDPLUGIN_H
#define CROSSWORDPLUGIN_H

#include <QObject>
#include "iplugin.h"

class CrosswordPlugin : public QObject, public IPlugin
{
  Q_OBJECT
  Q_INTERFACES(IPlugin)
public:
  virtual ~CrosswordPlugin() {}
  virtual void init(ICore *core, const QStringList &param);
};

#endif // CROSSWORDPLUGIN_H
