/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var MagicPen = {
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
        this.prepare(element);
        var list = element.pathSegList;
        var count = list.numberOfItems;
        var arx = new Array(count);
        var ary = new Array(count);
        var i;
        var seg;
        for (i = 0; i < count; i++) {
            seg = list.getItem(i);
            arx[i] = seg.x;
            ary[i] = seg.y;
        }
        if (path_prc.process(arx, ary)) {
            arx = path_prc.arx;
            ary = path_prc.ary;
            count = Math.min(arx.length, ary.length);
            seg = list.getItem(0);
            seg.x = arx[0];
            seg.y = ary[0];
            list.initialize(seg);
            for (i = 1; i < count; i++) {
                seg = element.createSVGPathSegLinetoAbs(arx[i], ary[i]);
                element.pathSegList.appendItem(seg);
            }
            this.prepare(element);
        }
        path_prc.clear();
    },

    prepare:
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
