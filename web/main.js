/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

function main() {
    var canvas = document.getElementById("canvas");
    canvas.state = false;
    canvas.onmousedown = canvas_onMouseDown;
    canvas.onmouseup = canvas_onMouseUp;
    canvas.onmousemove = canvas_onMouseMove;
    canvas.onmouseout = canvas_onMouseOut;
    canvas.onkeydown = canvas_onKeyDown;
    canvas.onkeypress = canvas_onKeyPress;

    var cursor = document.getElementById("text_cursor");
    function blink() {
        var b = cursor.getAttribute("display") == "none";
        cursor.setAttribute("display", b ? "inline" : "none");
    }
    setInterval(blink, 500);

    board.core.updateMode.connect(modeChange)
    modeChange();
}

function modeChange() {
    var cursor;
    switch (board.core.mode) {
        case "pen":
        case "rectangle":
        case "circle":
        case "ellipse":
            cursor = "crosshair";
            break;
        case "text":
            cursor = "text";
            break;
        default:
            cursor = "default";
            break;
    }
    var canvas = document.getElementById("canvas");
    canvas.style.setProperty("cursor", cursor);
}

window.onload = main;
