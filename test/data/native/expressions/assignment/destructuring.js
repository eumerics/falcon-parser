/// elision
[a] = [1]; //? <+>
[a,] = [1]; //? <+>
[,a] = [1, 2]; //? <+>
[a,,b] = [1, 2, 3]; //? <+>
/// rest
[...a] = [1, 2, 3]; //? <+>
[a, ...b] = [1, 2, 3]; //? <+>
[, a, b, ...c] = [1, 2, 3]; //? <+>
[...[a, ...b]] = [1, 2, 3]; //? <+>
[...[...[...[...a]]]] = [1, 2]; //? <+>
//- middle_rest
[...a, ] = []; //? <-> @1:2
[...a, b] = []; //? <-> @1:2
[...a, ...b] = []; //? <-> @1:2
[...a, b, ...c] = []; //? <-> @1:2
[...{a = 0}, ] = 0; //? <-> @1:2
/// initialization and nesting
[a = [1, 2]] = []; //? <+>
[a = [b, c] = [1, 2]] = []; //? <+>
[a = [b, c = 1, [d, e] = [f, [, g = 2] = [3, [4]]]]] = []; //? <+>
/// lhs expressions other than identifier
[...a.b] = []; //? <+>
[...a().b] = []; //? <+>
[...(a.b)] = []; //? <+>
[...(a().b)] = []; //? <+>
[a.b, [a.c, ...[a.d, a.e, f().g]]] = [1, 2, 3, 4, 5]; //? <+>


/// object assignment
z = {a: {a}, 'b': {b}, 1: {c}, [d]: d, e} = {}; //? <+>
/// rest
z = {...a} = {a: 1, b: 2}; //? <+>
z = {a, ...b} = {a: 1, b: 2, c: 3}; //? <+>
//- middle_rest
z = {...a, } = {}; //? <-> @1:6
z = {...a, b} = {}; //? <-> @1:6
z = {...a, ...b} = {}; //? <-> @1:6
z = {...a, b, ...c} = {}; //? <-> @1:6
// 12.15.7.1: Static Semantics: Early Errors
//    AssignmentRestProperty: ... DestructuringAssignmentTarget
// It is a Syntax Error if DestructuringAssignmentTarget is an
// ArrayLiteral or an ObjectLiteral
//z = {...{l, ...m}} = {l: 1, x: 2, y: 3}; // not valid for some reason
//z = {...{...{...{...n}}}} = {x: 1, y: 2, z: 3};
/// initialization
z = {a = {a: 1, b: 2}, b = 3} = {}; //? <+>
z = {a = {b, c} = {b: 1, c: 2}} = {}; //? <+>
z = {a, b: {c = 10}} = {a: 1, b: {}}; //? <+>
/// lhs expressions other than identifier
z = {...a.b} = {}; //? <+a>
z = {...a().b} = {}; //? <+a>
z = {...(a.b)} = {}; //? <+a>
z = {...(a().b)} = {}; //? <+a>
z = {a.b, {a.c, ...{a.d, a.e, a().f}}} = {}; //? <+a>

[a, {b, c}] = [1, {b: 2, c: 3}]; //? <+>
z = {a, b: [c, d]} = {a: 1, b: [2, 3]}; //? <+>
[a, {b = 1, c} = {b: 1, c: 2}] = [1, {b: 0, c: 0}]; //? <+>
z = {a, b = [1, 2]} = {a: 1}; //? <+>
[a, ...{0: b, c: {d} = {d: 3}}] = [1, 2]; //? <+>
[a, ...{0: b, c: {d} = {e, f} = {d: 3}}] = [1, 2]; //? <+>

//- invalid_assignment_target
z = {a(){}} = {}; //? <-> @1:6
z = {*a(){}} = {}; //? <-> @1:6
z = {async a(){}} = {}; //? <-> @1:6
z = {async* a(){}} = {}; //? <-> @1:6
z = {get a(){}} = {}; //? <-> @1:6
z = {set a(b){}} = {}; //? <-> @1:6
([a]) = 1; //? <-> @1:1
//- invalid_cover_grammar
z = {a = 0}; //? <-> @1:6
