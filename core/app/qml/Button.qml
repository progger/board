/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0

Rectangle {
    id: button
    property variant style
    property string image
    property string text
    property bool pressed: false
    property bool toggled: false
    property bool enabled: true
    signal clicked()

    radius: 8
    border.color: enabled ? mouseArea.containsMouse ? "#4040FF" : "#404040" : "#808080"
    border.width: enabled ? mouseArea.containsMouse ? 4 : 2 : 1
    smooth: true
    gradient: style.normal
    state: ""

    states: [
        State {
            name: "disabled"
            when: !enabled
            PropertyChanges {
                target: button
                gradient: style.disabled
            }
        },
        State {
            name: "pressed"
            when: toggled || (pressed && mouseArea.containsMouse)
            PropertyChanges {
                target: button
                gradient: style.pressed
            }
        },
        State {
            name: "hovered"
            when: mouseArea.containsMouse
            PropertyChanges {
                target: button
                gradient: style.hovered
            }
        }
    ]

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        enabled: button.enabled
        onPressedChanged: button.pressed = pressed
        onClicked: if (enabled) button.clicked()
    }

    Image {
        anchors.fill: parent
        anchors.margins: 3
        source: image
        smooth: true
    }

    Text {
        anchors.centerIn: parent
        font.pixelSize: parent.height / 2
        text: button.text
        smooth: true
    }
}
