/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

import QtQuick 1.1
import QtWebKit 1.0
import "webPage.js" as Script

WebView {
    id: webView
    property variant webViewObject
    preferredWidth: width
    preferredHeight: height
    pressGrabTime: 0
    onAlert: console.log("Web error: " + message)
    focus: true
    javaScriptWindowObjects: QtObject {
        id: webObject
        WebView.windowObjectName: "board"
        property variant core: Core
        property variant objects: []
    }

    Component.onCompleted: Script.init()
}
