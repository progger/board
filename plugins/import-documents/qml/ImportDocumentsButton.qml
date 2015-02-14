/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import board.core 2.0
import board.importdocuments 2.0

Item {
    anchors.fill: parent

    Button {
        id: button
        style: Style.normalButton
        anchors.fill: parent
        tooltip: "импорт документа"
        iconSource: "qrc:/import-documents/res/import.svg"
        onClicked: openDialog.open()
    }

    FileDialog {
        id: openDialog
        modality: Qt.ApplicationModal
        selectExisting: true
        title: "Открыть документ"
        onAccepted: ImportDoc.importDoc(fileUrl)
    }
}
