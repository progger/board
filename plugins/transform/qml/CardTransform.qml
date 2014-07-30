/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import board.core 2.0
import board.transform 2.0

CardTransform {
    id: cardTransform

    Rectangle {
        anchors.fill: parent
        color: "#804020"
        radius: 16

        Rectangle {
            id: place
            anchors.fill: parent
            anchors.margins: 16
            color: "#206020"
            clip: true
            radius: 12

            Item {
                id: cardPlace
                anchors.fill: parent
                anchors.margins: parent.width / 10
                visible: !editButton.checked

                Repeater {
                    model: cardTransform.cards
                    delegate: Image {
                        id: image
                        z: -index - 1
                        width: cardPlace.width / 4
                        height: cardPlace.height * 0.7
                        anchors.verticalCenter: cardPlace.verticalCenter
                        source: "qrc:/transform/res/cardQ.svg"

                        MouseArea {
                           anchors.fill: parent
                           onClicked: {
                               image.z = 0
                               image.source = modelData.leftSource
                               timer.start()
                           }
                        }

                        Timer {
                            id: timer
                            interval: 3000
                            onTriggered: anim1.start()
                        }

                        PropertyAnimation {
                            id: anim1
                            target: image
                            property: "x"
                            from: 0
                            to: (cardPlace.width - image.width) / 2
                            easing.type: "InOutCubic"
                            duration: 2000
                            onStopped: {
                                image.source = modelData.rightSource
                                anim2.start()
                            }
                        }

                        PropertyAnimation {
                            id: anim2
                            target: image
                            property: "x"
                            from: (cardPlace.width - image.width) / 2
                            to: cardPlace.width - image.width
                            easing.type: "InOutCubic"
                            duration: 2000
                            onStopped: image.z = -cardTransform.cards.lenght + index
                        }
                    }
                }

                Rectangle {
                    z: 1
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    x: (parent.width - width) / 2
                    width: parent.width / 3.5
                    radius: 8
                    color: "#A0A0A0"
                }
            }

            GridView {
                id: gridView
                anchors.fill: parent
                anchors.margins: 8
                cellWidth: width / 2
                cellHeight: height / 2.2
                visible: editButton.checked
                model: cardTransform.cards
                delegate: Item {
                    width: gridView.cellWidth
                    height: gridView.cellHeight

                    Rectangle {
                        anchors.fill: parent
                        anchors.margins: 8
                        radius: 4
                        color: "#C0C0C0"

                        Item {
                            anchors.left: parent.left
                            anchors.right: deleteButton.left
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom

                            Image {
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                anchors.left: parent.left
                                anchors.margins: 4
                                width: parent.width / 2 - 6
                                source: modelData.leftSource

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: leftImageFileDialog.open();
                                    FileDialog {
                                        id: leftImageFileDialog
                                        modality: Qt.ApplicationModal
                                        nameFilters: ["Image files (*.png *.jpg *.jpeg *.tif *.tiff *.gif *.svg)"]
                                        selectExisting: true
                                        title: "Открыть изображение"
                                        onAccepted: cardTransform.setCardLeftImage(index, fileUrl)
                                    }
                                }
                            }

                            Image {
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                anchors.right: parent.right
                                anchors.margins: 4
                                width: parent.width / 2 - 6
                                source: modelData.rightSource

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: rightImageFileDialog.open();
                                    FileDialog {
                                        id: rightImageFileDialog
                                        modality: Qt.ApplicationModal
                                        nameFilters: ["Image files (*.png *.jpg *.jpeg *.tif *.tiff *.gif *.svg)"]
                                        selectExisting: true
                                        title: "Открыть изображение"
                                        onAccepted: cardTransform.setCardRightImage(index, fileUrl)
                                    }
                                }
                            }
                        }

                        Button {
                            id: deleteButton
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.margins: 4
                            width: Style.buttonSize
                            height: Style.buttonSize
                            style: Style.normalButton
                            visible: editButton.checked
                            iconSource: "qrc:/core/res/delete.svg"
                            tooltip: "Удалить"
                            onClicked: cardTransform.removeItem(index)
                        }
                    }
                }

                footer: Button {
                    width: Style.buttonSize
                    height: Style.buttonSize
                    style: Style.normalButton
                    visible: editButton.checked
                    iconSource: "qrc:/core/res/add.svg"
                    tooltip: "Добавить"
                    onClicked: cardTransform.addItem()
                }
            }

            Button {
                id: editButton
                anchors.top: parent.top
                anchors.right: parent.right
                width: Style.buttonSize
                height: Style.buttonSize
                checkable: true
                style: Style.normalButton
                iconSource: "qrc:/core/res/pen.svg"
                tooltip: "Редактировать"
            }
        }
    }
}
