/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import board.core 2.0

Window {
    id: dialog
    property string error
    width: Math.max(text.width, button.width) + 16
    height: button.y + button.height + 8
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    modality: Qt.ApplicationModal
    flags: Qt.Dialog | Qt.WindowCloseButtonHint
    color: Style.panelColor
    title: "Ошибка"


    Text {
        id: text
        anchors.horizontalCenter: parent.horizontalCenter
        y: 8
        text: dialog.error
    }

    Button {
        id: button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: text.bottom
        anchors.topMargin: 8
        width: 64
        height: 28
        style: Style.normalButton
        text: "OK"
        onClicked: dialog.close()
    }
}
