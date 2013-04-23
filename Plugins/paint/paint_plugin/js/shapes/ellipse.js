/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

.import "rectangle.js" as Rectangle

function begin(mouse) {
    var container = Rectangle.begin(mouse);
    container.obj.paint = paint;
    return container;
}

function end(container, mouse) {
    move(container, mouse);
}

function move(container, mouse) {
    Rectangle.move(container, mouse);
}

function paint(ctx) {
    ctx.beginPath();
    ctx.lineWidth = this.thickness;
    ctx.strokeStyle = this.color;
    ctx.ellipse(0, 0, this.width, this.height);
    ctx.stroke();
}
