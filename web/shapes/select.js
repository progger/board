/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Select = {
    begin:
    function(canvas, start) {
        var select = canvas.select;
        if (select && pointInRect(start, select.rect)) {
            canvas.select.move = 1;
            return;
        }

        var element = document.getElementById("select_rect");
        element.setAttribute("visibility", "visible");
        var p = createSvgPoint(start.x + 1, start.y + 1);
        Rectangle.draw(element, start, p);
    },

    draw:
    function(canvas, p) {
        var element;
        if (canvas.select && canvas.select.move) {
            var list = canvas.select.list;
            var dx = p.x - canvas.last.x;
            var dy = p.y - canvas.last.y;
            for (var i = 0; i < list.length; i++) {
                element = list[i];
                translate(element, dx, dy);
            }
            var selectBar = document.getElementById("select_bar");
            selectBar.x.baseVal.value += dx;
            selectBar.y.baseVal.value += dy;
            var rect = canvas.select.rect;
            rect.x += dx;
            rect.y += dy;
            return;
        }

        element = document.getElementById("select_rect");
        Rectangle.draw(element, canvas.start, p);
    },

    end:
    function(canvas) {
        if (canvas.select && canvas.select.move) {
            canvas.select.move = 0;
            return;
        }

        var element = document.getElementById("select_rect");
        var content = document.getElementById("content");
        var rect = element.getBBox();
        //var list = content.getIntersectionList(rect);
        var list = this.getIntersectionList(rect);
        element.setAttribute("visibility", "hidden");
        if (list.length == 0) {
            this.hide();
            return;
        }
        this.show(list);
    },

    show:
    function(list) {
        var selectBox = document.getElementById("select_box");
        var selectBar = document.getElementById("select_bar");
        var rect = this.getListRect(list);
        selectBar.x.baseVal.value = rect.x;
        selectBar.y.baseVal.value = rect.y;
        selectBar.width.baseVal.value = rect.width;
        selectBar.height.baseVal.value = rect.height;
        selectBox.setAttribute("visibility", "visible");

        canvas.select = {
            list: list,
            rect: rect
        }
        board.core.selected = true;
    },

    hide:
    function() {
        var selectBox = document.getElementById("select_box");
        selectBox.setAttribute("visibility", "hidden");
        var canvas = document.getElementById("canvas");
        canvas.select = undefined;
        board.core.selected = false;
    },

    del:
    function() {
        var canvas = document.getElementById("canvas");
        var content = document.getElementById("content");
        var list = canvas.select.list;
        for (var i = 0; i < list.length; i++) {
            var element = list[i];
            content.removeChild(element);
        }
        this.hide();
        Diff.checkpoint();
    },

    duplicate:
    function() {
        var canvas = document.getElementById("canvas");
        var content = document.getElementById("content");
        var list = canvas.select.list;
        var newList = new Array();
        for (var i = 0; i < list.length; i++) {
            var element = list[i];
            element = element.cloneNode(true);
            translate(element, 20, 20);
            content.appendChild(element);
            newList.push(element);
        }
        this.show(newList);
        Diff.checkpoint();
    },

    getListRect:
    function(list) {
        var element = list[0];
        var rect = element.getBBox();
        var m = element.getCTM();
        var a = createSvgPoint(rect.x, rect.y);
        var b = createSvgPoint(rect.x + rect.width, rect.y + rect.height);
        a = a.matrixTransform(m);
        b = b.matrixTransform(m);
        for (i = 1; i < list.length; i++) {
            element = list[i];
            rect = element.getBBox();
            m = element.getCTM();
            var c = createSvgPoint(rect.x, rect.y);
            var d = createSvgPoint(rect.x + rect.width, rect.y + rect.height);
            c = c.matrixTransform(m);
            d = d.matrixTransform(m);
            if (c.x < a.x) {
                a.x = c.x;
            }
            if (c.y < a.y) {
                a.y = c.y;
            }
            if (d.x > b.x) {
                b.x = d.x;
            }
            if (d.y > b.y) {
                b.y = d.y;
            }
        }
        return createSvgRect(a.x, a.y, b.x - a.x, b.y - a.y);
    },

    getIntersectionList:
    function(rect) {
        var list = new Array();
        var content = document.getElementById("content");
        var element = content.firstChild;
        while (element) {
            var box = element.getBBox();
            var m = element.getCTM();
            var a1 = createSvgPoint(box.x, box.y);
            var a2 = createSvgPoint(box.x + box.width, box.y + box.height);
            a1 = a1.matrixTransform(m);
            a2 = a2.matrixTransform(m);
            var b1 = createSvgPoint(rect.x, rect.y);
            var b2 = createSvgPoint(rect.x + rect.width, rect.y + rect.height);
            var b = a1.x > b2.x || b1.x > a2.x || a1.y > b2.y || b1.y > a2.y;
            if (!b) {
                list.push(element);
            }
            element = element.nextSibling;
        }
        return list;
    }
}

function del() {
    Select.del();
}

function duplicate() {
    Select.duplicate();
}
