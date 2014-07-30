/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Controls 1.0
import board.core 2.0
import board.categories 2.0

CategoriesButton {
    id: categoriesButton
    width: button.width

    Button {
        id: button
        anchors.verticalCenter: parent.verticalCenter
        style: Style.normalButton
        width: height
        height: parent.height - 6
        tooltip: "Категории"
        iconSource: "qrc:/categories/res/categories.svg"
        onClicked: categoriesButton.placeCategories()
    }
}
