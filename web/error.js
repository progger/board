window.onerror = function(message, source, lineno)
        {
            var total = "";
            if (message)
            {
                total += "Ошибка: " + message + "\n";
            }
            if (source && (source !== "undefined"))
            {
                total += "Файл: " + source + "\n";
            }
            if (lineno)
            {
                total += "Строка: " + lineno;
            }
            alert(total);
        }
