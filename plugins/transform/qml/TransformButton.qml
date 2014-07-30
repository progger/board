/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Controls 1.0
import board.core 2.0
import board.transform 2.0

TransformButton {
    id: transformButton
    width: button.width

    Button {
        id: button
        anchors.verticalCenter: parent.verticalCenter
        style: Style.normalButton
        width: height
        height: parent.height - 6
        tooltip: "Преобразование"
        iconSource: "qrc:/transform/res/transform.svg"
        onClicked: transformButton.placeTransform()
    }
}
