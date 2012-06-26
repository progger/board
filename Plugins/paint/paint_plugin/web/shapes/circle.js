/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Circle = {
    begin:
    function(start) {
        var element = createSvgElement("circle");
        setStyle(element);
        translate(element, start.x, start.y);
        return element;
    },

    draw:
    function(element, start, p) {
        var dx = p.x - start.x;
        var dy = p.y - start.y;
        var r = Math.sqrt(dx * dx + dy * dy);
        element.r.baseVal.value = r;
    }
}
