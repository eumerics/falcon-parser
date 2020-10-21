a: break a; //? <+>
a: if(0) break a; //? <+>
a: if(0); else break a; //? <+>
a: for(;;) break a; //? <+>
a: for(;;) continue a; //? <+>
a: function b(){ for(;;) break a; } //? <->
a: function b(){ for(;;) continue a; } //? <->
a: !function b(){ for(;;) break a; } //? <->
a: !function b(){ for(;;) continue a; } //? <->

a: { break a; } //? <+>
a: { if(0) break a; } //? <+>
a: { for(;;) break a; } //? <+>
/// acorn fails a: { for(;;) continue a; } //? <+>

a: { { break a; } } //? <+>
a: { { if(0) break a; } } //? <+>
a: { { for(;;) break a; } } //? <+>
/// acorn fails a: { { for(;;) continue a; } } //? <+>

a: continue a; //? <->
a: break b; //? <->

a: b: break a; //? <+>
a: b: if(0) break a; //? <+>
a: b: if(0); else break a; //? <+>
a: b: for(;;) break a; //? <+>
a: b: for(;;) continue a; //? <+>

///
a: a:; //? <->
a: { a:; } //? <->
a: b: a:; //? <->
a: { b: { a:; } } //? <->
a: function b(){ a:; } //? <+>
a: !function b(){ a:; } //? <+>
a: !{b(){ a:; }} //? <+>
a:; a:; //? <+>
a: { b:; b:; } //? <+>
a: { b:; { break b; } break a; } //? <->
a: { b: { break b; } break a; } //? <+>
a: { !function(){ b:; }; break a; } //? <+>
a: { b:; { !function(){ c:; } } { break b; } break a; } //? <->
a: { b: { !function(){ c:; }; break b; } break a; } //? <+>

a: function b(){} //? <+>
a: b: function c(){} //? <+>
if(0) a: function b(){} //? <->
if(0) a: b: function c(){} //? <->
if(0); else a: function b(){} //? <->
if(0); else a: b: function c(){} //? <->
if(0) { a: function b(){} } //? <+>
if(0); else { a: function b(){} } //? <+>
with(0) a: function b(){} //? <->
with(0) a: b: function c(){} //? <->
with(0) { a: function b(){} } //? <+>
do a: function b(){} while(0); //? <->
do a: b: function c(){} while(0); //? <->
do { a: function b(){} } while(0); //? <+>
while(0) a: function b(){} //? <->
while(0) a: b: function b(){} //? <->
while(0) { a: function b(){} } //? <+>
for(;;) a: function b(){} //? <->
for(;;) a: b: function b(){} //? <->
for(;;) { a: function b(){} } //? <+>
