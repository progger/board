/*
 * Copyright (C) 2014 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.2
import QtQuick.Controls 1.0
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

                        Text {
                            id: header
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            height: parent.height * 0.2

                            Text {
                                anchors.centerIn: parent
                                font.pixelSize: parent.height * 0.8
                                text: mdl.name
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
                        }

                        DropArea {
                            anchors.fill: parent
                            onDropped: {
                                var item = drop.source.mdl
                                removeItemFromCategories(item)
                                mdl.addItem(item)
                                categories.updateRemainingItems()
                                updateResult()
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

                        Repeater {
                            model: categories.remainingItems
                            delegate: card
                        }
                    }

                    DropArea {
                        anchors.fill: parent
                        onDropped: {
                            var item = drop.source.mdl
                            removeItemFromCategories(item)
                            categories.updateRemainingItems()
                            updateResult()
                        }
                    }
                }

                Component {
                    id: card

                    Image {
                        property variant mdl: modelData
                        width: (column.width / categories.items.length) - 8
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
                    }
                }
            }
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
        console.log(categories.remainingItems.length)
        console.log(categories.checkResult())
        if (categories.remainingItems.length > 0)
            place.color = "#202060"
        else if (categories.checkResult())
            place.color = "#206020"
        else
            place.color = "#602020"
    }
}
