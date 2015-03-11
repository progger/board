/*
 * Copyright (C) 2015 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.0
import board.core 2.0

Rectangle {
    color: "white"

    Item {
        id: sheetSettings
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2

        Column {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 8

            CheckBox {
                id: chbScrollable
                text: "Неограниченный лист"
                onCheckedChanged: Core.sheets[Core.sheetIndex].scrollable = checked
            }

            Row {
                spacing: 8

                Label {
                    id: colorLabel
                    text: "Цвет:"
                }

                Rectangle {
                    id: colorRect
                    width: 50
                    height: colorLabel.height
                    border.color: "black"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: colorDialog.open()
                    }

                    ColorDialog {
                        id: colorDialog
                        color: colorRect.color
                        onAccepted: {
                            Core.sheets[Core.sheetIndex].color = color
                            colorRect.color = color
                        }
                    }
                }
            }

            Row {
                spacing: 8

                Label {
                    id: imageLabel
                    height: 28
                    verticalAlignment: Text.AlignVCenter
                    text: "Фоновое изображение"
                }

                Button {
                    width: height
                    height: imageLabel.height
                    style: Style.normalButton
                    iconSource: "qrc:/core/res/open.svg"
                    onClicked: openImageDialog.open()
                }

                Button {
                    width: height
                    height: imageLabel.height
                    style: Style.normalButton
                    iconSource: "qrc:/core/res/delete.svg"
                    onClicked: {
                        Core.sheets[Core.sheetIndex].deleteImage()
                        updateImage()
                    }
                }

                FileDialog {
                    id: openImageDialog
                    modality: Qt.ApplicationModal
                    nameFilters: ["Image files (*.png *.jpg *.jpeg *.tif *.tiff *.gif *.svg)"]
                    selectExisting: true
                    title: "Открыть изображение"
                    onAccepted: {
                        Core.sheets[Core.sheetIndex].selectImage(fileUrl)
                        updateImage()
                    }
                }
            }

            Row {
                id: imageRow
                spacing: 8

                Image {
                    id: image
                    width: 100
                    height: 100
                }

                Column {
                    spacing: 8

                    RadioButton {
                        id: imageModeNormal
                        text: "нормально"
                        exclusiveGroup: imageModeGroup
                        onCheckedChanged: if (checked) Core.sheets[Core.sheetIndex].imageMode = 0
                    }

                    RadioButton {
                        id: imageModeStretch
                        text: "растянуть"
                        exclusiveGroup: imageModeGroup
                        onCheckedChanged: if (checked) Core.sheets[Core.sheetIndex].imageMode = 1
                    }

                    RadioButton {
                        id: imageModeTile
                        text: "плиткой"
                        exclusiveGroup: imageModeGroup
                        onCheckedChanged: if (checked) Core.sheets[Core.sheetIndex].imageMode = 2
                    }

                    ExclusiveGroup {
                        id: imageModeGroup
                    }
                }
            }

            Button {
                width: 200
                height: 28
                style: Style.normalButton
                text: "Применить ко всем"
                onClicked: {
                    var cur = Core.sheets[Core.sheetIndex]
                    for (var i in Core.sheets)
                    {
                        var sheet = Core.sheets[i]
                        sheet.copySettings(cur)
                    }
                }
            }
        }
    }

    Connections {
        target: Core
        onSheetIndexChanged: {
            var sheet = Core.sheets[Core.sheetIndex]
            chbScrollable.checked = sheet.scrollable
            colorRect.color = sheet.color
            updateImage()
        }
    }

    function updateImage() {
        var sheet = Core.sheets[Core.sheetIndex]
        imageRow.visible = sheet.imageSource ? true : false
        image.source = sheet.imageSource
        switch (sheet.imageMode) {
        case 0:
            imageModeNormal.checked = true
            break
        case 1:
            imageModeStretch.checked = true
            break
        case 2:
            imageModeTile.checked = true
            break
        }
    }

    MouseArea {
        z: -1
        anchors.fill: parent
    }
}
