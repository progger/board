/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var core = board.core;
var paint = board.plugin.paint;
var path_prc = board.plugin.path;

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

    paint.updateMode.connect(modeChange)
    paint.undo.connect(undo);
    paint.redo.connect(redo);
    paint.del.connect(del);
    paint.duplicate.connect(duplicate);
    paint.save.connect(save);

    modeChange();
    Diff.prepare();
}

function modeChange() {
    var cursor;
    switch (paint.mode) {
        case "pen":
        case "magic_pen":
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

    if (paint.mode != "select") {
        Select.hide();
    }

    if (paint.mode == "image") {
        paint.selectImage();
        if (!paint.imageContent) {
            paint.mode = "select";
        }
    }
}

function save() {
    var element = document.getElementById("content");
    var w = element.width.baseVal.value;
    var h = element.height.baseVal.value;
    var svg = "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"" + w + "\" height=\"" + h + "\">";
    var content = Diff.getContent();
    var i = content.indexOf(">");
    content = svg + content.substr(i + 1);
    paint.saveContent(content);
}

window.onload = main;
