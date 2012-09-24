var webObjects = {};

function onUnloadPlugin(obj) {
    webView.html = "";
    webObject.plugin = null;
    webObjects = {};
}

function onaddPluginWebObject(name, obj) {
    webObjects[name] = obj;
    webObject.plugin = webObjects;
}

function onLoadWebViewPage(url, obj) {
    webView.url = url;
}

Core.unloadPlugin.connect(onUnloadPlugin);
Core.addPluginWebObject.connect(onaddPluginWebObject);
Core.loadWebViewPage.connect(onLoadWebViewPage);
