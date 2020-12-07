for(;;); //? <+>
for(;;){} //? <+>
for(1;;); //? <+>
for(;2;); //? <+>
for(;;3); //? <+>
for(1;2;); //? <+>
for(;2;3); //? <+>
for(1;;3); //? <+>
for(1;2;3); //? <+>

for(a;;); //? <+>
for(var a;;); //? <+>
for(let a;;); //? <+>
for(const a;;); //? <-> @1:12 -missing_const_initializer
for(a = 0;;); //? <+>
for(var a = 0;;); //? <+>
for(let a = 0;;); //? <+>
for(const a = 0;;); //? <+>

for(var [a] = [];;); //? <+>
for(let [a] = [];;); //? <+>
for(const [a] = [];;); //? <+>
for(l\u0065t[a];;); //? <+>

for(; a in {};); //? <+>
for(;; a in {}); //? <+>
for(var a = (b in {});;); //? <+>
for(var a = [b in {}];;); //? <+>
for(var [a] = [b in {}];;); //? <+>
for(var [a = b in {}] = [1];;); //? <+>

for(b in {}); //? <+>
for(var b in {}); //? <+>
for(let b in {}); //? <+>
for(const b in {}); //? <+>

for(var [a] in {}); //? <+>
for(let [a] in {}); //? <+>
for(const [a] in {}); //? <+>

for(c of []); //? <+>
for(var c of []); //? <+>
for(let c of []); //? <+>
for(const c of []); //? <+>

for(var [a] of []); //? <+>
for(let [a] of []); //? <+>
for(const [a] of []); //? <+>

!async function(){ for await(a of []); } //? <+>
!async function(){ for await(var a of []); } //? <+>
!async function(){ for await(let a of []); } //? <+>
!async function(){ for await(const a of []); } //? <+>
!async function(){ for await(let [a, b = [c = 3], d] of {}); } //? <+>
!async function(){ for await(let {a, b: [c = 3], d} of {}); } //? <+>

/// let as keyword or identifier?
for(let.a;;); //? <+>
for(let/a;;); //? <+>
for(let in;;); //? <-> @1:11
for(let of;;); //? <+>
for(let[a];;); //? <-> @1:11
///
for(let in {}); //? <+>
for(let.a in {}); //? <+>
for(let() in {}); //? <-> @1:5 -invalid_for_assignment
for(let().a in {}); //? <+>
for(let[0] in {}); //? <-> @1:9
for(let[a] in {}); //? <+>
//- for_of_begins_with_let
for(let of []); //? <-> @1:12 -expect ;
for(let.a of []); //? <-> @1:5
for(let() of []); //? <-> @1:5
for(let().a of []); //? <-> @1:5
for(let[0] of []); //? <-> @1:9 -default
for(let[a] of []); //? <+>

/// invalid initialization
//- initializer_in_for
for(var a = 1 in []); //? <+&>
'use strict'; for(var a = 1 in {}); //? <-> @1:27
for(let a = 1 in {}); //? <-> @1:13
for(const a = 1 in {}); //? <-> @1:15
for(var [a, b] = [1, 2] in []); //? <-> @1:25 -expect ;
for(let [a, b] = [1, 2] in []); //? <-> @1:25 -expect ;
for(var a, b in {}); //? <-> @1:14 -expect ;
for(let a, b in {}); //? <-> @1:14 -expect ;
for(const a = 1, b = 2 in {}); //? <-> @1:24 -expect ;
for(a + b in {}); //? <-> @1:11 -expect ;
for(a + b of []); //? <-> @1:11 -expect ;
for(let [a.b] in {}); //? <-> @1:11 -default
for(a = 1 in {}); //? <-> @1:11 -expect ;

for(a, b = 2, [c] = [3], {d} = {d: 4};;); //? <+>
for([a, b = [c = 3], d];;); //? <+>

for(let [a, b = [c = 3], d] in {}); //? <+>
for(let [a, b = [c = 3], d] of []); //? <+>
for(let {a, b: [c = 3], d} in {}); //? <+>
for(let {a, b: [c = 3], d} of {}); //? <+>

/// exclude "in" keyword in initialize expression
//- default
for(a in {};;); //? <-> @1:12
for(a = x in {};;); //? <-&> @1:11 -expect ;
for(a=>a in b;;); //? <-> @1:10 -expect ;
for(var a = x in {};;); //? <-&> @1:20 -default
for(let a = x in {};;); //? <-> @1:13 -initializer_in_for
for(const a = x in {};;); //? <-> @1:15 -initializer_in_for
for(var [a];;); //? <-> @1:12 -missing_binding_initializer
for(let [a];;); //? <-> @1:12 -missing_binding_initializer
for(const [a];;); //? <-> @1:14 -missing_binding_initializer
for(var [a] = x in {};;); //? <-> @1:17 -expect ;
for(let [a] = x in {};;); //? <-> @1:17 -expect ;
for(const [a] = x in {};;); //? <-> @1:19 -expect ;

/// incomplete for statements
//- default
for(;) //? <-> @1:6
for(;0) //? <-> @1:7
for(;;) //? <-> @1:9
for(a in) //? <-> @1:9
for(a of) //? <-> @1:9
for(a in {}) //? <-> @1:14
for(a of []) //? <-> @1:14
//- unexpected_for_await
for await(;;); //? <-> @1:5
for await(a in {}); //? <-> @1:5
for await(a of []); //? <-> @1:5
///
!async function(){ for await(;;); }; //? <-> @1:30 -default
!async function(){ for await(a in {}); }; //? <-> @1:32 -expecting_of

//- let_in_lexical
for(let let;;); //? <-> @1:9
for(let let = 0;;); //? <-> @1:9
for(let let in {}); //? <-> @1:9
for(let let of []); //? <-> @1:9
for(let [let] in {}); //? <-> @1:10
for(let {let} of []); //? <-> @1:10
for(let [...let] in {}); //? <-> @1:13
for(let {...let} of []); //? <-> @1:13
///
for(const let;;); //? <-> @1:11
for(const let = 0;;); //? <-> @1:11
for(const let in {}); //? <-> @1:11
for(const let of []); //? <-> @1:11
for(const [let] in {}); //? <-> @1:12
for(const {let} of []); //? <-> @1:12
for(const [...let] in {}); //? <-> @1:15
for(const {...let} of []); //? <-> @1:15
