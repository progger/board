/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.2
import QtQuick.Controls 1.0
import board.core 2.0
import board.blackyellow 2.0

BlackYellowButton {
    id: blackYellowButton
    anchors.fill: parent

    Button {
        id: button
        style: Style.normalButton
        anchors.fill: parent
        tooltip: "Чёрное-желтое"
        iconSource: "qrc:/black-yellow/res/black-yellow.svg"
        onClicked: blackYellowButton.placeBlackYellow()
    }
}
