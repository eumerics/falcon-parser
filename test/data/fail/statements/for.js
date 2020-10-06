for(const a;;);

// exclude "in" keyword in initialize expression
//<>
for(a in {};;);
//<>
for(a = x in {};;);
//<>
for(a=>a in b;;);
//<>
for(var a = x in {};;);
//<>
for(let a = x in {};;);
//<>
for(const a = x in {};;);
//<>
for(var [a];;);
//<>
for(let [a];;);
//<>
for(const [a];;);
//<>
for(var [a] = x in {};;);
//<>
for(let [a] = x in {};;);
//<>
for(const [a] = x in {};;);

// let as keyword or identifier?
//<>
for(let in;;);
//<>
for(let of []);
//<>
for(let.a of []);

// invalid initialization
//<>
'use strict';
for(var a=1 in {});
//<>
for(let a=1 in {});
//<>
for(const a=1 in {});
//<>
for(var [a, b] = [1, 2] in []);
//<>
for(let [a, b] = [1, 2] in []);

//<>
for(var a, b in {});
//<>
for(let a, b in {});
//<>
for(const a=1, b=2 in {});
//<>
for(a + b in {});
//<>
for(a + b of []);
//<>
for(let [a.b] in {});
//<>
for(a = 1 in {});
//<>
for(let a; )
//<>
for await(let a in {});
//<>
for await(a of []);
