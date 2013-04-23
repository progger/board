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
    obj.paint = paint;
    return container;
}

function end(container, mouse) {
    move(container, mouse);
}

function move(container, mouse) {
    var start = container.start;
    var obj = container.obj;
    if (mouse.x < start.x) {
        obj.x = mouse.x;
        obj.width = start.x - mouse.x;
        obj.dx = -obj.width;
    }
    else {
        obj.x = start.x;
        obj.width = mouse.x - start.x;
        obj.dx = 0;
    }
    if (mouse.y < start.y) {
        obj.y = mouse.y;
        obj.height = start.y - mouse.y;
        obj.dy = -obj.y;
    }
    else {
        obj.y = start.y;
        obj.height = mouse.y - start.y;
        obj.dy = 0;
    }
}

function paint(ctx) {
    ctx.beginPath();
    ctx.lineWidth = this.thickness;
    ctx.strokeStyle = this.color;
    ctx.rect(0, 0, this.width, this.height);
    ctx.stroke();
}
