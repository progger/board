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
    function(element, last, p) {
        var seg = element.createSVGPathSegLinetoAbs(p.x, p.y);
        element.pathSegList.appendItem(seg);
    },

    end:
    function(element) {
        var rect = element.getBBox();
        var x = rect.x + rect.width / 2;
        var y = rect.y + rect.height / 2;
        var list = element.pathSegList;
        var count = list.numberOfItems;
        for (var i = 0; i < count; i++) {
            var seg = list.getItem(i);
            seg.x = seg.x - x;
            seg.y = seg.y - y;
        }
        translate(element, x, y);
    }
}
