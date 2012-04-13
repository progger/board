/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Select = {
    begin:
    function(canvas, target, start) {
        var select = canvas.select;
        if (select && target) {
            var id = target.getAttribute("id");
            if (id) {
                var mode;
                if (id == "select_bar") {
                    mode = "move";
                }
                else if (id.substr(0, 3) == "sp_") {
                    mode = id.substr(3, 2);
                }
                canvas.select.mode = mode;
                if (mode) return;
            }
        }

        var element = document.getElementById("select_rect");
        element.setAttribute("visibility", "visible");
        var p = createSvgPoint(start.x + 1, start.y + 1);
        Rectangle.draw(element, start, p);
    },

    draw:
    function(canvas, p) {
        var element;
        var i;
        if (canvas.select && canvas.select.mode) {
            var list = canvas.select.list;

            switch (canvas.select.mode) {
                case "move":
                    var selectBox = document.getElementById("select_box");
                    var dx = p.x - canvas.last.x;
                    var dy = p.y - canvas.last.y;
                    for (i = 0; i < list.length; i++) {
                        element = list[i];
                        translate(element, dx, dy);
                    }
                    translate(selectBox, dx, dy);
                    break;
                case "tl":
                    this.drawScale(list, p, -1, -1);
                    break;
                case "tc":
                    this.drawScale(list, p, 0, -1);
                    break;
                case "tr":
                    this.drawScale(list, p, 1, -1);
                    break;
                case "cl":
                    this.drawScale(list, p, -1, 0);
                    break;
                case "cr":
                    this.drawScale(list, p, 1, 0);
                    break;
                case "bl":
                    this.drawScale(list, p, -1, 1);
                    break;
                case "bc":
                    this.drawScale(list, p, 0, 1);
                    break;
                case "br":
                    this.drawScale(list, p, 1, 1);
                    break;
            }
            return;
        }

        element = document.getElementById("select_rect");
        Rectangle.draw(element, canvas.start, p);
    },

    drawScale:
    function(list, p, mx, my) {
        function d(a, b, m) {
            switch (m) {
                case -1:
                    return Math.min(a + b / 2, b - 10);
                case 1:
                    return Math.max(a - b / 2, 10 - b);
                default:
                    return 0;
            }
        }

        var selectBox = document.getElementById("select_box");
        var selectBar = document.getElementById("select_bar");
        var bw = selectBar.width.baseVal.value;
        var bh = selectBar.height.baseVal.value;
        var bm = selectBox.getCTM();
        var dx = d(p.x - bm.e, bw, mx);
        var dy = d(p.y - bm.f, bh, my);
        var sx = 1 + dx / bw * mx;
        var sy = 1 + dy / bh * my;
        for (i = 0; i < list.length; i++) {
            var element = list[i];
            scale(element, sx, sy);
            var em = element.getCTM();
            var edx = (em.e - bm.e) / bw * dx * mx;
            var edy = (em.f - bm.f) / bh * dy * my;
            edx += dx / 2;
            edy += dy / 2;
            translate(element, edx, edy);
        }
        this.placeBox(list);
    },

    end:
    function(canvas) {
        if (canvas.select && canvas.select.mode) {
            canvas.select.mode = undefined;
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
        this.placeBox(list);
        var selectBox = document.getElementById("select_box");
        selectBox.setAttribute("visibility", "visible");
        var group = document.getElementById("select_point_group");
        group.setAttribute("visibility", "visible");

        var canvas = document.getElementById("canvas");
        canvas.select = { list: list };
        board.core.selected = true;
    },

    hide:
    function() {
        var selectBox = document.getElementById("select_box");
        selectBox.setAttribute("visibility", "hidden");
        var group = document.getElementById("select_point_group");
        group.setAttribute("visibility", "hidden");
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

    placeBox:
    function(list) {
        var selectBox = document.getElementById("select_box");
        var selectBar = document.getElementById("select_bar");
        var rect = this.getListRect(list);
        var w = rect.width / 2;
        var h = rect.height / 2;

        selectBar.x.baseVal.value = -w;
        selectBar.y.baseVal.value = -h;
        selectBar.width.baseVal.value = rect.width;
        selectBar.height.baseVal.value = rect.height;

        this.place("sp_tl", -w, -h);
        this.place("sp_tc", 0, -h);
        this.place("sp_tr", w, -h);
        this.place("sp_cl", -w, 0);
        this.place("sp_cr", w, 0);
        this.place("sp_bl", -w, h);
        this.place("sp_bc", 0, h);
        this.place("sp_br", w, h);

        clearTransform(selectBox);
        translate(selectBox, rect.x + w, rect.y + h);
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

    place:
    function(name, x, y) {
        var element = document.getElementById(name);
        element.cx.baseVal.value = x;
        element.cy.baseVal.value = y;
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
