/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Rectangle = {
    begin:
    function(start) {
        var element = createSvgElement("rect");
        setStyle(element);
        this.draw(element, start, start);
        return element;
    },

    draw:
    function(element, start, p) {
        element.x.baseVal.value = Math.min(start.x, p.x);
        element.y.baseVal.value = Math.min(start.y, p.y);
        element.width.baseVal.value = Math.abs(start.x - p.x);
        element.height.baseVal.value = Math.abs(start.y - p.y);
    },

    end:
    function(element) {
        var w = element.width.baseVal.value;
        var h = element.height.baseVal.value;
        var x = element.x.baseVal.value + w / 2;
        var y = element.y.baseVal.value + h / 2;
        translate(element, x, y);
        element.x.baseVal.value = - w / 2;
        element.y.baseVal.value = - h / 2;
    }
}
