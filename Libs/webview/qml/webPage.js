/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var objects = {};

function onAddObject(name, obj) {
    objects[name] = obj;
    webObject.objects = objects;
}

function init() {
    webView.webViewObject.addObject.connect(onAddObject);
}
