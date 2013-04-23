/*
 * Copyright (C) 2013 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

.import "ellipse.js" as Ellipse

function begin(mouse) {
    var container = Ellipse.begin(mouse);
    return container;
}

function end(container, mouse) {
    move(container, mouse);
}

function move(container, mouse) {
    var start = container.start;
    var obj = container.obj;
    var dx = mouse.x - start.x;
    var dy = mouse.y - start.y;
    var r = Math.sqrt(dx * dx + dy * dy);
    obj.x = start.x - r;
    obj.y = start.y - r;
    obj.width = r * 2;
    obj.height = r * 2;
}
