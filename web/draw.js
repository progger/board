function beginPen(draw)
{
    var element = createSvgElement("path");
    setDrawStyleAttr(element);
    element.setAttribute("d", "M" + draw.start[0] + "," + draw.start[1]);
    return element;
}

function drawPen(element, p)
{
    var d = element.getAttribute("d");
    d += "L" + p[0] + "," + p[1];
    element.setAttribute("d", d);
}

function beginRectangle(draw)
{
    var element = createSvgElement("rect");
    setDrawStyleAttr(element);
    element.setAttribute("x", draw.start[0]);
    element.setAttribute("y", draw.start[1]);
    return element;
}

function drawRectangle(element, start, p)
{
    var tmp;
    var sx = start[0];
    var sy = start[1];
    var x = p[0];
    var y = p[1];
    if (x < sx)
    {
        tmp = sx;
        sx = x;
        x = tmp;
    }
    if (y < sy)
    {
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

function beginCircle(draw)
{
    var element = createSvgElement("circle");
    setDrawStyleAttr(element);
    element.setAttribute("cx", draw.start[0]);
    element.setAttribute("cy", draw.start[1]);
    return element;
}

function drawCircle(element, start, p)
{
    var dx = p[0] - start[0];
    var dy = p[1] - start[1];
    var r = Math.sqrt(dx * dx + dy * dy);
    element.setAttribute("r", r);
}

function beginEllipse(draw)
{
    var element = createSvgElement("ellipse");
    setDrawStyleAttr(element);
    element.setAttribute("cx", draw.start[0]);
    element.setAttribute("cy", draw.start[1]);
    return element;
}

function drawEllipse(element, start, p)
{
    var tmp;
    var sx = start[0];
    var sy = start[1];
    var x = p[0];
    var y = p[1];
    if (x < sx)
    {
        tmp = sx;
        sx = x;
        x = tmp;
    }
    if (y < sy)
    {
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

function draw_onMouseDown(e)
{
    if (e.which !== 1) return;
    drawObject.state = true;
    var drawGroup = getDrawGroup(this);
    var m = getMatrix(drawGroup);
    this.start = getPos(m, e);
    this.last = this.start;
    var element;
    switch (drawObject.mode)
    {
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
    case "move":
        break;
    }
    if (element)
    {
        drawGroup.appendChild(element);
    }
    this.element = element;
}

function draw_onMouseUp(e)
{
    if (e.which !== 1) return;
    drawObject.state = false;
}

function draw_onMouseMove(e)
{
    if (!drawObject.state) return;
    var drawGroup = getDrawGroup(this);
    var element = this.element;
    var m = getMatrix(drawGroup);
    var p = getPos(m, e);

    switch (drawObject.mode)
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
    case "move":
        var t = $T.translate(p[0] - this.last[0], p[1] - this.last[1]);
        m = $T.mult(t, m);
        p = getPos(m, e);
        setMatrix(drawGroup, m);
        break;
    }
    this.last = p;
}

function draw_onMouseOut(e)
{
      drawObject.state = drawObject.state && !isOutside(e, this);
}
