/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    id: button
    property variant style
    property string image
    property string text
    property bool pressed: false
    property bool toggled: false
    signal clicked()

    radius: 8
    border.color: mouseArea.containsMouse ? "#4040FF" : "#404040"
    border.width: mouseArea.containsMouse ? 4 : 2
    smooth: true
    gradient: style.gradientButtonNormal
    state: ""

    states: [
        State {
            name: "pressed"
            when: toggled || (pressed && mouseArea.containsMouse)
            PropertyChanges {
                target: button
                gradient: style.gradientButtonPressed
            }
        },
        State {
            name: "hovered"
            when: mouseArea.containsMouse
            PropertyChanges {
                target: button
                gradient: style.gradientButtonHovered
            }
        }
    ]

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onPressedChanged: button.pressed = pressed
        onClicked: button.clicked()
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
