function Transform() {
    this.parse = function(str)
         {
             var m = str.slice(7, -1).split(" ");
             m = [+m[0], +m[1], +m[2], +m[3], +m[4], +m[5]];
             return m
         }

    this.compose = function(m)
         {
             return "matrix(" + m.join(" ") + ")";
         }

    this.translate = function(x, y)
         {
             return [+1, +0, +0, +1, +x, +y];
         }

    this.rotate = function(a)
         {
             var s = Math.sin(a);
             var c = Math.cos(a);
             return [+c, +s, -s, +c, +0, +0];
         }

    this.mult = function(a, b)
         {
             return [a[0] * b[0] + a[2] * b[1],
                     a[1] * b[0] + a[3] * b[1],
                     a[0] * b[2] + a[2] * b[3],
                     a[1] * b[2] + a[3] * b[3],
                     a[0] * b[4] + a[2] * b[5] + a[4],
                     a[1] * b[4] + a[3] * b[5] + a[5]];
         }

    this.apply = function(m, v)
         {
             return [m[0] * v[0] + m[2] * v[1] + m[4],
                     m[1] * v[0] + m[3] * v[1] + m[5]];
         }

    this.reverse = function(m)
         {
             return[m[0], m[1], m[2], m[3], -m[4], -m[5]];
         }
}

var $T = new Transform();
