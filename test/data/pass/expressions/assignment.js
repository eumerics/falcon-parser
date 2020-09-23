// destructuring assignment
{
   // -- array assignment
   let a, b, c, d, e, f, g, h, i, j, k, l, m;
   let n, o, p, q, r, s, t, u, v, w, x, y, z = {a, b, c, d, e};
   function fun(){ return z; }
   // ----- elision
   [a] = [1];
   [b,] = [1];
   [,c] = [1, 2];
   [d,,e] = [1, 2, 3];
   // ----- rest
   //[...e, f] = [1, 2, 3];
   [...f] = [1, 2, 3];
   [g, ...h] = [1, 2, 3];
   [, i, j, ...k] = [1, 2, 3];
   [...[l, ...m]] = [1, 2, 3];
   [...[...[...[...n]]]] = [1, 2];
   // ----- initialization and nesting
   [o = [1, 2]] = [];
   [p = [q, r] = [1, 2]] = [];
   [s = [t, u = 1, [v, w] = [x, [, y = 2] = [3, [4]]]]] = [];
   // ----- lhs expressions other than identifier
   [z.a, [z.b, ...[z.c, z.d, fun().e]]] = [1, 2, 3, 4, 5]; // funny :) get it?!
   // ----- array equivalents
   [a];
   [b,];
   [,c];
   [d,,e];
   [...f];
   [g, ...h];
   [, i, j, ...k];
   [...[l, ...m]];
   [...[...[...[...n]]]];
   [o = [1, 2]];
   [p = [q, r]];
   [s = [t, u = 1, [v, w] = [x, [, y = 2] = [3, [4]]]]];
}
{
   // -- object assignment
   let a, b, c, d, e, f, g, h, i, j, k, l, m;
   let n, o, p, q, r, s, t, u, v, w, x, y, z;
   // the former below is a neater vesion of the latter, we will use that format
   z = {a} = {a: 1}; ({a} = {a: 1});
   z = {b, c: {d}} = {b: 1, c: {d: 2}};
   // ----- rest
   z = {...f} = {x: 1, y: 2};
   z = {g, ...h} = {g: 1, y: 2, z: 3};
   // 12.15.7.1: Static Semantics: Early Errors
   //    AssignmentRestProperty: ... DestructuringAssignmentTarget
   // It is a Syntax Error if DestructuringAssignmentTarget is an
   // ArrayLiteral or an ObjectLiteral
   //z = {...{l, ...m}} = {l: 1, x: 2, y: 3}; // not valid for some reason
   //z = {...{...{...{...n}}}} = {x: 1, y: 2, z: 3};
   // ----- initialization
   z = {o = {a: 1, b: 2}, oo = 3} = {};
   z = {p = {q, r} = {q: 1, r: 2}} = {};
   z = {s, t: {u = 10}} = {s: 1, t: {}};
   //z = {s = {t, u = 1, v: {w = {w: {x: 2}}}}} = {};
}
{
   // -- mixed assignment
   let a, b, c, d, e, f, g, h, i, j, k, l, m;
   let n, o, p, q, r, s, t, u, v, w, x, y, z;
   [a, {b, c}] = [1, {b: 2, c: 3}];
   z = {d, e: [f, g]} = {d: 1, e: [2, 3]};
   [h, {i = 4, j} = {i: 1, j: 2}] = [1, {b: 0, c: 0}];
   z = {k, l = [2, 3]} = {k: 1};
   [m, ...{0: n, o: {p} = {p: 3}}] = [1, 2];
   //[m, ...{0: n, o: {p} = {q, r} = {p: 3}}] = [1, 2];

   //({...(obj)} = foo);
}
