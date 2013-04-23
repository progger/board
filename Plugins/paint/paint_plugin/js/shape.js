/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

function empty() {}

function createObject(x, y) {
    return {
        x: x,
        y: y,
        dx: 0,
        dy: 0,
        width: 0,
        height: 0,
        sx: 1,
        sy: 1,
        paint: empty,
        getRect: getRect
    }
}

function createContainer(x, y) {
    var obj = createObject(x, y);
    return {
        start: Qt.point(x, y),
        obj: obj,
        paint: empty
    }
}

function getRect() {
    return Qt.rect(this.x + this.dx * this.sx, this.y + this.dy * this.sy,
                   this.width * this.sx, this.height * this.sy);
}
