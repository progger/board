/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Select = {
    begin:
    function(start) {
        var element = document.getElementById("select_rect");
        element.setAttribute("visibility", "visible");
        Rectangle.draw(element, start, start);
    },

    draw:
    function(start, p) {
        var element = document.getElementById("select_rect");
        Rectangle.draw(element, start, p);
    },

    end:
    function() {
        var element = document.getElementById("select_rect");
        element.setAttribute("visibility", "hidden");
        alert(element.getAttribute("visibility"));
    }
}
