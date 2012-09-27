var libObjects = {};
var pluginObjects = {};

function onUnloadPlugin() {
    webView.html = "";
    webObject.plugin = null;
    pluginObjects = {};
}

function onAddLibWebObject(name, obj) {
    libObjects[name] = obj;
    webObject.lib = libObjects;
}

function onAddPluginWebObject(name, obj) {
    pluginObjects[name] = obj;
    webObject.plugin = pluginObjects;
}

function onLoadWebViewPage(url, obj) {
    webView.url = url;
}

Core.unloadPlugin.connect(onUnloadPlugin);
Core.addPluginWebObject.connect(onAddPluginWebObject);
Core.addLibWebObject.connect(onAddLibWebObject);
Core.loadWebViewPage.connect(onLoadWebViewPage);
