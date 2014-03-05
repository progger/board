/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core 2.0

Panel {
    property int buttonWidth: Math.max.apply(Math, actions)
    width: 100
    height: 100

    Rectangle {
        anchors.fill: parent
        color: Style.panelColor
    }

    Component.onCompleted: console.log(buttonWidth)
}