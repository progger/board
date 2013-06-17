/*
 * Copyright (C) 2012 Michael Kulabuhov, Kemerovo, Russia.
 *
 * See the LICENSE file for terms of use.
 */

var keys = [
            [
                {button: [["1", "!"], ["1", "!"]], size: 1},
                {button: [["2", "@"], ["2", "\""]], size: 1},
                {button: [["3", "#"], ["3", "№"]], size: 1},
                {button: [["4", "$"], ["4", ";"]], size: 1},
                {button: [["5", "%"], ["5", "%"]], size: 1},
                {button: [["6", "^"], ["6", ":"]], size: 1},
                {button: [["7", "&"], ["7", "?"]], size: 1},
                {button: [["8", "*"], ["8", "*"]], size: 1},
                {button: [["9", "("], ["9", "("]], size: 1},
                {button: [["0", ")"], ["0", ")"]], size: 1},
                {button: [["-", "_"], ["-", "_"]], size: 1},
                {button: [["=", "+"], ["=", "+"]], size: 1},
                {button: [["", ""], ["", ""]], size: 1.5, image: "backspace.svg", key: Qt.Key_Backspace},
            ],
            [
                {button: [["q", "Q"], ["й", "Й"]], size: 1},
                {button: [["w", "W"], ["ц", "Ц"]], size: 1},
                {button: [["e", "E"], ["у", "У"]], size: 1},
                {button: [["r", "R"], ["к", "К"]], size: 1},
                {button: [["t", "T"], ["е", "Е"]], size: 1},
                {button: [["y", "Y"], ["н", "Н"]], size: 1},
                {button: [["u", "U"], ["г", "Г"]], size: 1},
                {button: [["i", "I"], ["ш", "Ш"]], size: 1},
                {button: [["o", "O"], ["щ", "Щ"]], size: 1},
                {button: [["p", "P"], ["з", "З"]], size: 1},
                {button: [["[", "{"], ["х", "Х"]], size: 1},
                {button: [["]", "}"], ["ъ", "Ъ"]], size: 1},
                {button: [["\\", "|"], ["\\", "/"]], size: 1},
            ],
            [
                {button: [["a", "A"], ["ф", "Ф"]], size: 1},
                {button: [["s", "S"], ["ы", "Ы"]], size: 1},
                {button: [["d", "D"], ["в", "В"]], size: 1},
                {button: [["f", "F"], ["а", "А"]], size: 1},
                {button: [["g", "G"], ["п", "П"]], size: 1},
                {button: [["h", "H"], ["р", "Р"]], size: 1},
                {button: [["j", "J"], ["о", "О"]], size: 1},
                {button: [["k", "K"], ["л", "Л"]], size: 1},
                {button: [["l", "L"], ["д", "Д"]], size: 1},
                {button: [[";", ":"], ["ж", "Ж"]], size: 1},
                {button: [["'", "\""], ["э", "Э"]], size: 1},
                {button: [["", ""], ["", ""]], size: 1.5, image: "enter.svg", key: Qt.Key_Enter},
            ],
            [
                {button: [["z", "Z"], ["я", "Я"]], size: 1},
                {button: [["x", "X"], ["ч", "Ч"]], size: 1},
                {button: [["c", "C"], ["с", "С"]], size: 1},
                {button: [["v", "V"], ["м", "М"]], size: 1},
                {button: [["b", "B"], ["и", "И"]], size: 1},
                {button: [["n", "N"], ["т", "Т"]], size: 1},
                {button: [["m", "M"], ["ь", "Ь"]], size: 1},
                {button: [[",", "<"], ["б", "Б"]], size: 1},
                {button: [[".", ">"], ["ю", "Ю"]], size: 1},
                {button: [["/", "?"], [".", ","]], size: 1},
                {button: [["Shift", "Shift"], ["Shift", "Shift"]], size: 1.5, click: "shiftClick"},
            ],
            [
                {button: [["рус", "рус"], ["eng", "eng"]], size: 1.5, click: "layoutClick"},
                {button: [[" ", " "], [" ", " "]], size: 7.5},
                {button: [["", ""], ["", ""]], size: 1, image: "left_arrow.svg", key: Qt.Key_Left},
                {button: [["", ""], ["", ""]], size: 1, image: "right_arrow.svg", key: Qt.Key_Right},
            ]
        ];

function charClick(button, data) {
    var text = data.button[keyboard.layout][keyboard.shift];
    var key = data.key ? data.key : 0;
    Core.emulateKeyPress(key, 0, text);
}

function layoutClick(button, data) {
    keyboard.layout = !keyboard.layout;
}

function shiftClick(button, data) {
    keyboard.shift = !keyboard.shift;
    button.toggled = keyboard.shift
}

function click(button, data) {
    if (!data.click) {
        charClick(button, data);
    }
    else {
        this[data.click](button, data);
    }
}

function getMaxLength() {
    var max = 0;
    for (var i in keys) {
        var row = keys[i];
        var len = 0;
        for (var j in row) {
            len += row[j].size;
        }
        if (len > max) {
            max = len;
        }
    }
    return max;
}
