/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0

Rectangle {
    id: spinBox
    property variant style
    property real value: 0
    property real step: 1
    property real minValue: 0
    property real maxValue: 100
    property int lineCount: (maxValue - minValue) / step + 1
    property real itemHeight: textBar.height / 2
    border.width: 2
    border.color: "black"
    color: "white"
    radius: 4

    Item {
        id: textBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: buttons.left

        Text {
            anchors.centerIn: parent
            font.pixelSize: parent.height / 2
            text: value.toPrecision(2);
            smooth: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: selectBar.opacity = !selectBar.opacity
        }
    }

    Item {
        id: buttons
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.height / 2

        Button {
            style: spinBox.style.normalButton
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.verticalCenter
            width: height
            radius: 4
            image: "qrc:/core/res/up_arrow.svg"
            onClicked: value = Math.min(value + step, maxValue)
        }

        Button {
            style: spinBox.style.normalButton
            anchors.right: parent.right
            anchors.top: parent.verticalCenter
            anchors.bottom: parent.bottom
            width: height
            radius: 4
            image: "qrc:/core/res/down_arrow.svg"
            onClicked: value = Math.max(value - step, minValue)
        }
    }

    Rectangle {
        id: selectBar
        z: 1
        anchors.top: parent.bottom
        anchors.left: parent.left
        width: textBar.width
        height: itemHeight * lineCount
        border.width: 2
        border.color: "black"
        gradient: Gradient {
            GradientStop { position: 0; color: "#C0C0C0" }
            GradientStop { position: 1; color: "#F0F0F0" }
        }
        smooth: true
        opacity: 0

        Repeater {
            model: lineCount

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                y: itemHeight * modelData
                height: itemHeight

                Text {
                    anchors.centerIn: parent
                    text: (minValue + step * modelData).toPrecision(2)
                    smooth: true
                }

                MouseArea {
                    anchors.fill: parent
                    enabled: selectBar.opacity
                    onClicked: {
                               value = minValue + step * modelData;
                               selectBar.opacity = 0;
                    }
                }
            }
        }

        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }
    }
}
