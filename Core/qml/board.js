var toolBar = null;
var modeBar = null;

function onUnloadPlugin(obj) {
    if (toolBar) {
        toolBar.destroy();
        toolBar = null;
    }
    if (modeBar) {
        modeBar.destroy();
        modeBar = null;
    }
}

function onLoadPlugin(obj) {
    var component = Qt.createComponent("qrc:/plugin/qml/ToolBar.qml");
    if (component.status == Component.Ready) {
        toolBar = component.createObject(toolBarRect);
    }
    else {
        console.log(component.errorString());
    }

    component = Qt.createComponent("qrc:/plugin/qml/ModeBar.qml");
    if (component.status == Component.Ready) {
        modeBar = component.createObject(modeBarRect);
    }
    else {
        console.log(component.errorString());
    }
}

Core.unloadPlugin.connect(onUnloadPlugin);
Core.loadPlugin.connect(onLoadPlugin);
