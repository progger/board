/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Ellipse = {
    begin:
    function(start) {
        var element = createSvgElement("ellipse");
        setStyle(element);
        this.draw(element, start, start);
        return element;
    },

    draw:
    function(element, start, p) {
        element.cx.baseVal.value = (start.x + p.x) / 2;
        element.cy.baseVal.value = (start.y + p.y) / 2;
        element.rx.baseVal.value = Math.abs(start.x - p.x) / 2;
        element.ry.baseVal.value = Math.abs(start.y - p.y) / 2;
    },

    end:
    function(element) {
        var x = element.cx.baseVal.value;
        var y = element.cy.baseVal.value;
        translate(element, x, y);
        element.cx.baseVal.value = 0;
        element.cy.baseVal.value = 0;
    }
}
