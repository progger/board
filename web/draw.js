function beginPen(draw)
{
    var element = createDrawElement(draw, "path");
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
    var element = createDrawElement(draw, "rect");
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
    width = x - startX;
    height = y - startY;
    element.setAttribute("x", startX);
    element.setAttribute("y", startY);
    element.setAttribute("width", width);
    element.setAttribute("height", height);
}

function beginCircle(draw)
{
    var element = createDrawElement(draw, "circle");
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
    case "move":
        break;
    }
    if (element)
    {
        this.mainGroup.appendChild(element);
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
    case "move":
        this.translateX += e.pageX - this.lastX;
        this.translateY += e.pageY - this.lastY;
        var translate = getTranslateAttr(this.translateX, this.translateY);
        this.mainGroup.setAttribute("transform", translate);
        break;
    }
    this.lastX = e.pageX;
    this.lastY = e.pageY;
}

function draw_onMouseOut(e)
{
      drawObject.state = drawObject.state && !isOutside(e, this);
}
