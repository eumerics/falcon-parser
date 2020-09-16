// simple binding
let {a} = {a: 1}; // a = 1
let {b, c, d} = {b: 1, c: 2, d: 3}; // b = 1, c = 2, d = 3

// rest element
let {...e} = {a: 1, b: 2}; // e = {a: 1, b: 2}
let {f, ...g} = {f: 1, c: 2, d: 3}; // f = 1, g = {c: 2, d: 3}
let {h, i, ...j} = {h: 1, i: 2, f: 3, g: 4}; // h = 1, i = 2, j = {f: 3, g: 4}

// elision is meaningless for object binding

// nesting
let {q, a: {r, s}} = {q: 1, a: {r: 2, s: 3}}; // q = 1, r = 2, s = 3 (a is not declared or defined)
let {v, a: {w, b: {x}, ...y}, z} = {v: 1, a: {w: 2, b: {a: 3, x: 4}, c: 5, d: 6}, z: 7}; // v = 1, w = 2, x = 4, y = {c: 5, d: 6}, z = 7

// default initializations
let {aa, ab = 10} = {aa: 1}; // aa = 1, ab = 10
let {a: {ac, ad} = {ac: 1, ad: 2}} = {}; // ac = 1, ad = 2

// multiple binding patterns
let {ae} = {ae: 1, af: 2}, {af = 3} = {}; // ae = 1, af = 3
