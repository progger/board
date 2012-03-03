function isOutside(e, parent)
{
  var relatedTarget = e.relatedTarget;
  while (relatedTarget && relatedTarget !== parent)
    relatedTarget = relatedTarget.parentNode;
  return !relatedTarget;
}

function getTranslateAttr(x, y)
{
    return "translate(" + x + " " + y + ")";
}

function createDrawElement(draw, name)
{
    var ns = draw.getAttribute("xmlns");
    return document.createElementNS(ns, name);
}

function setDrawStyleAttr(element)
{
    var fill = "fill:none;";
    var stroke = "stroke:" + drawObject.color + ";";
    var strokeWidth = "stroke-width:3px;";
    element.setAttribute("style", fill + stroke + strokeWidth);
}
