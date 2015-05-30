import QtQuick 2.0
import QtWebKit 3.0
import board.mimio 2.0

SwfPlayer {
    id: swfPlayer
    WebView {
        id: webView
        anchors.fill: parent
        url: swfPlayer.hash ? "http://127.0.0.1:" + swfPlayer.port + "/html:" + swfPlayer.hash : ""
        onLoadingChanged: {
            if (!loading)
            {
                swfPlayer.width += 1
                swfPlayer.width -= 1
            }
        }
    }
}
