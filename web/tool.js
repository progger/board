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

function createSvgElement(name)
{
    var ns = "http://www.w3.org/2000/svg";
    return document.createElementNS(ns, name);
}

function getDrawGroup(draw)
{
    return draw.firstChild.firstChild;
}

function setDrawStyleAttr(element)
{
    var fill = "fill:none;";
    var stroke = "stroke:" + drawObject.color + ";";
    var strokeWidth = "stroke-width:3px;";
    element.setAttribute("style", fill + stroke + strokeWidth);
}
