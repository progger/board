/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import ":/lib/webview/qml"

Item {
    anchors.fill: parent
    WebPage {
        anchors.fill: parent
        webViewObject: WebViewObject
        url: ":/plugin/paint/web/page.html"
    }
}
