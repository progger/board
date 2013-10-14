/*
 * Copyright (C) 2013 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.1

Rectangle {
    id: scrollBar
    property bool horizontal: true
    property real position: 0
    property real length: 1
    signal leftButton();
    signal rightButton();
    signal leftPage();
    signal rightPage();
    signal move(real step);
    color: "#C0C0C0"
    border.width: 1

    ScrollButton {
        id: leftButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: !scrollBar.horizontal ? parent.right : undefined
        anchors.bottom: scrollBar.horizontal ? parent.bottom : undefined
        width: scrollBar.horizontal ? height : undefined
        height: !scrollBar.horizontal ? width : undefined
        source: scrollBar.horizontal
                ? "qrc:/core/res/left_arrow.svg"
                : "qrc:/core/res/up_arrow.svg"
        onPressed: scrollBar.leftButton();
    }

    ScrollButton {
        id: rightButton
        anchors.left: !scrollBar.horizontal ? parent.left : undefined
        anchors.top: scrollBar.horizontal ? parent.top : undefined
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: scrollBar.horizontal ? height : undefined
        height: !scrollBar.horizontal ? width : undefined
        source: scrollBar.horizontal
                ? "qrc:/core/res/right_arrow.svg"
                : "qrc:/core/res/down_arrow.svg"
        onPressed: scrollBar.rightButton();
    }

    Item {
        anchors.left: scrollBar.horizontal ? leftButton.right : parent.left
        anchors.top: !scrollBar.horizontal ? leftButton.bottom : parent.top
        anchors.right: scrollBar.horizontal ? rightButton.left : parent.right
        anchors.bottom: !scrollBar.horizontal ? rightButton.top : parent.bottom
        clip: true

        Rectangle {
            id: slider
            anchors.left: !scrollBar.horizontal ? parent.left : undefined
            anchors.top: scrollBar.horizontal ? parent.top : undefined
            anchors.right: !scrollBar.horizontal ? parent.right : undefined
            anchors.bottom: scrollBar.horizontal ? parent.bottom : undefined
            x: scrollBar.horizontal ? scrollBar.position * parent.width : 0
            y: !scrollBar.horizontal ? scrollBar.position * parent.height : 0
            width: scrollBar.horizontal ? scrollBar.length * parent.width : undefined
            height: !scrollBar.horizontal ? scrollBar.length * parent.height : undefined
            color: "#E0E0E0"
            border.width: 1

            MouseArea {
                property int start
                anchors.fill: parent
                hoverEnabled: true
                onPressed: start = scrollBar.horizontal ? mouse.x : mouse.y
                onPositionChanged: posChanged(mouse)

                function posChanged(mouse) {
                     if (mouse.buttons & Qt.LeftButton) {
                         var pos = scrollBar.horizontal ? mouse.x : mouse.y;
                         var size = scrollBar.horizontal ? slider.width : slider.height;
                         var step = (pos - start) / size;
                         if (scrollBar.position + step < 0)
                             step = -scrollBar.position;
                         if (scrollBar.position + scrollBar.length + step > 1)
                             step = 1 - scrollBar.position - scrollBar.length;
                         scrollBar.move(step);
                     }
                }
            }
        }

        MouseArea {
            z: -1
            anchors.fill: parent
            onClicked:
                if (scrollBar.horizontal
                        ? mouse.x <= slider.x : mouse.y <= slider.y)
                    scrollBar.leftPage()
                else
                    scrollBar.rightPage()
        }
    }
}
