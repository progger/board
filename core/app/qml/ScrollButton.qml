/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0

Rectangle {
    id: scrollButton
    property string source
    signal pressed()
    border.width: 1

    Image {
        anchors.fill: parent
        source: scrollButton.source
    }

    MouseArea {
        anchors.fill: parent
        onPressed: uptimer.running = true
        onReleased: uptimer.running = false

        Timer {
            id: uptimer
            interval: 20
            repeat: true
            triggeredOnStart: true
            onTriggered: scrollButton.pressed()
        }
    }
}
