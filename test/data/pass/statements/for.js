for(;;);
for(;;){}
for(1;;);
for(;2;);
for(;;3);
for(1;2;);
for(;2;3);
for(1;;3);
for(1;2;3);

for(a; a < 1; ++a);
for(var a; a < 1; ++a);
for(let a; a < 1; ++a);
//for(const a; a < 1; ++a);
for(a = 0; a < 1; ++a);
for(var a = 0; a < 1; ++a);
for(let a = 0; a < 1; ++a);
for(const a = 0; a < 1; ++a);

for(var [a] = [1];;);
for(let [a] = [1];;);
for(const [a] = [1];;);

for(; a in {};);
for(;; a in {});
for(var a = (b in {});;);
for(var a = [b in {}];;);
for(var [a] = [b in {}];;);
for(var [a = b in {}] = [1];;);

for(b in {});
for(var b in {});
for(let b in {});
for(const b in {});

for(var [a] in {});
for(let [a] in {});
for(const [a] in {});

for(c of []);
for(var c of []);
for(let c of []);
for(const c of []);

for(var [a] of []);
for(let [a] of []);
for(const [a] of []);

// let as keyword or identifier?
for(let.a;;);
//for(let/a;;);
for(let of;;);
for(let in {});
for(let.a in {});

async function f(){
   for await(c of []);
   for await(var c of []);
   for await(let c of []);
   for await(const c of []);
   for await(let [a, b = [c = 3], d] of {});
   for await(let {a, b: [c = 3], d} of {});
}

for(a, b = 2, [c] = [3], {d} = {d: 4};;);
for([a, b = [c = 3], d];;);

for(let [a, b = [c = 3], d] in {});
for(let [a, b = [c = 3], d] of []);
for(let {a, b: [c = 3], d} in {});
for(let {a, b: [c = 3], d} of {});

for(var a = 1 in []); //legacy
