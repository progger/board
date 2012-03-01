function isOutside(e, parent)
{
  var relatedTarget = e.relatedTarget;
  while (relatedTarget && relatedTarget !== parent)
    relatedTarget = relatedTarget.parentNode;
  return !relatedTarget;
};

function getTranslateAttr(x, y)
{
    return "translate(" + x + " " + y + ")";
}

function draw_onMouseDown(e)
{
    if (e.which !== 1) return;
    core.state = true;
    this.lastX = e.pageX;
    this.lastY = e.pageY;
    switch (core.mode)
    {
    case "pen":
        var ns = this.getAttribute("xmlns");
        var path = document.createElementNS(ns, "path");
        var x = e.pageX - this.translateX;
        var y = e.pageY - this.translateY;
        path.setAttribute("d", "M" + x + "," + y);
        path.setAttribute("stroke-width", "3");
        path.setAttribute("stroke", core.color);
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
    core.state = false;
};

function draw_onMouseMove(e)
{
    if (!core.state) return;
    switch (core.mode)
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
      core.state = core.state && !isOutside(e, this);
};

function core_onModeChanged(e)
{
    core.state = false;
};

function main()
{
    core.modeChanged.connect(this, core_onModeChanged);
    var draw = document.getElementById("draw");
    var mainGroup = document.getElementById("mainGroup");
    draw.mainGroup = mainGroup;
    draw.translateX = 0;
    draw.translateY = 0;
    draw.onmousedown = draw_onMouseDown;
    draw.onmouseup = draw_onMouseUp;
    draw.onmousemove = draw_onMouseMove;
    draw.onmouseout = draw_onMouseOut;
    core.readyToWork();
};

function globalError(message)
{
    alert(message);
};

window.onload = main;
window.onerror = globalError;
