/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

.import "../tool.js" as Tool
.import "pen.js" as Pen

function begin(mouse) {
    return Pen.begin(mouse);
}

function end(container, mouse) {
    Pen.end(container, mouse);
    var obj = container.obj;
    var arx = [];
    var ary = [];
    var count = obj.points.length;
    for (var i = 0; i < count; ++i) {
        var p = obj.points[i];
        arx.push(p.x);
        ary.push(p.y);
    }
    if (PathProcessor.process(arx, ary)) {
        obj.points.length = 0;
        arx = PathProcessor.arx;
        ary = PathProcessor.ary;
        count = Math.min(arx.length, ary.length);
        for (i = 0; i < count; ++i) {
            p = Qt.point(arx[i], ary[i]);
            obj.points.push(p);
        }
        Pen.updateRect(obj);
    }
}

function move(container, mouse) {
    Pen.move(container, mouse);
}
