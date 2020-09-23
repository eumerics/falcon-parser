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

for(b in {});
for(var b in {});
for(let b in {});
for(const b in {});

for(c of []);
for(var c of []);
for(let c of []);
for(const c of []);

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

//for(var x = ('x' in {x: 1}); false;);
//for(var x = 1 in []); //legacy
//for(var [x, y] = [1, 2] in []);
//for(var x = 1 in []; false; );
//for (x=>x in y;;);
