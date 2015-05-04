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
        selectExisting: false
        title: "Сохранить книгу"
        onAccepted: Core.saveBook(fileUrl)
        Component.onCompleted: buildNameFilters()

        function buildNameFilters() {
            nameFilters = []
            for (var i in Core.exporters) {
                var exporter = Core.exporters[i]
                nameFilters.push(exporter.name + " (*." + exporter.suffix + ")")
            }
        }
    }

    Connections {
        target: Core
        onExportersChanged: saveBookDialog.buildNameFilters()
    }

    FileDialog {
        id: openBookDialog
        modality: Qt.ApplicationModal
        selectExisting: true
        title: "Открыть книгу"
        onAccepted: Core.openBook(fileUrl)
        Component.onCompleted: buildNameFilters()

        function buildNameFilters() {
            var filters = []
            var suffixes = []
            for (var i in Core.importers) {
                var importer = Core.importers[i]
                var filter = "*." + importer.suffix
                suffixes.push(filter)
                filters.push(importer.name + " (" + filter + ")")
            }
            filters.unshift("All supported (" + suffixes.join(" ") + ")")
            nameFilters = filters
        }
    }

    Connections {
        target: Core
        onImportersChanged: openBookDialog.buildNameFilters()
    }

    onClosing: {
        if (closeQuestion && Core.hasChanges) {
            closeCaution.show()
            close.accepted = false
        }
    }

}
