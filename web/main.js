function draw_onMouseDown(e)
{
    if (e.which !== 1) return;
    drawObject.state = true;
    this.lastX = e.pageX;
    this.lastY = e.pageY;
    switch (drawObject.mode)
    {
    case "pen":
        var ns = this.getAttribute("xmlns");
        var path = document.createElementNS(ns, "path");
        var x = e.pageX - this.translateX;
        var y = e.pageY - this.translateY;
        path.setAttribute("d", "M" + x + "," + y);
        path.setAttribute("stroke-width", "3");
        path.setAttribute("stroke", drawObject.color);
        path.setAttribute("fill", "none");
        this.path = path;
        this.mainGroup.appendChild(path);
        break;
    case "move":
        break;
    }
};

function draw_onMouseUp(e)
{
    if (e.which !== 1) return;
    drawObject.state = false;
};

function draw_onMouseMove(e)
{
    if (!drawObject.state) return;
    switch (drawObject.mode)
    {
    case "pen":
        var path = this.path;
        var d = path.getAttribute("d");
        var x = e.pageX - this.translateX;
        var y = e.pageY - this.translateY;
        d += "L" + x + "," + y;
        path.setAttribute("d", d);
        break;
    case "move":
        this.translateX += e.pageX - this.lastX;
        this.translateY += e.pageY - this.lastY;
        this.mainGroup.setAttribute("transform",
            getTranslateAttr(this.translateX, this.translateY));
        break;
    }
    this.lastX = e.pageX;
    this.lastY = e.pageY;
};

function draw_onMouseOut(e)
{
      drawObject.state = drawObject.state && !isOutside(e, this);
};

function main()
{
    var draw = document.getElementById("draw");
    var mainGroup = document.getElementById("mainGroup");
    draw.mainGroup = mainGroup;
    draw.translateX = 0;
    draw.translateY = 0;
    draw.onmousedown = draw_onMouseDown;
    draw.onmouseup = draw_onMouseUp;
    draw.onmousemove = draw_onMouseMove;
    draw.onmouseout = draw_onMouseOut;
    coreObject.readyToWork();
};

function globalError(message)
{
    alert(message);
};

window.onload = main;
window.onerror = globalError;
