super; //<>
super.a; //<>
super(); //<>

!{ a(super){} }; //<>
!{ a(b = super){} }; //<>
!{ a(b = super()){} }; //<>
!{ a(){ super; } }; //<>
!{ a(){ b = super(); } }; //<>
!function a(super){} //<>
!function a(b = super){} //<>
!function a(b = super.c){} //<>
!function a(b = super()){} //<>
!function a(){ super; } //<>
!function a(){ super.b; } //<>
!function a(){ super(); } //<>
function a(super){} //<>
function a(b = super){} //<>
function a(b = super.c){} //<>
function a(b = super()){} //<>
function a(){ super; } //<>
function a(){ super.b; } //<>
function a(){ super(); } //<>
super => {}; //<>
(super) => {}; //<>
(a = super) => {}; //<>
(a = super.b) => {}; //<>
(a = super()) => {}; //<>
() => { super; }; //<>
() => { super.a; }; //<>
() => { super(); }; //<>
a => { super; }; //<>
a => { super.b; }; //<>
a => { super(); }; //<>

class a extends b { c(){ !{ d(super){} } } } //<>
class a extends b { c(){ !{ d(e = super){} } } } //<>
class a extends b { c(){ !{ d(e = super()){} } } } //<>
class a extends b { c(){ !{ d(){ super; } } } } //<>
class a extends b { c(){ !{ d(){ e = super(); } } } } //<>
class a extends b { c(){ !function d(super){} } } //<>
class a extends b { c(){ !function d(e = super){} } } //<>
class a extends b { c(){ !function d(e = super.f){} } } //<>
class a extends b { c(){ !function d(e = super()){} } } //<>
class a extends b { c(){ !function d(){ super; } } } //<>
class a extends b { c(){ !function d(){ super.e; } } } //<>
class a extends b { c(){ !function d(){ super(); } } } //<>
class a extends b { c(){ function d(super){} } } //<>
class a extends b { c(){ function d(e = super){} } } //<>
class a extends b { c(){ function d(e = super.f){} } } //<>
class a extends b { c(){ function d(e = super()){} } } //<>
class a extends b { c(){ function d(){ super; } } } //<>
class a extends b { c(){ function d(){ super.e; } } } //<>
class a extends b { c(){ function d(){ super(); } } } //<>
class a extends b { c(){ super => {} } } //<>
class a extends b { c(){ (super) => {} } } //<>
class a extends b { c(){ (d = super) => {} } } //<>
class a extends b { c(){ (d = super()) => {} } } //<>
class a extends b { c(){ () => { super; } } } //<>
class a extends b { c(){ () => { super(); } } } //<>
class a extends b { c(){ d => { super; } } } //<>
class a extends b { c(){ d => { super(); } } } //<>

class a { constructor(b = super()){} } //<>
class a { constructor(){ super(); } } //<>
