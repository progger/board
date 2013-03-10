/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 2.0
import "qrc:/lib/webview/qml"

Item {
    anchors.fill: parent
    WebPage {
        anchors.fill: parent
        webViewObject: WebViewObject
        url: ":/plugin/paint/web/page.html"
    }
}
