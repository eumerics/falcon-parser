// function* token
function* a() {}
function *a() {}
function * a() {}
function
* a() {}
function
*
a() {}

// function name
function* yield() {}

// function arguments
function* a(b) {}
function* a(b,) {}
function* a(b, c) {}
//function* a(b,,c) {}
function* a(...b) {}
//function* a(...b,) {}
//function* a(...b, c) {}
function* a(b, ...c) {}
function* a([b]) {}
function* a(b = 0) {}
function* a([b] = [0]) {}
//function* a(b = yield) {} early
//function* a(b = yield.a) {}
//function* a(b = [yield]) {} early
//function* a(b = [...yield]) {} early
//function* a(b = {[yield]: 0}) {} early
function* a(b = {yield(){}}) {}
function* a(b = {c(yield){}}) {}

// function body
function* a(){ yield; }
//function* a(){ yield.a; }
function* a(){ [yield]; }
function* a(){ [...yield]; }
//function* a(){ ({yield})}
//function* a(){ ({yield = 0})}
function* a(){ ({b = yield} = {}); }
function* a(){ ({yield: 0}); }
function* a(){ ({0: yield}); }
function* a(){ ({[yield]: 0}); }
function* a(){ ({yield(){}}); }
function* a(){ ({b(yield){}}); }
function* a(){ ({yield(yield){}}); }
function* a(){ ({[yield](){}}); }
function* a(){ ({[yield](yield){}}); }
function* a(){ ({get yield(){}}); }
function* a(){ ({set yield(a){}}); }
function* a(){ ({set b(yield){}}); }
function* a(){ ({set yield(yield){}}); }
function* a(){ ({...yield}); }
function* a(){ (function(yield){}); }
function* a(){ (function(){ yield.a }); }
function* a(){ (function(){ var yield; }); }
function* a(){ (function(){ let yield; }); }
function* a(){ (function(){ yield: ; }); }
function* a(){ (async function(yield){}); }
function* a(){ (async function(){ yield.a }); }
function* a(){ (async function(){ var yield; }); }
function* a(){ (async function(){ let yield; }); }
function* a(){ (async function(){ yield: ; }); }
function* a(){ `${yield}`; }
function* a(){ (yield); }
//function* a(){ yield => {}; }
//function* a(){ (yield) => {}; } early
//function* a(){ (b = yield) => {}; } early
function* a(){ b[yield]; }
function* a(){ b`${yield}`; }
function* a(){ new b(yield); }
function* a(){ true ? yield : 0; }
function* a(){ false ? 0 : yield; }
function* a(){ b(yield); }
function* a(){ b(...yield); }
