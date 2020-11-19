let a = () => {}; //? <+>
let a = () => 0; //? <+>
let a = () => ({}); //? <+>
let a = () => { return 0; }; //? <+>
let a = () => function b(){}; //? <+>
let a = () => class b{}; //? <+>
let a = () => () => {}; //? <+>
let a = b => b; //? <+>
let a = b => (b); //? <+>
let a = b => b, c; //? <+>
let a, b = c => (a, c); //? <+>
let a = (b) => b; //? <+>
let a = (b) => { return b; }; //? <+>
let a = (b, c,) => { return b; }; //? <+>
let a = (b, c = 1) => { return c; }; //? <+>

let a = (...b) => { return b; }; //? <+>
let a = (b, ...c) => { return c; }; //? <+>
let a = (...[b = 1, c]) => { return {b, c}; }; //? <+>
let a = (...{b, c = 2}) => { return {b, c}; }; //? <+>

let a = ([b, c]) => { return {b, c}; }; //? <+>
let a = ({b, c}) => { return {b, c}; }; //? <+>
let a = (b, [c, d], e, {f, g}, h, ...i) => {
   return {b, c, d, e, f, g, h, i};
}; //? <+>
let a = (b = 1, [c = 2, d, {e = 3, f}], {g = 3, h}) => {
   return {b, c, d, e, f, g, h};
}; //? <+>

let a = async () => {}; //? <+>
let a = async () => 0; //? <+>
let a = async () => ({}); //? <+>
let a = async () => { return 0; }; //? <+>
let a = async () => function b(){}; //? <+>
let a = async () => class b{}; //? <+>
let a = async () => () => {}; //? <+>
let a = async b => b; //? <+>
let a = async b => (b); //? <+>
let a = async b => b, c; //? <+>
let a, b = async c => (a, c); //? <+>
let a = async (b) => b; //? <+>
let a = async (b) => { return b; }; //? <+>
let a = async (b, c,) => { return b; }; //? <+>
let a = async (b, c = 1) => { return c; }; //? <+>

let a = async (...b) => { return b; }; //? <+>
let a = async (b, ...c) => { return c; }; //? <+>
let a = async (...[b = 1, c]) => { return {b, c}; }; //? <+>
let a = async (...{b, c = 2}) => { return {b, c}; }; //? <+>

let a = async ([b, c]) => { return {b, c}; }; //? <+>
let a = async ({b, c}) => { return {b, c}; }; //? <+>
let a = async (b, [c, d], e, {f, g}, h, ...i) => {
   return {b, c, d, e, f, g, h, i};
}; //? <+>
let a = async (b = 1, [c = 2, d, {e = 3, f}], {g = 3, h}) => {
   return {b, c, d, e, f, g, h};
}; //? <+>
