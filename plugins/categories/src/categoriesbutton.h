/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef CATEGORIESBUTTON_H
#define CATEGORIESBUTTON_H

#include <QQuickItem>

class CategoriesButton : public QQuickItem
{
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(CategoriesButton)
public:
  explicit CategoriesButton(QQuickItem *parent = nullptr);
  ~CategoriesButton() override = default;
public slots:
  void placeCategories();
};

#endif // CATEGORIESBUTTON_H
