/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1

Rectangle {
    id: toolBar
    property variant style
    property int buttonSize: height - 6
    color: style.panelColor

    Row {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 4

        ColorSelector {
            style: toolBar.style
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height
        }

        Item {
            width: 16
            height: parent.height
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: toolBar.style.normalButton
            width: buttonSize
            height: buttonSize
            image: "qrc:/res/undo.svg"
            enabled: Core.canUndo
            onClicked: Core.undo()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: toolBar.style.normalButton
            width: buttonSize
            height: buttonSize
            image: "qrc:/res/redo.svg"
            enabled: Core.canRedo
            onClicked: Core.redo()
        }

        Item {
            width: 16
            height: parent.height
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: toolBar.style.normalButton
            enabled: Core.selected;
            width: buttonSize
            height: buttonSize
            image: "qrc:/res/delete.svg"
            onClicked: Core.del()
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: toolBar.style.normalButton
            enabled: Core.selected;
            width: buttonSize
            height: buttonSize
            image: "qrc:/res/duplicate.svg"
            onClicked: Core.duplicate()
        }

        Item {
            width: 16
            height: parent.height
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/res/thickness.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            anchors.verticalCenter: parent.verticalCenter
            width: 60
            height: buttonSize
            onValueChanged: Core.thickness = value
            step: 0.5
            minValue: 0.5
            maxValue: 10
            Component.onCompleted: value = Core.thickness
        }

        Item {
            width: 8
            height: parent.height
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            width: buttonSize
            source: "qrc:/res/font_size.svg"
            smooth: true
        }

        SpinBox {
            style: toolBar.style
            width: 60
            anchors.verticalCenter: parent.verticalCenter
            height: buttonSize
            onValueChanged: Core.fontSize = value
            step: 2
            minValue: 10
            maxValue: 60
            Component.onCompleted: value = Core.fontSize
        }

        Item {
            width: 8
            height: parent.height
        }

        Button {
            anchors.verticalCenter: parent.verticalCenter
            style: toolBar.style.normalButton
            width: buttonSize
            height: buttonSize
            image: "qrc:/res/save.svg"
            onClicked: Core.save()
        }
    }

    Button {
        x: parent.width - buttonSize - 4
        anchors.verticalCenter: parent.verticalCenter
        style: toolBar.style.closeButton
        width: buttonSize
        height: buttonSize
        image: "qrc:/res/close.svg"
        onClicked: Qt.quit()
    }
}
