function onAddWebViewObject(name, obj) {
    //TODO
}

function onLoadPage(page) {
    webView.url = page;
}

Core.addWebViewObject.connect(onAddWebViewObject);
Core.loadPage(onLoadPage);
