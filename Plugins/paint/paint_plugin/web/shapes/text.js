/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Text = {
    begin:
    function(canvas) {
        var element = createSvgElement("text");
        element.style.setProperty("fill", paint.color);
        element.style.setProperty("font-size", paint.fontSize);
        element.style.setProperty("font-family", "sans");
        element.x.baseVal.initialize(createSvgLength(canvas.last.x));
        element.y.baseVal.initialize(createSvgLength(canvas.last.y));
        element.setAttributeNS(xmlns, "space", "preserve");

        var content = document.getElementById("content");
        content.appendChild(element);
        canvas.textElement = element;
        canvas.textCursor = 0;
        this.draw(canvas);
        core.keyboard = true;
    },

    draw:
    function(canvas) {
        var element = canvas.textElement;
        var p = createSvgPoint(element.x.baseVal.getItem(0).value - 4,
                               element.y.baseVal.getItem(0).value + 6);
        var w = element.getComputedTextLength() + 8;
        var h = paint.fontSize + 6;

        var textBar = document.getElementById("text_bar");
        textBar.x.baseVal.value = p.x;
        textBar.y.baseVal.value = p.y - h;
        textBar.width.baseVal.value = w;
        textBar.height.baseVal.value = h;
        textBar.setAttribute("visibility", "visible");

        var cur;
        if (canvas.textCursor == 0) {
            cur = p.x + 4;
        }
        else {
            var pnt = element.getEndPositionOfChar(canvas.textCursor - 1);
            cur = pnt.x;
        }
        var textCursor = document.getElementById("text_cursor");
        textCursor.x1.baseVal.value = cur;
        textCursor.y1.baseVal.value = p.y - 2;
        textCursor.x2.baseVal.value = cur;
        textCursor.y2.baseVal.value = p.y - h + 2;
        textCursor.setAttribute("visibility", "visible");
    },

    end:
    function(canvas) {
        if (!canvas.textElement) return;
        canvas.textElement = null;
        canvas.textCursor = null;
        var textBar = document.getElementById("text_bar");
        textBar.setAttribute("visibility", "hidden");
        var textCursor = document.getElementById("text_cursor");
        textCursor.setAttribute("visibility", "hidden");
        core.keyboard = false;
        Diff.checkpoint();
    }
}
