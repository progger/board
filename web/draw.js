/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */
var svgns = "http://www.w3.org/2000/svg";
var xmlns = "http://www.w3.org/XML/1998/namespace"

function canvas_onMouseDown(e) {
    if (e.which !== 1) return;
    stopText(this);
    this.state = true;
    this.start = [e.pageX, e.pageY];
    this.last = this.start;
    var element;
    switch (board.core.mode) {
        case "pen":
            element = beginPen(this);
            break;
        case "rectangle":
            element = beginRectangle(this);
            break;
        case "circle":
            element = beginCircle(this);
            break;
        case "ellipse":
            element = beginEllipse(this);
            break;
    }
    if (element) {
        var content = document.getElementById("content");
        content.appendChild(element);
    }
    this.element = element;
}

function canvas_onMouseUp(e) {
    if (e.which !== 1) return;
    this.state = false;
    this.last = [e.pageX, e.pageY];
    switch (board.core.mode) {
        case "text":
            startText(this);
            board.core.mode = "select";
            break;
    }
}

function canvas_onMouseMove(e) {
    if (!this.state) return;
    var element = this.element;
    var p = [e.pageX, e.pageY];
    switch (board.core.mode)
    {
    case "pen":
        drawPen(element, p);
        break;
    case "rectangle":
        drawRectangle(element, this.start, p);
        break;
    case "circle":
        drawCircle(element, this.start, p);
        break;
    case "ellipse":
        drawEllipse(element, this.start, p);
        break;
    }
    this.last = p;
}

function canvas_onMouseOut(e) {
      this.state = this.state && !isOutside(e, this);
}

function canvas_onKeyDown(e) {
    var element = this.textElement;
    if (!element) return;
    var text = element.textContent;
    var cursor = this.textCursor;
    switch(e.keyCode) {
        case 8:
            if (cursor == 0) return;
            element.textContent = text.substr(0, text.length - 1);
            this.textCursor = cursor - 1;
            break;
        case 13:
            stopText(this);
            return;
        case 37:
            if (cursor == 0) return;
            this.textCursor = cursor - 1;
            break;
        case 39:
            if (cursor >= text.length) return;
            this.textCursor = cursor + 1;
            break;
    }
    updateText(this);
}

function canvas_onKeyPress(e) {
    if (e.charCode < 32) return;
    var element = this.textElement;
    if (!element) return;
    var key = String.fromCharCode(e.charCode);
    var cursor = this.textCursor;
    var text = element.textContent;
    text = text.substr(0, cursor) + key + text.substr(cursor);
    element.textContent = text;
    this.textCursor += 1;
    updateText(this);
}

function beginPen(canvas) {
    var element = createSvgElement("path");
    setStyleAttr(element);
    element.setAttribute("d", "M " + canvas.start[0] + "," + canvas.start[1]);
    return element;
}

function drawPen(element, p) {
    var d = element.getAttribute("d");
    d += "L" + p[0] + "," + p[1];
    element.setAttribute("d", d);
}

function beginRectangle(canvas) {
    var element = createSvgElement("rect");
    setStyleAttr(element);
    element.setAttribute("x", canvas.start[0]);
    element.setAttribute("y", canvas.start[1]);
    return element;
}

function drawRectangle(element, start, p) {
    var tmp;
    var sx = start[0];
    var sy = start[1];
    var x = p[0];
    var y = p[1];
    if (x < sx) {
        tmp = sx;
        sx = x;
        x = tmp;
    }
    if (y < sy) {
        tmp = sy;
        sy = y;
        y = tmp;
    }
    var width = x - sx;
    var height = y - sy;
    element.setAttribute("x", sx);
    element.setAttribute("y", sy);
    element.setAttribute("width", width);
    element.setAttribute("height", height);
}

function beginCircle(canvas) {
    var element = createSvgElement("circle");
    setStyleAttr(element);
    element.setAttribute("cx", canvas.start[0]);
    element.setAttribute("cy", canvas.start[1]);
    return element;
}

function drawCircle(element, start, p) {
    var dx = p[0] - start[0];
    var dy = p[1] - start[1];
    var r = Math.sqrt(dx * dx + dy * dy);
    element.setAttribute("r", r);
}

function beginEllipse(canvas) {
    var element = createSvgElement("ellipse");
    setStyleAttr(element);
    element.setAttribute("cx", canvas.start[0]);
    element.setAttribute("cy", canvas.start[1]);
    return element;
}

function drawEllipse(element, start, p) {
    var tmp;
    var sx = start[0];
    var sy = start[1];
    var x = p[0];
    var y = p[1];
    if (x < sx) {
        tmp = sx;
        sx = x;
        x = tmp;
    }
    if (y < sy) {
        tmp = sy;
        sy = y;
        y = tmp;
    }
    var rx = (x - sx) / 2;
    var ry = (y - sy) / 2;
    var cx = sx + rx;
    var cy = sy + ry;
    element.setAttribute("cx", cx);
    element.setAttribute("cy", cy);
    element.setAttribute("rx", rx);
    element.setAttribute("ry", ry);
}

function startText(canvas) {
    var element = createSvgElement("text");
    element.setAttribute("fill", board.core.color);
    element.setAttribute("font-size", board.core.fontSize);
    element.setAttribute("font-family", "sans");
    element.setAttribute("x", canvas.last[0]);
    element.setAttribute("y", canvas.last[1]);
    element.setAttributeNS(xmlns, "space", "preserve");

    var content = document.getElementById("content");
    content.appendChild(element);
    canvas.textElement = element;
    canvas.textCursor = 0;
    updateText(canvas);
    board.core.keyboard = true;
}

function stopText(canvas) {
    if (!canvas.textElement) return;
    canvas.textElement = null;
    canvas.textCursor = null;
    var textBar = document.getElementById("text_bar");
    textBar.setAttribute("visibility", "hidden");
    var textCursor = document.getElementById("text_cursor");
    textCursor.setAttribute("visibility", "hidden");
    board.core.keyboard = false;
}

function updateText(canvas) {
    var element = canvas.textElement;
    var p = [+element.getAttribute("x") - 4, +element.getAttribute("y") + 4];
    var width = element.getComputedTextLength() + 8;
    var height = board.core.fontSize;

    var textBar = document.getElementById("text_bar");
    textBar.setAttribute("x", p[0]);
    textBar.setAttribute("y", p[1] - height);
    textBar.setAttribute("width", width);
    textBar.setAttribute("height", height);
    textBar.setAttribute("visibility", "visible");

    var cur;
    if (canvas.textCursor == 0) {
        cur = p[0] + 4;
    }
    else {
        var pnt = element.getEndPositionOfChar(canvas.textCursor - 1);
        cur = pnt.x;
    }
    var textCursor = document.getElementById("text_cursor");
    textCursor.setAttribute("x1", cur);
    textCursor.setAttribute("y1", p[1] - 2);
    textCursor.setAttribute("x2", cur);
    textCursor.setAttribute("y2", p[1] - height + 2);
    textCursor.setAttribute("visibility", "visible");
}

function createSvgElement(name) {
    return document.createElementNS(svgns, name);
}

function isOutside(e, parent) {
  var relatedTarget = e.relatedTarget;
  while (relatedTarget && relatedTarget !== parent)
    relatedTarget = relatedTarget.parentNode;
  return !relatedTarget;
}

function setStyleAttr(element) {
    var fill = "fill:none;";
    var stroke = "stroke:" + board.core.color + ";";
    var strokeWidth = "stroke-width:3;";
    element.setAttribute("style", fill + stroke + strokeWidth);
}
