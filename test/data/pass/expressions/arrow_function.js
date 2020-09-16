let a = () => {};
let b = () => 1;
let bb = () => ({});
let c = () => { return 2; };
let d = x => x;
let d0 = x => (x);
let d1 = x => x, y;
let d2 = x => (x, y);
let e = (x) => x;
let f = (x) => { return x; };
let g = (x, y,) => { return x; };
let h = (x, y = 10) => { return y; };

let i = (...x) => { return x; };
let j = (x, ...y) => { return y; };
let k = (...[x = 1, y]) => { return {x, y}; };
let l = (...{x, y = 2}) => { return {x, y}; };

let m = ([x, y]) => { return {x, y}; };
let n = ({x, y}) => { return {x, y}; };
let o = (a, [b, c], d, {e, f}, g, ...h) => {
   return {a, b, c, d, e, f, g, h};
};
let p = (a = 1, [b = 2, c, {d = 3, e}], {f = 3, g}) => {
   return {a, b, c, d, e, f, g};
};
