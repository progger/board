/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

function canvas_onMouseDown(e) {
    if (e.which !== 1) return;
    Text.end(this);
    this.state = true;
    var start = createSvgPoint(e.pageX, e.pageY);
    this.start = start;
    this.last = start;
    var element;
    switch (paint.mode) {
        case "select":
            Select.begin(this, e.target, start);
            break;
        case "pen":
            element = Pen.begin(start);
            break;
        case "magic_pen":
            element = MagicPen.begin(start);
            break;
        case "rectangle":
            element = Rectangle.begin(start);
            break;
        case "circle":
            element = Circle.begin(start);
            break;
        case "ellipse":
            element = Ellipse.begin(start);
            break;
        case "image":
            element = Image.begin(start);
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
    var element = this.element;
    switch (paint.mode) {
        case "select":
            Select.end(this);
            break;
        case "pen":
            Pen.end(element);
            break;
        case "magic_pen":
            MagicPen.end(element);
            break;
        case "rectangle":
            Rectangle.end(element);
            break;
        case "ellipse":
            Ellipse.end(element);
            break;
        case "text":
            Text.begin(this);
            paint.mode = "select";
            break;
        case "image":
            paint.mode = "select";
            break;
        default:
            break;
    }
    Diff.checkpoint();
}

function canvas_onMouseMove(e) {
    if (!this.state) return;
    var p = createSvgPoint(e.pageX, e.pageY);
    var element = this.element;
    switch (paint.mode) {
        case "select":
            Select.draw(this, p);
            break;
        case "pen":
            Pen.draw(element, this.last, p);
            break;
        case "magic_pen":
            MagicPen.draw(element, this.last, p);
            break;
        case "rectangle":
            Rectangle.draw(element, this.start, p);
            break;
        case "circle":
            Circle.draw(element, this.start, p);
            break;
        case "ellipse":
            Ellipse.draw(element, this.start, p);
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
            Text.end(this);
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
    Text.draw(this);
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
    Text.draw(this);
}

