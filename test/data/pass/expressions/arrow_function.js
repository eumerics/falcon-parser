{
   let a = () => {};
   let b = () => 1;
   let c = () => ({});
   let d = () => { return 2; };
   let e = x => x;
   let f = x => (x);
   let g = x => x, y;
   let h = x => (x, y);
   let i = (x) => x;
   let j = (x) => { return x; };
   let k = (x, y,) => { return x; };
   let l = (x, y = 10) => { return y; };

   let m = (...x) => { return x; };
   let n = (x, ...y) => { return y; };
   let o = (...[x = 1, y]) => { return {x, y}; };
   let p = (...{x, y = 2}) => { return {x, y}; };

   let q = ([x, y]) => { return {x, y}; };
   let r = ({x, y}) => { return {x, y}; };
   let s = (a, [b, c], d, {e, f}, g, ...h) => {
      return {a, b, c, d, e, f, g, h};
   };
   let t = (a = 1, [b = 2, c, {d = 3, e}], {f = 3, g}) => {
      return {a, b, c, d, e, f, g};
   };
}
{
   let a = async () => {};
   let b = async () => 1;
   let c = async () => ({});
   let d = async () => { return 2; };
   let e = async x => x;
   let f = async x => (x);
   let g = async x => x, y;
   let h = async x => (x, y);
   let i = async (x) => x;
   let j = async (x) => { return x; };
   let k = async (x, y,) => { return x; };
   let l = async (x, y = 10) => { return y; };

   let m = async (...x) => { return x; };
   let n = async (x, ...y) => { return y; };
   let o = async (...[x = 1, y]) => { return {x, y}; };
   let p = async (...{x, y = 2}) => { return {x, y}; };

   let q = async ([x, y]) => { return {x, y}; };
   let r = async ({x, y}) => { return {x, y}; };
   let s = async (a, [b, c], d, {e, f}, g, ...h) => {
      return {a, b, c, d, e, f, g, h};
   };
   let t = async (a = 1, [b = 2, c, {d = 3, e}], {f = 3, g}) => {
      return {a, b, c, d, e, f, g};
   };
}
{
   /* negative
   let b = async (await) => {};
   let a = async
   () => {};
   let b = async ()
   => {};
   */
}
/*
//({...(obj)}) => x;
*/
