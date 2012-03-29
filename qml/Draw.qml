/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import QtWebKit 1.0

WebView {
    id: webView
    url: "qrc:/web/page.html"
    pressGrabTime: 0
    onAlert: console.log("Web error: " + message)
    focus: true

    javaScriptWindowObjects: QtObject {
        WebView.windowObjectName: "board"
        property variant core: Core
    }
}
