/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0

Item {
    property real buttonWidth: 128
    property real imageHeigth: 128
    property real textHeight: 32
    property real buttonHeight: imageHeigth + textHeight
    property real buttonMargin: 8

    Rectangle {
        anchors.fill: parent
        color: "#80A080"
    }

   Rectangle  {
        id: backButton
        x: buttonMargin
        y: buttonMargin
        width: buttonWidth
        height: imageHeigth
        color: backButtonMouseArea.containsMouse ? "#E0E0E0" : "#404080"
        radius: 8
        smooth: true
        opacity: 0.5
        visible: !Core.isRootMenu

        Image {
            anchors.fill: parent
            source: "qrc:/core/res/back.svg"
        }

        MouseArea {
            id: backButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: Core.upMenu()
        }
    }

    GridView {
        id: pluginInfoGrid
        anchors.left: backButton.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: buttonMargin
        cellWidth: buttonWidth + buttonMargin
        cellHeight: buttonHeight + buttonMargin
        model: Core.menuItemList
        delegate: Item {
            id: gridDelegate
            width: buttonWidth
            height: buttonHeight

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: Core.selectMenuItem(modelData);
            }

            Rectangle {
                anchors.fill: parent
                color: mouseArea.containsMouse ? "#E0E0E0" : "#404080"
                radius: 8
                smooth: true
                opacity: 0.5
            }

            Image {
                id: buttonImage
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: imageHeigth
                source: modelData.image
                smooth: true
            }

            Item {
                id: buttonText
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: buttonImage.bottom
                anchors.bottom: parent.bottom

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: parent.height * 0.7
                    text: modelData.name
                    smooth: true
                }
            }
        }
    }
}
