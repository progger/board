function draw_onMouseDown(e)
{
    if (e.which !== 1) return;
    this.state = true;
    var ns = this.getAttribute("xmlns");
    var path = document.createElementNS(ns, "path");
    path.setAttribute("d", "M" + e.pageX + "," + e.pageY);
    path.setAttribute("stroke-width", "3");
    path.setAttribute("stroke", "black");
    path.setAttribute("fill", "none");
    this.path = path;
    this.appendChild(path);
};

function draw_onMouseUp(e)
{
    if (e.which !== 1) return;
    this.state = false;
}

function draw_onMouseMove(e)
{
    if (!this.state) return;
    var path = this.path;
    var d = path.getAttribute("d");
    d += "L" + e.pageX + "," + e.pageY;
    path.setAttribute("d", d);
}

function main()
{
    var draw = document.getElementById("drawElement");
    draw.state = false;
    draw.onmousedown = draw_onMouseDown;
    draw.onmouseup = draw_onMouseUp;
    draw.onmousemove = draw_onMouseMove;
};

window.onload = main;
