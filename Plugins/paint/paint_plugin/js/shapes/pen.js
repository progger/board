/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

.import "../tool.js" as Tool
.import "../shape.js" as Shape

function begin(mouse) {
    var container = Shape.createContainer(mouse.x, mouse.y);
    var obj = container.obj;
    obj.thickness = Paint.thickness;
    obj.color = Paint.getColor();
    obj.points = [Qt.point(0, 0)];
    obj.paint = paint;
    return container;
}

function end(container, mouse) {
    var start = container.start;
    var obj = container.obj;
    var p = Qt.point(mouse.x - start.x, mouse.y - start.y);
    var last = obj.points[obj.points.length - 1];
    if (p.x !== last.x || p.y !== last.y) {
        obj.points.push(p);
    }
    if (obj.points.length > 1) {
        obj.points.shift();
    }
    updateRect(obj);
}

function move(container, mouse) {
    var start = container.start;
    var obj = container.obj;
    var p = Qt.point(mouse.x - start.x, mouse.y - start.y);
    var last = obj.points[obj.points.length - 1];
    var d = Math.abs(p.x - last.x) + Math.abs(p.y - last.y);
    if (d > obj.thickness) {
        obj.points.push(p);
    }
    updateRect(obj);
}

function updateRect(obj) {
    var x1 = 0;
    var y1 = 0;
    var x2 = 0;
    var y2 = 0;
    for (var i in obj.points) {
        var p = obj.points[i];
        if (p.x < x1) x1 = p.x;
        if (p.y < y1) y1 = p.y;
        if (p.x > x2) x2 = p.x;
        if (p.y > y2) y2 = p.y;
    }
    obj.dx = x1;
    obj.dy = y1;
    obj.width = x2 - x1;
    obj.height = y2 - y1;
}

function paint(ctx) {
    ctx.beginPath();
    ctx.lineWidth = this.thickness;
    ctx.strokeStyle = this.color;
    ctx.lineCap = "round";
    ctx.lineJoin = "round";
    ctx.moveTo(0, 0)
    for (var i in this.points) {
        var p = this.points[i];
        ctx.lineTo(p.x, p.y);
    }
    ctx.stroke();
}
