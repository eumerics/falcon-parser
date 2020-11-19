a.b; //? <+>
a[b]; //? <+>
a`b`; //? <+>
a.b.c; //? <+>
a.b[c]; //? <+>
a.b`c`; //? <+>
a[b].c; //? <+>
a[b][c]; //? <+>
a[b]`c`; //? <+>
a`b`.c; //? <+>
a`b`[c]; //? <+>
a`b``c`; //? <+>
````; //? <+>

a.await; //? <+>
a.yield; //? <+>
a.let; //? <+>
a.static; //? <+>
a.implements; //? <+>
a.interface; //? <+>
a.package; //? <+>
a.private; //? <+>
a.protected; //? <+>
a.public; //? <+>
a.as; //? <+>
a.async; //? <+>
a.from; //? <+>
a.get; //? <+>
a.of; //? <+>
a.set; //? <+>
a.target; //? <+>
a.if; //? <+>
a.else; //? <+>
a.for; //? <+>
a.while

new a; //? <+>
new a(); //? <+>
new new a; //? <+>
new new a()(); //? <+>

super; //? <-> @1:1 -standalone_super
import.meta; //? <-> @1:1 -import_in_non_module
new.target; //? <-> @1:1 -new_meta

!{a(){ new.target; }}; //? <+>
!{get a(){ new.target; }}; //? <+>
!{set a(b){ new.target; }}; //? <+>
!{a(b = new.target){}}; //? <+>
!{set a(b = new.target){}}; //? <+>
!function(){ new.target; } //? <+>
!function(a = new.target){} //? <+>
!class{ constructor(){ new.target; } } //? <+>
!class{ a(){ new.target; } } //? <+>
!class{ get a(){ new.target; } } //? <+>
!class{ set a(b){ new.target; } } //? <+>
!class{ constructor(a = new.target){} }; //? <+>
!class{ a(b = new.target){} }; //? <+>
!class{ set b(c = new.target){} }; //? <+>

function a(){ new.target; } //? <+>
function a(b = new.target){} //? <+>
class a { constructor(){ new.target; } } //? <+>
class a { b(){ new.target; } } //? <+>
class a { get b(){ new.target; } } //? <+>
class a { set b(c){ new.target; } } //? <+>
class a { constructor(a = new.target){} }; //? <+>
class a { a(b = new.target){} }; //? <+>
class a { set b(c = new.target){} }; //? <+>
