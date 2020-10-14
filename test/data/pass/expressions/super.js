!{ a(b = super.c){} }; //<>
!{ a(){ super.c; } }; //<>
class a { b(){ !{ c(d = super.e){} } } } //<>
class b { b(){ !{ c(){ super.d; } } } } //<>
class c { b(){ (d = super.e) => {} } } //<>
class d { b(){ () => { super.c; } } } //<>
class e { b(){ c => { super.d; } } } //<>
class f { b(){ super.c; } } //<>

class h extends f { constructor(g = super()){} } //<>
class i extends f { constructor(){ super(); } } //<>
class j extends f { constructor(){ (g = super()) => {} } } //<>
class k extends f { constructor(){ () => { super(); } } } //<>
class l extends f { constructor(){ g => { super(); } } } //<>
