function beginPen(draw)
{
    var element = createSvgElement("path");
    setDrawStyleAttr(element);
    element.setAttribute("d", "M" + draw.startX + "," + draw.startY);
    return element;
}

function drawPen(element, x, y)
{
    var d = element.getAttribute("d");
    d += "L" + x + "," + y;
    element.setAttribute("d", d);
}

function beginRectangle(draw)
{
    var element = createSvgElement("rect");
    setDrawStyleAttr(element);
    element.setAttribute("x", draw.startX);
    element.setAttribute("y", draw.startY);
    return element;
}

function drawRectangle(element, startX, startY, x, y)
{
    var tmp;
    if (x < startX)
    {
        tmp = startX;
        startX = x;
        x = tmp;
    }
    if (y < startY)
    {
        tmp = startY;
        startY = y;
        y = tmp;
    }
    var width = x - startX;
    var height = y - startY;
    element.setAttribute("x", startX);
    element.setAttribute("y", startY);
    element.setAttribute("width", width);
    element.setAttribute("height", height);
}

function beginCircle(draw)
{
    var element = createSvgElement("circle");
    setDrawStyleAttr(element);
    element.setAttribute("cx", draw.startX);
    element.setAttribute("cy", draw.startY);
    return element;
}

function drawCircle(element, startX, startY, x, y)
{
    var dx = x - startX;
    var dy = y - startY;
    var r = Math.sqrt(dx * dx + dy * dy);
    element.setAttribute("r", r);
}

function beginEllipse(draw)
{
    var element = createSvgElement("ellipse");
    setDrawStyleAttr(element);
    element.setAttribute("cx", draw.startX);
    element.setAttribute("cy", draw.startY);
    return element;
}

function drawEllipse(element, startX, startY, x, y)
{
    var tmp;
    if (x < startX)
    {
        tmp = startX;
        startX = x;
        x = tmp;
    }
    if (y < startY)
    {
        tmp = startY;
        startY = y;
        y = tmp;
    }
    var rx = (x - startX) / 2;
    var ry = (y - startY) / 2;
    var cx = startX + rx;
    var cy = startY + ry;
    element.setAttribute("cx", cx);
    element.setAttribute("cy", cy);
    element.setAttribute("rx", rx);
    element.setAttribute("ry", ry);
}

function draw_onMouseDown(e)
{
    if (e.which !== 1) return;
    drawObject.state = true;
    this.lastX = e.pageX;
    this.lastY = e.pageY;
    this.startX = e.pageX - this.translateX;
    this.startY = e.pageY - this.translateY;
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
        var drawGroup = getDrawGroup(this);
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
    var element = this.element;
    var x = e.pageX - this.translateX;
    var y = e.pageY - this.translateY;
    switch (drawObject.mode)
    {
    case "pen":
        drawPen(element, x, y);
        break;
    case "rectangle":
        drawRectangle(element, this.startX, this.startY, x, y);
        break;
    case "circle":
        drawCircle(element, this.startX, this.startY, x, y);
        break;
    case "ellipse":
        drawEllipse(element, this.startX, this.startY, x, y);
        break;
    case "move":
        this.translateX += e.pageX - this.lastX;
        this.translateY += e.pageY - this.lastY;
        var translate = getTranslateAttr(this.translateX, this.translateY);
        var drawGroup = getDrawGroup(this);
        drawGroup.setAttribute("transform", translate);
        break;
    }
    this.lastX = e.pageX;
    this.lastY = e.pageY;
}

function draw_onMouseOut(e)
{
      drawObject.state = drawObject.state && !isOutside(e, this);
}
