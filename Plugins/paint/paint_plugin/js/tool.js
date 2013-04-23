/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

function copyObject(src, dst) {
    for (var key in src) {
        dst[key] = src[key];
    }
}

function isRectIntersect(r1, r2) {
    return !(r1.x > r2.x + r2.width || r1.x + r1.width < r2.x || r1.y > r2.y + r2.height || r1.y + r1.height < r2.y);
}

function clonePoint(p) {
    return Qt.point(p.x, p.y);
}

function cloneRect(rect) {
    return Qt.rect(rect.x, rect.y, rect.width, rect.height);
}

function copyRect(src, dst) {
    dst.x = src.x;
    dst.y = src.y;
    dst.width = src.width;
    dst.height = src.height;
}

function getBoundRect(r1, r2) {
    var x1 = Math.min(r1.x, r2.x);
    var x2 = Math.max(r1.x + r1.width, r2.x + r2.width);
    var y1 = Math.min(r1.y, r2.y);
    var y2 = Math.max(r1.y + r1.height, r2.y + r2.height);
    return Qt.rect(x1, y1, x2 - x1, y2 - y1);
}

function pointInRect(p, r) {
    return (p.x >= r.x) && (p.x <= r.x + r.width) && (p.y >= r.y) && (p.y <= r.y + r.height);
}

function dump(obj) {
    for (var i in obj) {
        console.log(i + ": " + obj[i]);
    }
}
