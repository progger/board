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
}

window.onload = main;
