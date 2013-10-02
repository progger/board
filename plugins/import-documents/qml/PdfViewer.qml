/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import board.core 2.0
import board.importdocuments 2.0
import "qrc:/core/qml"

PdfViewer {
    id: pdfViewer
    imageWidth: image.width
    imageHeight: image.height

    Rectangle {
        anchors.fill: parent
        color: "#808080"
        radius: 8

        Image {
            id: image
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: panel.top
            anchors.margins: 8
            source: pdfViewer.imageSource
            cache: false
            fillMode: Image.PreserveAspectFit
        }

        Item {
            id: panel
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 8
            height: 30
            enabled: pdfViewer.pageCount > 0

            Row {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 8

                Button {
                    width: height
                    height: parent.height
                    radius: height / 2
                    style: Style.normalButton
                    image: "qrc:/core/res/left_arrow.svg"
                    enabled: panel.enabled && pdfViewer.page > 0
                    onClicked: --pdfViewer.page
                }

                Text {
                    font.pixelSize: parent.height / 2
                    anchors.verticalCenter: parent.verticalCenter
                    text: (pdfViewer.page + 1) + " / " + pdfViewer.pageCount
                }

                Button {
                    width: height
                    height: parent.height
                    radius: height / 2
                    style: Style.normalButton
                    image: "qrc:/core/res/right_arrow.svg"
                    enabled: panel.enabled && pdfViewer.page < pdfViewer.pageCount - 1
                    onClicked: ++pdfViewer.page
                }
            }
        }
    }
}
