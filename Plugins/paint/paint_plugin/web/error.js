/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

window.onerror = function(message, source, lineno)
        {
            var total = message;
            if (source && (source !== "undefined"))
            {
                total += "\nFile: " + source;
            }
            if (lineno)
            {
                total += "\nRow: " + lineno;
            }
            alert(total);
        }
