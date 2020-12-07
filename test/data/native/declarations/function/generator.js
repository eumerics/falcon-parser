/// variations of function* tokens
function* a() {} //? <+>
function *a() {} //? <+>
function * a() {} //? <+>
function
* a() {} //? <+>
function
*
a() {} //? <+>

/// formal parameters
function* a(b) {} //? <+>
function* a(b,) {} //? <+>
function* a(b, c) {} //? <+>
function* a(b,,c) {} //? <-> @1:15
function* a(...b) {} //? <+>
function* a(...b,) {} //? <-> @1:17 -middle_rest
function* a(...b, c) {} //? <-> @1:17 -middle_rest
function* a(b, ...c) {} //? <+>
function* a([b]) {} //? <+>
function* a(b = 0) {} //? <+>
function* a([b] = [0]) {} //? <+>

// yield as function name
function* yield() {} //? <+?>

/// yield as an identifier in parameter list
//- contextual_identifier
function* a(yield) {} //? <-> @1:13
function* a([yield]) {} //? <-> @1:14
function* a(b = yield) {} //? <-> @1:17
function* a(b = yield.a) {} //? <-> @1:17
function* a(b = [yield]) {} //? <-> @1:18
function* a(b = [...yield]) {} //? <-> @1:21
function* a(b = {yield}) {} //? <-> @1:18
function* a(b = {yield = 0}) {} //? <-> @1:18
function* a(b = {[yield]: 0}) {} //? <-> @1:19
function* a(b = {...yield}) {} //? <-> @1:21
/// yield as non-identifier in parameter list
function* a(b = {yield(){}}) {} //? <+>
function* a(b = {c(yield){}}) {} //? <+>

/// yield in body
function* a(){ yield; } //? <+>
function* a(){ yield.a; } //? <-> @1:21 -default
function* a(){ [yield]; } //? <+>
function* a(){ [...yield]; } //? <+>
function* a(){ !{yield}; } //? <-> @1:18
function* a(){ !{yield = 0}; } //? <-> @1:18
function* a(){ !{[yield]: 0}; } //? <+>
function* a(){ !{...yield}; } //? <+>
function* a(){ !{yield(){}}; } //? <+>
function* a(){ !{b(yield){}}; } //? <+>
function* a(){ yield = 0; } //? <-> @1:22 -default

//- contextual_identifier
function* a(){ ({b = yield} = {}); } //? <+>
function* a(){ ({yield: 0}); } //? <+>
function* a(){ ({0: yield}); } //? <+>
function* a(){ ({[yield]: 0}); } //? <+>
function* a(){ ({yield(){}}); } //? <+>
function* a(){ ({b(yield){}}); } //? <+>
function* a(){ ({yield(yield){}}); } //? <+>
function* a(){ ({[yield](){}}); } //? <+>
function* a(){ ({[yield](yield){}}); } //? <+>
function* a(){ ({get yield(){}}); } //? <+>
function* a(){ ({set yield(a){}}); } //? <+>
function* a(){ ({set b(yield){}}); } //? <+>
function* a(){ ({set yield(yield){}}); } //? <+>
function* a(){ ({...yield}); } //? <+>
function* a(){ (function(yield){}); } //? <+>
function* a(){ (function(){ yield.a }); } //? <+>
function* a(){ (function(){ var yield; }); } //? <+>
function* a(){ (function(){ let yield; }); } //? <+>
function* a(){ (function(){ yield: ; }); } //? <+>
function* a(){ (async function(yield){}); } //? <+>
function* a(){ (async function(){ yield.a }); } //? <+>
function* a(){ (async function(){ var yield; }); } //? <+>
function* a(){ (async function(){ let yield; }); } //? <+>
function* a(){ (async function(){ yield: ; }); } //? <+>
function* a(){ `${yield}`; } //? <+>
function* a(){ (yield); } //? <+>
function* a(){ b[yield]; } //? <+>
function* a(){ b`${yield}`; } //? <+>
function* a(){ new yield; } //? <-> @1:20
function* a(){ new b(yield); } //? <+>
function* a(){ true ? yield : 0; } //? <+>
function* a(){ false ? 0 : yield; } //? <+>
function* a(){ b(yield); } //? <+>
function* a(){ b(...yield); } //? <+>
function* a(){ yield => {}; } //? <-> @1:22 -default
function* a(){ (yield) => {}; } //? <-> @1:17 -yield_await_in_arrow_params
function* a(){ (b = yield) => {}; } //? <-> @1:21 -yield_await_in_arrow_params
function* a(){ var yield; } //? <-> @1:20
function* a(){ let yield; } //? <-> @1:20
function* a(){ yield: ; } //? <-> @1:16
