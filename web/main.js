function main()
{
    var draw = document.getElementById("draw");
    draw.translateX = 0;
    draw.translateY = 0;
    draw.onmousedown = draw_onMouseDown;
    draw.onmouseup = draw_onMouseUp;
    draw.onmousemove = draw_onMouseMove;
    draw.onmouseout = draw_onMouseOut;
    coreObject.readyToWork();
}

window.onload = main;
