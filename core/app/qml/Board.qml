/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.1
import board.core 2.0

Window {
    id: board
    color: Core.transparent ? "transparent" : "white"
    Behavior on color {
        ColorAnimation { duration: 300 }
    }

    width: 400
    height: 300

    ToolBar {
        id: toolBar
        z: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: Style.panelSize
    }

    Settings {
        id: settings
        z: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
        opacity: 0
        enabled: opacity
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }
    }

    ModeBar {
        z: 2
        x: 10
        y: (parent.height - height) / 2
    }

    Repeater {
        model: Core.panels
        PanelQml {
            z: 2
            panel: modelData
        }
    }

    Item {
        id: sheetPlace
        objectName: "sheetPlace"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
    }

    Keyboard {
        id: keyboard
        z: 1
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: board.height / 4
        opacity: Core.keyboard
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }

        Component.onCompleted: enabled = Qt.binding(function() { return Core.keyboard })
    }

    ErrorMessageBox {
        id: errorMessageBox
        Component.onCompleted: Core.errorMessageBox.connect(openErrorMessageBox)

        function openErrorMessageBox(error) {
            errorMessageBox.error = error
            errorMessageBox.show()
        }
    }

    property bool closeQuestion: true

    CloseCaution {
        id: closeCaution
        onCloseApp: {
            closeQuestion = false
            board.close()
        }
        onSave: saveBookDialog.open()
    }

    FileDialog {
        id: saveBookDialog
        modality: Qt.ApplicationModal
        nameFilters: ["Book files (*.brd)"]
        selectExisting: false
        title: "Сохранить книгу"
        onAccepted: Core.saveBook(fileUrl)
    }

    onClosing: {
        if (closeQuestion && Core.hasChanges) {
            closeCaution.show()
            close.accepted = false
        }
    }
}
