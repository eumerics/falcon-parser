// test all binary operators
1 * 2; 3 / 4; 5 % 6; // multiplicative: equal procdence
7 + 8; 9 - 0; // additive: equal precedence
1 << 2; 9 >> 2; -1 >>> 0; // shift: equal precedence
1 < 2; 3 > 4; 5 <= 6; 7 >= 7; [] instanceof Array; a in {a: 1}; // relational: equal procdence
1 == 2; 3 != 4; undefined === null; undefined !== null; // equality: equal precedence
1 & 2; 3 ^ 4; 5 | 6; // bitwise: descending precedence
true && false; true || false; undefined ?? null; // logical: descending precedence

// test operator precedence
1 + 2 + 3;
3 - 4 - 5;
6 + 7 - 8;
8 - 9 + 0;

1 + 2 * 3;
1 * 2 + 3;
(1 + 2) * 3;
1 * (2 + 3);

1 + 2 + 3 + 4;
