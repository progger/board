/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#include "global.h"
#include "categories.h"
#include "categoriesbutton.h"
#include "plugin.h"

Plugin::Plugin(QObject *parent) :
  QObject(parent)
{
}

void Plugin::init()
{
  qmlRegisterType<Categories>("board.categories", 2, 0, "Categories");
  qmlRegisterType<CategoriesButton>("board.categories", 2, 0, "CategoriesButton");
  qmlRegisterAnonymousType<Category>("board.categories", 1);
  qmlRegisterAnonymousType<CategoryItem>("board.categories", 1);
  QQmlComponent *component = g_core->getComponent("qrc:/categories/qml/CategoriesButton.qml");
  g_core->registerTool("categories", "common", component, 1, 1);
  g_core->paint()->RegisterShape("categories", []() -> Shape* { return static_cast<Shape*>(g_core->getComponent("qrc:/categories/qml/Categories.qml")->create()); });
}
