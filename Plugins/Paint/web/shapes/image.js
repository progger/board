/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Image = {
    begin:
    function(start) {
        var element = createSvgElement("image");
        var w = board.core.imageWidth;
        var h = board.core.imageHeight;
        element.x.baseVal.value = -w / 2;
        element.y.baseVal.value = -h / 2;
        element.width.baseVal.value = w;
        element.height.baseVal.value = h;
        element.href.baseVal = board.core.imageContent;
        translate(element, start.x, start.y);
        return element;
    }
}
