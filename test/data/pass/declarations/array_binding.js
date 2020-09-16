// simple binding
let [a] = [1]; // a = 1
let [b, c, d] = [1, 2, 3]; // b = 1, c = 2, d = 3

// rest element
let [...e] = [1, 2]; // e = [1, 2]
let [f, ...g] = [1, 2, 3]; // f = 1, g = [2, 3]
let [h, i, ...j] = [1, 2, 3, 4]; // h = 1, i = 2, j = [3, 4]

// elision
let [, k] = [1, 2]; // k = 2
let [,, l] = [1, 2, 3]; // l = 3
let [m,] = [1]; // m = 1
let [n,,o] = [1, 2, 3]; // n = 1, o = 3
let [p,,,] = [1]; // p = 1

// nesting
let [q, [r, s]] = [1, [2, 3]]; // q = 1, r = 2, s = 3
// [NOTE] is there a useful use case for rest element + array binding?
let [...[t, u]] = [1, 2]; // t = 1, u = 2
let [v, [w, [, x], ...y], z] = [1, [2, [3, 4], 5, 6], 7]; // v = 1, w = 2, x = 4, y = [5, 6], z = 7

// default initializations
let [aa, ab = 10] = [1]; // aa = 1, ab = 10
let [[ac, ad] = [1, 2]] = []; // ac = 1, ad = 2

// multiple binding patterns
let [ae] = [1, 2], [af] = [3]; // ae = 1, af = 3
