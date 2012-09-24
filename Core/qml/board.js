var qmlObjects = [];

function onUnloadPlugin(obj) {
    for (i in qmlObjects)
    {
        obj = qmlObjects[i];
        console.log("destroy: " + obj);
        obj.destroy();
    }
    qmlObjects.length = 0;
}

function onAddPluginQml(path) {
    var component = Qt.createComponent(path);
    if (component.status == Component.Ready) {
        var obj = component.createObject(board);
        qmlObjects.push(obj);
    }
    else {
        console.log(component.errorString());
    }
}

Core.unloadPlugin.connect(onUnloadPlugin);
Core.addPluginQml.connect(onAddPluginQml);
