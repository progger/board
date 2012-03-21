/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

function getMatrix(drawGroup)
{
    var attr = drawGroup.getAttribute("transform");
    return $T.parse(attr);
}

function getPos(m, e)
{
    var r = $T.reverse(m);
    return $T.apply(r, [e.pageX, e.pageY]);
}

function setMatrix(drawGroup, m)
{
    var attr = $T.compose(m);
    drawGroup.setAttribute("transform", attr);
}

function getTranslateAttr(x, y)
{
    return "translate(" + x + " " + y + ")";
}
