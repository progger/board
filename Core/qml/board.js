var qmlObjects = [];

function onUnloadPlugin(plugin) {
    for (var i in qmlObjects)
    {
        var obj = qmlObjects[i];
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
