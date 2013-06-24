/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core 2.0
import board.importdocuments 2.0
import "qrc:/core/qml"

Item {
    width: button.width

    Button {
        id: button
        anchors.verticalCenter: parent.verticalCenter
        style: Style.normalButton
        width: height
        height: parent.height - 6
        image: "qrc:/import-documents/res/import.svg"
        onClicked: ImportDoc.importDoc()
    }
}
