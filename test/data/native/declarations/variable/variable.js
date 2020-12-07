var a; //? <+>
var a = 1; //? <+>
var a = 1, b = 2; //? <+>
var a = 1, b, c = 2; //? <+>
var a, b = 2, c; //? <+>

let a; //? <+>
let a = 1; //? <+>
let a = 1, b = 2; //? <+>
let a = 1, b, c = 2; //? <+>
let a, b = 2, c; //? <+>

//- missing_const_initializer
const a; //? <-> @1:8
const a = 1; //? <+>
const a = 1, b = 2; //? <+>
const a = 1, b, c = 2; //? <-> @1:15
const a = 1, b = 2, c; //? <-> @1:22

let a = b = 1; //? <+>
