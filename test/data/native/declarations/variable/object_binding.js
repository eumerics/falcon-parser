/// simple binding
let {a} = {a: 1}; // a = 1 //? <+>
let {a, b, c} = {a: 1, b: 2, c: 3}; // a = 1, b = 2, c = 3 //? <+>

/// rest element
let {...a} = {a: 1, b: 2}; // a = {a: 1, b: 2} //? <+>
let {a, ...b} = {a: 1, b: 2, c: 3}; // a = 1, b = {b: 2, c: 3} //? <+>
let {a, b, ...c} = {a: 1, b: 2, c: 3, d: 4}; // a = 1, b = 2, c = {c: 3, d: 4} //? <+>

/// elision is meaningless for object binding

/// nesting
let {a, b: {c, d}} = {a: 1, b: {c: 2, d: 3}}; // a = 1, c = 2, d = 3 //? <+>
let {a, b: {c, d: {e}, ...f}, g} = {a: 1, b: {c: 2, d: {a: 3, e: 4}, c: 5, d: 6}, g: 7}; // a = 1, c = 2, e = 4, f = {c: 5, d: 6}, g = 7 //? <+>

/// default initializations
let {a, b = 10} = {a: 1}; // a = 1, a = 10 //? <+>
let {a: {a, b} = {a: 1, b: 2}} = {}; // a = 1, b = 2 //? <+>

/// multiple binding patterns
let {a} = {a: 1, b: 2}, {c = 3} = {}; // a = 1, c = 3 //? <+>
