/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Pen = {
    begin:
    function(start) {
        var element = createSvgElement("path");
        setStyle(element);
        var seg = element.createSVGPathSegMovetoAbs(start.x, start.y);
        element.pathSegList.appendItem(seg);
        return element;
    },

    draw:
    function(element, p) {
        var seg = element.createSVGPathSegLinetoAbs(p.x, p.y);
        element.pathSegList.appendItem(seg);
    }
}
