/// simple binding
let [a] = [1]; // a = 1 //? <+>
let [a, b, c] = [1, 2, 3]; // a = 1, b = 2, c = 3 //? <+>

/// rest element
let [...a] = [1, 2]; // a = [1, 2] //? <+>
let [a, ...b] = [1, 2, 3]; // a = 1, b = [2, 3] //? <+>
let [a, b, ...c] = [1, 2, 3, 4]; // a = 1, b = 2, c = [3, 4] //? <+>

/// elision
let [, a] = [1, 2]; // a = 2 //? <+>
let [,, a] = [1, 2, 3]; // a = 3 //? <+>
let [a,] = [1]; // a = 1 //? <+>
let [a,,b] = [1, 2, 3]; // a = 1, b = 3 //? <+>
let [a,,,] = [1]; // a = 1 //? <+>

/// nesting
let [a, [b, c]] = [1, [2, 3]]; // a = 1, b = 2, c = 3 //? <+>
// [NOTE] is there a useful use case for rest element + array binding?
let [...[a, b]] = [1, 2]; // a = 1, b = 2 //? <+>
let [a, [b, [, c], ...d], e] = [1, [2, [3, 4], 5, 6], 7]; // a = 1, b = 2, c = 4, d = [5, 6], e = 7 //? <+>

/// default initializations
let [a, b = 10] = [1]; // a = 1, b = 10 //? <+>
let [[a, b] = [1, 2]] = []; // a = 1, b = 2 //? <+>

/// multiple binding patterns
let [a] = [1, 2], [b] = [3]; // a = 1, b = 3 //? <+>
