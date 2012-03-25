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
}

window.onload = main;
