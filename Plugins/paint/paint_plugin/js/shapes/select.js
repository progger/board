/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

.import "../tool.js" as Tool

var canvas;
var objects;
var selectedObjects = [];
var selectRect = null;
var changeMode = null;
var lastPoint = null;
var emptyContainer = { paint: function() {} };

var bobberModes = ["lt", "ct", "rt",
                   "lc",       "rc",
                   "lb", "cb", "rb"];

var modeFunc = {
    "move": moveObjects,
    "lt": function(obj, dx, dy) { scaleObjects(obj, dx,  0, dy,  0) },
    "ct": function(obj, dx, dy) { scaleObjects(obj,  0,  0, dy,  0) },
    "rt": function(obj, dx, dy) { scaleObjects(obj,  0, dx, dy,  0) },
    "lc": function(obj, dx, dy) { scaleObjects(obj, dx,  0,  0,  0) },
    "rc": function(obj, dx, dy) { scaleObjects(obj,  0, dx,  0,  0) },
    "lb": function(obj, dx, dy) { scaleObjects(obj, dx,  0,  0, dy) },
    "cb": function(obj, dx, dy) { scaleObjects(obj,  0,  0,  0, dy) },
    "rb": function(obj, dx, dy) { scaleObjects(obj,  0, dx,  0, dy) }
};

function begin(mouse) {
    var p = Qt.point(mouse.x, mouse.y);
    if (selectRect) {
        for (var i in bobberModes) {
            var mode = bobberModes[i];
            var bobber = getBobberRect(mode);
            if (Tool.pointInRect(p, bobber)) {
                changeMode = mode;
                break;
            }
        }
        if (!changeMode && Tool.pointInRect(p, selectRect)) {
            changeMode = "move";
        }
        if (changeMode) {
            lastPoint = p;
            return emptyContainer;
        }
        selectRect = null;
    }
    return {
        start: p,
        rect: Qt.rect(mouse.x, mouse.y, 0, 0),
        paint: paint
    }
}

function end(container, mouse) {
    move(container, mouse);
    if (selectRect) {
        changeMode = null;
        lastPoint = null;
        return;
    }
    var obj;
    selectedObjects.length = 0;
    for (var i in objects) {
        obj = objects[i];
        if (Tool.isRectIntersect(container.rect, obj.getRect())) {
            selectedObjects.push(obj);
        }
    }
    if (selectedObjects.length > 0) {
        updateSelectRect();
        canvas.requestPaint();
    }
}

function move(container, mouse) {
    if (selectRect) {
        var dx = mouse.x - lastPoint.x;
        var dy = mouse.y - lastPoint.y;
        var func = modeFunc[changeMode];
        for (var i in selectedObjects) {
            var obj = selectedObjects[i];
            func(obj, dx, dy);
        }
        updateSelectRect();
        lastPoint = Qt.point(mouse.x, mouse.y);
        return;
    }
    var start = container.start;
    var rect = container.rect;
    if (mouse.x < start.x) {
        rect.x = mouse.x;
        rect.width = start.x - mouse.x;
    }
    else {
        rect.x = start.x;
        rect.width = mouse.x - start.x;
    }
    if (mouse.y < start.y) {
        rect.y = mouse.y;
        rect.height = start.y - mouse.y;
    }
    else {
        rect.y = start.y;
        rect.height = mouse.y - start.y;
    }
}

function updateSelectRect() {
    var obj = selectedObjects[0];
    selectRect = obj.getRect();
    var count = selectedObjects.length;
    for (var i = 1; i < count; ++i) {
        obj = selectedObjects[i];
        selectRect = Tool.getBoundRect(selectRect, obj.getRect());
    }
}

function moveObjects(obj, dx, dy) {
    obj.x += dx;
    obj.y += dy;
}

function scaleObjects(obj, dlx, drx, dty, dby) {
    var width = selectRect.width;
    var height = selectRect.height;
    var sx = 1 + (drx - dlx) / width;
    var sy = 1 + (dby - dty) / height;
    var ax = (obj.x - selectRect.x) / width;
    var ay = (obj.y - selectRect.y) / height;
    obj.x += (dlx * (1 - ax) + drx * ax) * sx;
    obj.y += (dty * (1 - ay) + dby * ay) * sy;
    obj.sx *= sx;
    obj.sy *= sy;
}

function paint(ctx) {
    if (selectRect) return;
    ctx.beginPath();
    ctx.lineWidth = 2;
    ctx.strokeStyle = Qt.rgba(0, 0, 0, 0.5);
    ctx.fillStyle = Qt.rgba(1, 1, 0, 0.5);
    ctx.rect(this.rect.x, this.rect.y, this.rect.width, this.rect.height);
    ctx.fill();
    ctx.stroke();
}

function paintSelected(ctx) {
    if (!selectRect) return;
    ctx.beginPath();
    ctx.lineWidth = 2;
    ctx.strokeStyle = Qt.rgba(0, 0, 1, 1);
    ctx.fillStyle = Qt.rgba(0.8, 1, 0, 0.5);
    ctx.rect(selectRect.x, selectRect.y, selectRect.width, selectRect.height);
    ctx.fill();
    ctx.stroke();
    ctx.beginPath();
    ctx.strokeStyle = Qt.rgba(0, 0, 1, 1);
    ctx.fillStyle = Qt.rgba(0, 1, 1, 1);
    for (var i in bobberModes) {
        var mode = bobberModes[i];
        var bobber = getBobberRect(mode);
        ctx.ellipse(bobber.x, bobber.y, bobber.width, bobber.height);
    }
    ctx.fill();
    ctx.stroke();
}

function getBobberRect(mode) {
    var x = selectRect.x;
    var y = selectRect.y;
    var w = selectRect.width;
    var h = selectRect.height;
    switch(mode) {
    case "ct":
        x += w / 2;
        break;
    case "rt":
        x += w;
        break;
    case "lc":
        y += h / 2;
        break;
    case "rc":
        x += w;
        y += h /2;
        break;
    case "lb":
        y += h;
        break;
    case "cb":
        x += w / 2;
        y += h;
        break;
    case "rb":
        x += w;
        y += h;
        break;
    }
    return Qt.rect(x - 6, y - 6, 12, 12);
}

function modeChange() {
    if (selectRect && Paint.mode !== "select") {
        selectedObjects.length = 0;
        selectRect = null;
        canvas.requestPaint();
    }
}

Paint.updateMode.connect(modeChange);
