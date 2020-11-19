/// multiplicative operators
1 * 2; //? <+>
1 / 2; //? <+>
1 % 2; //? <+>

/// additive operators
1 + 2; //? <+>
1 - 2; //? <+>

/// shift operators
1 << 2; //? <+>
1 >> 2; //? <+>
-1 >>> 2; //? <+>

/// relational operators
1 < 2; //? <+>
1 > 2; //? <+>
1 <= 2; //? <+>
1 >= 2; //? <+>
[] instanceof Array; //? <+>
a in {a: 1}; //? <+>

/// equality operators
1 == 2; //? <+>
1 != 2; //? <+>
undefined === null; //? <+>
undefined !== null; //? <+>

/// bitwise: descending precedence
1 & 2; //? <+>
1 ^ 2; //? <+>
1 | 2; //? <+>

/// logical: descending precedence
true && false; //? <+>
true || false; //? <+>
undefined ?? null; //? <+>

/// test operator precedence
1 + 2 + 3; //? <+>
1 - 2 - 3; //? <+>
1 + 2 - 3; //? <+>
1 - 2 + 3; //? <+>
///
1 + 2 * 3; //? <+>
1 * 2 + 3; //? <+>
(1 + 2) * 3; //? <+>
1 * (2 + 3); //? <+>
///
1 + 2 + 3 + 4; //? <+>

async function a() { await a ** b; } //? <-> @1:30
