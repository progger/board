/*
 * Copyright (C) 2012 Kulabuhov Michail, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var Diff = {
    DiffItem:
    function(str1, str2) {
        var len1 = str1.length;
        var len2 = str2.length;
        var len = Math.min(len1, len2);
        var beg = 0;
        while ((str1[beg] == str2[beg]) &&
               (beg < len)) beg++;
        var end = 0;
        while ((str1[len1 - end] == str2[len2 - end]) &&
               (end < len - beg)) end++;

        this.begin = beg;
        this.end = len1 - end;
        this.str = str2.substring(beg, len2 - end);
    },

    undoStack: [],
    redoStack: [],
    begin_content: "<!--begin_content-->",
    end_content: "<!--end_content-->",

    getContent:
    function() {
        var canvas = document.getElementById("canvas");
        var html = canvas.innerHTML;
        var beg = html.indexOf(this.begin_content) + this.begin_content.length;
        var end = html.lastIndexOf(this.end_content);
        return html.substring(beg, end);
    },

    setContent:
    function(content) {
        var canvas = document.getElementById("canvas");
        var html = canvas.innerHTML;
        var beg = html.indexOf(this.begin_content) + this.begin_content.length;
        var end = html.lastIndexOf(this.end_content);
        canvas.innerHTML = html.substring(0, beg) +
                content +
                html.substring(end, html.length);
    },

    applyDiff:
    function(str, diff) {
        return str.substring(0, diff.begin) +
                diff.str +
                str.substring(diff.end, str.length);
    },

    checkpoint:
    function() {
        var content = this.getContent();
        if (!this.lastContnet) {
            this.lastContnet = content;
            return;
        }

        if (content == this.lastContnet) return;
        var diff = new this.DiffItem(content, this.lastContnet);
        this.undoStack.push(diff);
        this.redoStack.length = 0;
        this.lastContnet = content;
    },

    undoRedo:
    function(stack1, stack2) {
        if (!stack1.length) return;
        var content = this.getContent();
        var diff1 = stack1.pop();
        var newContent = this.applyDiff(content, diff1);
        var diff2 = new this.DiffItem(newContent, content);
        stack2.push(diff2);
        this.setContent(newContent);
        this.lastContnet = newContent;
    },

    undo:
    function() {
        this.undoRedo(this.undoStack, this.redoStack);
    },

    redo:
    function() {
        this.undoRedo(this.redoStack, this.undoStack);
    }
}

function undo() {
    Select.hide();
    Diff.undo();
}

function redo() {
    Select.hide();
    Diff.redo();
}
