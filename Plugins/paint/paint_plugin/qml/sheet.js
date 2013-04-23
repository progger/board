/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

.import "../js/tool.js" as Tool
.import "../js/shapes/select.js" as Select
.import "../js/shapes/pen.js" as Pen
.import "../js/shapes/rectangle.js" as Rectangle
.import "../js/shapes/circle.js" as Circle
.import "../js/shapes/ellipse.js" as Ellipse

var shapes = {
    "select": Select,
    "pen": Pen,
    "rectangle": Rectangle,
    "circle": Circle,
    "ellipse": Ellipse
};
var objects = [];
var shape = null;
var container = null;
var state = 0;

function paint(rect) {
    var ctx = canvas.context;
    ctx.reset();
    for (var i in objects) {
        var obj = objects[i];
        ctx.save();
        ctx.translate(obj.x, obj.y);
        ctx.scale(obj.sx, obj.sy);
        obj.paint(ctx);
        ctx.restore();
    }
    if (container) {
        ctx.save();
        container.paint(ctx);
        ctx.restore();
    }
    ctx.save();
    Select.paintSelected(ctx);
    ctx.restore();
}

function mouseDown(mouse) {
    if (mouse.button !== Qt.LeftButton) return;
    shape = shapes[Paint.mode];
    if (!shape) return;
    container = shape.begin(mouse);
    var obj = container.obj;
    if (obj) {
        objects.push(obj);
    }
    canvas.requestPaint();
    state = 1;
}

function mouseUp(mouse) {
    if (mouse.button !== Qt.LeftButton || !shape) return;
    shape.end(container, mouse);
    canvas.requestPaint();
    shape = null;
    container = null;
    state = 0;
}

function mouseMove(mouse) {
    if (!state) return;
    shape.move(container, mouse);
    canvas.requestPaint();
}

function init() {
    Select.canvas = canvas;
    Select.objects = objects;
}
