/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.0
import board.core 2.0
import board.categories 2.0

Categories {
    id: categories

    Rectangle {
        anchors.fill: parent
        color: "#804020"
        radius: 16

        Rectangle {
            id: place
            anchors.fill: parent
            anchors.margins: 16
            color: "#202060"
            clip: true
            radius: 12

            Column {
                id: column
                anchors.fill: parent
                anchors.margins: 8

                Repeater {
                    model: categories.categories
                    delegate: Item {
                        property variant mdl: modelData
                        width: column.width
                        height: column.height / (categories.categories.length + 1)

                        Item {
                            id: header
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            height: parent.height * 0.2

                            TextInput {
                                id: categoryName
                                anchors.centerIn: parent
                                font.pixelSize: parent.height * 0.8
                                readOnly: !editButton.checked
                                color: !editButton.checked ? "white" : "yellow"
                                text: mdl.name
                                onEditingFinished: {
                                    mdl.name = text
                                    categories.saveItems()
                                }
                            }

                            Button {
                                anchors.top: categoryName.top
                                anchors.bottom: categoryName.bottom
                                anchors.left: categoryName.right
                                anchors.leftMargin: 8
                                width: height
                                style: Style.normalButton
                                visible: editButton.checked
                                iconSource: "qrc:/core/res/delete.svg"
                                tooltip: "Удалить"
                                onClicked: categories.removeCategory(mdl)
                            }
                        }

                        Row {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: header.bottom
                            anchors.bottom: parent.bottom
                            spacing: 8

                            Repeater {
                                model: mdl.items
                                delegate: card
                            }

                            Button {
                                width: Style.buttonSize
                                height: Style.buttonSize
                                style: Style.normalButton
                                visible: editButton.checked
                                iconSource: "qrc:/core/res/add.svg"
                                tooltip: "Добавить"
                                onClicked: {
                                    openImageDialog.category = mdl
                                    openImageDialog.open()
                                }
                            }
                        }

                        DropArea {
                            anchors.fill: parent
                            onDropped: {
                                var item = drop.source.mdl
                                if (editButton.checked) {
                                    item.setCategory(mdl)
                                    categories.fillCategoriesItems()
                                } else {
                                    removeItemFromCategories(item)
                                    mdl.addItem(item)
                                    categories.updateRemainingItems()
                                    updateResult()
                                }
                            }
                        }
                    }
                }

                Item {
                    width: column.width
                    height: column.height / (categories.categories.length + 1)

                    Row {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        height: parent.height * 0.8
                        spacing: 8
                        visible: !editButton.checked

                        Repeater {
                            model: categories.remainingItems
                            delegate: card
                        }
                    }

                    DropArea {
                        anchors.fill: parent
                        onDropped: {
                            var item = drop.source.mdl
                            if (editButton.checked) {
                                categories.removeItem(item)
                                categories.saveItems()
                            } else {
                                removeItemFromCategories(item)
                                categories.updateRemainingItems()
                                updateResult()
                            }
                        }
                    }

                    Button {
                        y: 8
                        width: Style.buttonSize
                        height: Style.buttonSize
                        style: Style.normalButton
                        visible: editButton.checked
                        iconSource: "qrc:/core/res/add.svg"
                        tooltip: "Добавить"
                        onClicked: categories.addCategory()
                    }
                }

                Component {
                    id: card

                    Image {
                        property variant mdl: modelData
                        width: Math.min(column.width / (categories.items.length + editButton.checked) - 8, height)
                        height: parent.height
                        source: mdl.source

                        Drag.active: dragArea.drag.active
                        Drag.hotSpot.x: width / 2
                        Drag.hotSpot.y: height / 2

                        MouseArea {
                            id: dragArea
                            anchors.fill: parent
                            drag.target: parent
                            onReleased: parent.Drag.drop()
                        }

                        Button {
                            anchors.top: parent.top
                            anchors.right: parent.right
                            width: Style.buttonSize
                            height: Style.buttonSize
                            style: Style.normalButton
                            visible: editButton.checked
                            iconSource: "qrc:/core/res/delete.svg"
                            tooltip: "Удалить"
                            onClicked: categories.removeItem(mdl)
                        }
                    }
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
                onCheckedChanged: {
                    if (checked) {
                        categories.fillCategoriesItems()
                        updateResult()
                    } else {
                        categories.clearCategoriesItems()
                        categories.shuffle()
                        updateResult()
                    }
                }
            }
        }
    }

    FileDialog {
        id: openImageDialog
        property variant category
        modality: Qt.ApplicationModal
        nameFilters: ["Image files (*.png *.jpg *.jpeg *.tif *.tiff *.gif *.svg)"]
        selectExisting: true
        title: "Открыть изображение"
        onAccepted: {
            categories.addItem(category, fileUrl)
            categories.fillCategoriesItems()
        }
    }

    function removeItemFromCategories(item)
    {
        for (var i in categories.categories)
        {
            var category = categories.categories[i]
            category.removeItem(item)
        }
    }

    function updateResult() {
        if (editButton.checked || categories.remainingItems.length > 0)
            place.color = "#202060"
        else if (categories.checkResult())
            place.color = "#206020"
        else
            place.color = "#602020"
    }
}
