/*
 * Copyright (C) 2012 Kulabuhov Michael, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var qmlObjects = [];

function onUnloadPlugin() {
    for (var i in qmlObjects)
    {
        var obj = qmlObjects[i];
        obj.destroy();
    }
    qmlObjects.length = 0;
    board.Keys.forwardTo = qmlObjects;
}

function onAddPluginQml(path) {
    var component = Qt.createComponent(path);
    if (component.status == Component.Ready) {
        var obj = component.createObject(board);
        qmlObjects.push(obj);
        board.Keys.forwardTo = qmlObjects;
    }
    else {
        console.log(component.errorString());
    }
}

Core.unloadPlugin.connect(onUnloadPlugin);
Core.addPluginQml.connect(onAddPluginQml);
