/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var svgns = "http://www.w3.org/2000/svg";
var xmlns = "http://www.w3.org/XML/1998/namespace"

function createSvgElement(name) {
    return document.createElementNS(svgns, name);
}

function createSvgPoint(x, y) {
    var content = document.getElementById("content");
    var p = content.createSVGPoint();
    p.x = x;
    p.y = y;
    return p;
}

function createSvgLength(length) {
    var content = document.getElementById("content");
    var len = content.createSVGLength();
    len.value = length;
    return len;
}

function isOutside(e, parent) {
  var relatedTarget = e.relatedTarget;
  while (relatedTarget && relatedTarget !== parent)
    relatedTarget = relatedTarget.parentNode;
  return !relatedTarget;
}

function setStyle(element) {
    var style = element.style;
    style.setProperty("fill", "none");
    style.setProperty("stroke", board.core.color);
    style.setProperty("stroke-width", 3);
}

function createTransform() {
    var content = document.getElementById("content");
    var transform = content.createSVGTransform();
    return transform;
}

function translate(element, x, y) {
    var transformList = element.transform.baseVal;
    var transform = createTransform();
    transform.setTranslate(x, y);
    transformList.appendItem(transform);
    transformList.consolidate();
}
