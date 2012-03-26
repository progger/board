/*
 * Copyright (C) 2011 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var colors = [
            {color: "#000000", freq: 1},
            {color: "#ff0000", freq: 1},
            {color: "#00ff00", freq: 1},
            {color: "#0000ff", freq: 1},
            {color: "#ffff00", freq: 1},
            {color: "#ff00ff", freq: 1},
            {color: "#00ffff", freq: 1},
            {color: "#800000", freq: 1},
            {color: "#008000", freq: 1},
            {color: "#000080", freq: 1},
            {color: "#808000", freq: 1},
            {color: "#800080", freq: 1},
            {color: "#008080", freq: 1}
        ];

function sortColors() {
    function sortFunc(a, b) {
        return a.freq - b.freq;
    }
    colors.sort(sortFunc);
}

function clickColor(index) {
    if (selected == index) return;
    changeColor(index);
}

function changeColor(index) {
    selected = index;
    var item = repeater.itemAt(index);
    Core.color = item.color;

    for (var i = 0; i < numButtons; i++) {
        item = repeater.itemAt(i);
        if (i == selected) {
            item.freq++;
        }
        else {
            item.freq *= 0.9;
        }
    }

    for (i in colors) {
        var obj = colors[i];
        if (obj.color == item.color) {
            obj.freq++
        }
        else {
            obj.freq *= 0.95;
        }
    }
}

function moreClick() {
    if (colorGridRect.opacity) {
        colorGridRect.opacity = 0;
    }
    else {
        showColorGrid();
    }
}

function showColorGrid() {
    sortColors();
    colorGridModel.clear();
    for (var i in colors) {
        var color = colors[i].color;
        if (checkColor(color)) continue;
        colorGridModel.append({color: color});
    }
    colorGridRect.opacity = 1;
}

function checkColor(color) {
    for (var i = 0; i < numButtons; i++) {
        var item = repeater.itemAt(i);
        if (color == item.color) return true;
    }
    return false;
}

function selectColor(color) {
    colorGridRect.opacity = 0;
    var index = getMinBar();
    var item = repeater.itemAt(index);
    item.freq = 1
    item.color = color;
    changeColor(index);
}

function getMinBar() {
    var index = 0;
    var min = repeater.itemAt(index).freq;
    for (var i = 1; i < numButtons; i++) {
        var item = repeater.itemAt(i);
        if (min > item.freq) {
            index = i;
            min = item.freq;
        }
    }
    return index
}

function selectCustomColor(index) {
    var item = repeater.itemAt(index);
    var color = Core.selectColor(item.color);
    if (!colorExsits(color)) {
        colors.push({color: color, freq: 1});
    }
    item.freq = 1;
    item.color = color;
    changeColor(index);
}

function colorExsits(color) {
    for (var i in colors) {
        if (color == colors[i].color) return true;
    }
    return false;
}
