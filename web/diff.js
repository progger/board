/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

function DiffItem(str1, str2) {
    var len1 = str1.length;
    var len2 = str2.length;
    var len = Math.min(len1, len2);
    var beg = 0;
    while ((str1[beg] == str2[beg]) && (beg < len)) beg++;
    var end = 0;
    while ((str1[len1 - end] == str2[len2 - end]) && (end < len - beg)) end++;

    this.begin = beg;
    this.end = len1 - end;
    this.str = str2.substring(beg, len2 - end);
}

var undoStack = [];
var redoStack = [];
var lastContnet;
var begin_content = "<!--begin_content-->";
var end_content = "<!--end_content-->";

function getContent() {
    var canvas = document.getElementById("canvas");
    var html = canvas.innerHTML;
    var beg = html.indexOf(begin_content) + begin_content.length;
    var end = html.lastIndexOf(end_content);
    return html.substring(beg, end);
}

function setContent(content) {
    var canvas = document.getElementById("canvas");
    var html = canvas.innerHTML;
    var beg = html.indexOf(begin_content) + begin_content.length;
    var end = html.lastIndexOf(end_content);
    canvas.innerHTML = html.substring(0, beg) +
            content +
            html.substring(end, html.length);
}

function applyDiff(str, diff) {
    return str.substring(0, diff.begin) +
            diff.str +
            str.substring(diff.end, str.length);
}

function checkpoint() {
    var content = getContent();
    if (!lastContnet) {
        lastContnet = content;
        return;
    }

    var diff = new DiffItem(content, lastContnet);
    undoStack.push(diff);
    redoStack.length = 0;
    lastContnet = content;
}

function undoRedo(stack1, stack2) {
    if (!stack1.length) return;
    var content = getContent();
    var diff1 = stack1.pop();
    var newContent = applyDiff(content, diff1);
    var diff2 = new DiffItem(newContent, content);
    stack2.push(diff2);
    setContent(newContent);
    lastContnet = newContent;
}

function undo() {
    undoRedo(undoStack, redoStack);
}

function redo() {
    undoRedo(redoStack, undoStack);
}
