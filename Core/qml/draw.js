function onUnloadPlugin(obj) {
    webView.html = "";
    webObject.plugin = null;
}

function onAddWebViewPluginObject(name, obj) {
    var p = {};
    p[name] = obj;
    webObject.plugin = p;
}

function onLoadWebViewPage(url, obj) {
    webView.url = url;
}

Core.unloadPlugin.connect(onUnloadPlugin);
Core.addWebViewPluginObject.connect(onAddWebViewPluginObject);
Core.loadWebViewPage.connect(onLoadWebViewPage);
