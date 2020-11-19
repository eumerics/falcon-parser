super; //? <-> @1:1 -standalone_super
super.a; //? <-> @1:1 -misplaced_super_property
super(); //? <-> @1:1 -misplaced_super_call

!{ a(super){} }; //? <-> @1:6 -default
!{ a(b = super){} }; //? <-> @1:10 -standalone_super
!{ a(b = super()){} }; //? <-> @1:10 -misplaced_super_call
!{ a(b = super.c){} }; //? <+>
!{ a(){ super; } }; //? <-> @1:9 -standalone_super
!{ a(){ b = super(); } }; //? <-> @1:13 -misplaced_super_call
!{ a(){ super.c; } }; //? <+>

!function a(super){} //? <-> @1:13 -default
!function a(b = super){} //? <-> @1:17 -standalone_super
!function a(b = super()){} //? <-> @1:17 -misplaced_super_call
!function a(b = super.c){} //? <-> @1:17 -misplaced_super_property
!function a(){ super; } //? <-> @1:16 -standalone_super
!function a(){ b = super(); } //? <-> @1:20 -misplaced_super_call
!function a(){ super.c; } //? <-> @1:16 -misplaced_super_property

function a(super){} //? <-> @1:12 -default
function a(b = super){} //? <-> @1:16 -standalone_super
function a(b = super()){} //? <-> @1:16 -misplaced_super_call
function a(b = super.c){} //? <-> @1:16 -misplaced_super_property
function a(){ super; } //? <-> @1:15 -standalone_super
function a(){ b = super(); } //? <-> @1:19 -misplaced_super_call
function a(){ super.c; } //? <-> @1:15 -misplaced_super_property

super => {}; //? <-> @1:1 -default
(super) => {}; //? <-> @1:2 -default
(a = super) => {}; //? <-> @1:6 -standalone_super
(a = super.b) => {}; //? <-> @1:6 -misplaced_super_property
(a = super()) => {}; //? <-> @1:6 -misplaced_super_call
() => { super; }; //? <-> @1:9 -standalone_super
() => { super.a; }; //? <-> @1:9 -misplaced_super_property
() => { super(); }; //? <-> @1:9 -misplaced_super_call
a => { super; }; //? <-> @1:8 -standalone_super
a => { super.b; }; //? <-> @1:8 -misplaced_super_property
a => { super(); }; //? <-> @1:8 -misplaced_super_call

class a extends b { c(){ !{ d(super){} } } } //? <-> @1:31 -default
class a extends b { c(){ !{ d(e = super){} } } } //? <-> @1:35 -standalone_super
class a extends b { c(){ !{ d(e = super.f){} } } } //? <+>
class a extends b { c(){ !{ d(e = super()){} } } } //? <-> @1:35 -misplaced_super_call
class a extends b { c(){ !{ d(){ super; } } } } //? <-> @1:34 -standalone_super
class a extends b { c(){ !{ d(){ super.e; } } } } //? <+>
class a extends b { c(){ !{ d(){ super(); } } } } //? <-> @1:34 -misplaced_super_call
class a extends b { c(){ !function d(super){} } } //? <-> @1:38 -default
class a extends b { c(){ !function d(e = super){} } } //? <-> @1:42 -standalone_super
class a extends b { c(){ !function d(e = super.f){} } } //? <-> @1:42 -misplaced_super_property
class a extends b { c(){ !function d(e = super()){} } } //? <-> @1:42 -misplaced_super_call
class a extends b { c(){ !function d(){ super; } } } //? <-> @1:41 -standalone_super
class a extends b { c(){ !function d(){ super.e; } } } //? <-> @1:41 -misplaced_super_property
class a extends b { c(){ !function d(){ super(); } } } //? <-> @1:41 -misplaced_super_call
class a extends b { c(){ function d(super){} } } //? <-> @1:37 -default
class a extends b { c(){ function d(e = super){} } } //? <-> @1:41 -standalone_super
class a extends b { c(){ function d(e = super.f){} } } //? <-> @1:41 -misplaced_super_property
class a extends b { c(){ function d(e = super()){} } } //? <-> @1:41 -misplaced_super_call
class a extends b { c(){ function d(){ super; } } } //? <-> @1:40 -standalone_super
class a extends b { c(){ function d(){ super.e; } } } //? <-> @1:40 -misplaced_super_property
class a extends b { c(){ function d(){ super(); } } } //? <-> @1:40 -misplaced_super_call
class a extends b { c(){ super => {} } } //? <-> @1:26 -default
class a extends b { c(){ (super) => {} } } //? <-> @1:27 -default
class a extends b { c(){ (d = super) => {} } } //? <-> @1:31 -standalone_super
class a extends b { c(){ (d = super.e) => {} } } //? <+>
class a extends b { c(){ (d = super()) => {} } } //? <-> @1:31 -misplaced_super_call
class a extends b { c(){ () => { super; } } } //? <-> @1:34 -standalone_super
class a extends b { c(){ () => { super.d; } } } //? <+>
class a extends b { c(){ () => { super(); } } } //? <-> @1:34 -misplaced_super_call
class a extends b { c(){ d => { super; } } } //? <-> @1:33 -standalone_super
class a extends b { c(){ d => { super.e; } } } //? <+>
class a extends b { c(){ d => { super(); } } } //? <-> @1:33 -misplaced_super_call

class a { constructor(b = super()){} } //? <-> @1:27 -misplaced_super_call
class a { constructor(){ super(); } } //? <-> @1:26 -misplaced_super_call

class a { b(){ !{ c(d = super.e){} } } } //? <+>
class b { b(){ !{ c(){ super.d; } } } } //? <+>
class c { b(){ (d = super.e) => {} } } //? <+>
class d { b(){ () => { super.c; } } } //? <+>
class e { b(){ c => { super.d; } } } //? <+>
class f { b(){ super.c; } } //? <+>

class h extends f { constructor(g = super()){} } //? <+>
class i extends f { constructor(){ super(); } } //? <+>
class j extends f { constructor(){ (g = super()) => {} } } //? <+>
class k extends f { constructor(){ () => { super(); } } } //? <+>
class l extends f { constructor(){ g => { super(); } } } //? <+>
