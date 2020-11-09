a: break a; //? <+>
a: if(0) break a; //? <+>
a: if(0); else break a; //? <+>
a: for(;;) break a; //? <+>
a: for(;;) continue a; //? <+>
//- undefined_label
a: function b(){ for(;;) break a; } //? <-> @1:32
a: function b(){ for(;;) continue a; } //? <-> @1:35
a: !function b(){ for(;;) break a; } //? <-> @1:33
a: !function b(){ for(;;) continue a; } //? <-> @1:36

a: { break a; } //? <+>
a: { if(0) break a; } //? <+>
a: { for(;;) break a; } //? <+>
/// acorn fails a: { for(;;) continue a; } //? <+>

a: { { break a; } } //? <+>
a: { { if(0) break a; } } //? <+>
a: { { for(;;) break a; } } //? <+>
/// acorn fails a: { { for(;;) continue a; } } //? <+>

a: continue a; //? <-> @1:4 -unsyntatic_continue
a: break b; //? <-> @1:10 -undefined_label

a: b: break a; //? <+>
a: b: if(0) break a; //? <+>
a: b: if(0); else break a; //? <+>
a: b: for(;;) break a; //? <+>
a: b: for(;;) continue a; //? <+>

//- duplicate_label
a: a:; //? <-> @1:4
a: { a:; } //? <-> @1:6
a: b: a:; //? <-> @1:7
a: { b: { a:; } } //? <-> @1:11
a: function b(){ a:; } //? <+>
a: !function b(){ a:; } //? <+>
a: !{b(){ a:; }} //? <+>
a:; a:; //? <+>
a: { b:; b:; } //? <+>
//- undefined_label
a: { b:; { break b; } break a; } //? <-> @1:18
a: { b: { break b; } break a; } //? <+>
a: { !function(){ b:; }; break a; } //? <+>
a: { b:; { !function(){ c:; } } { break b; } break a; } //? <-> @1:41
a: { b: { !function(){ c:; }; break b; } break a; } //? <+>

//- default
a: function b(){} //? <+&>
a: function* b(){} //? <-&> @1:12
a: async function b(){} //? <-> @1:4
a: async function* b(){} //? <-> @1:4
a: b: function c(){} //? <+&>
if(0) a: function b(){} //? <-> @1:10
if(0) a: b: function c(){} //? <-> @1:13
if(0); else a: function b(){} //? <-> @1:16
if(0); else a: b: function c(){} //? <-> @1:19
if(0) { a: function b(){} } //? <+>
if(0); else { a: function b(){} } //? <+>
with(0) a: function b(){} //? <-> @1:12
with(0) a: b: function c(){} //? <-> @1:15
with(0) { a: function b(){} } //? <+>
do a: function b(){} while(0); //? <-> @1:7
do a: b: function c(){} while(0); //? <-> @1:10
do { a: function b(){} } while(0); //? <+>
while(0) a: function b(){} //? <-> @1:13
while(0) a: b: function b(){} //? <-> @1:16
while(0) { a: function b(){} } //? <+>
for(;;) a: function b(){} //? <-> @1:12
for(;;) a: b: function b(){} //? <-> @1:15
for(;;) { a: function b(){} } //? <+>
for(a in {}) b: function c(){} //? <-> @1:17
for(a of []) b: function c(){} //? <-> @1:17

'use strict'; a: function b(){} //? <-> @1:18
a: function b(){} //? <-#> @1:4

!async function() { for await(a of []) b: function c(){} } //? <-> @1:43
