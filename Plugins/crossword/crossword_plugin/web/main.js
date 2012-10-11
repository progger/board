var $ = board.plugin.crossword;

function drawCrossword() {
    var crossword = document.getElementById("crossword");
    var questions = document.getElementById("questions");
    for (y = 0; y < $.height; y++) {
        var row = crossword.insertRow(-1);
        for (x = 0; x < $.width; x++) {
            var cell = row.insertCell(-1);
            var letter = $.grid(x, y);
            if (letter == ".")
            {
                cell.style.setProperty("background-color", "black");
            }
            else
            {
                cell.innerHTML = letter;
            }
        }
    }
}

function main() {
    drawCrossword();
}

window.onload = main;
