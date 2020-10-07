let a;
function f(){ return [1, 2]; }
function g(){ return f; }

a.b, a[c], a`d`;
a.b.e, a.b[c], a.b`d`;
a[c].e, a[c][f], a[c]`d`;
a`d`.e, a`d`[f], a`d``g`;
````;

a.await, a.yield, a.let, a.static, a.implements,
a.interface, a.package, a.private, a.protected,
a.public, a.as, a.async, a.from, a.get, a.of,
a.set, a.target, a.if, a.else, a.for, a.while

new f; new f();
new new f; new new f()();

{
   ({a(){ new.target; }});
   ({get a(){ new.target; }});
   ({set a(b){ new.target; }});
   function h(){ new.target; }
   class x {
      constructor(){ new.target; }
      a(){ new.target; }
      get b(){ new.target; }
      set b(x){ new.target; }
   }
}

{
   ({a(b = new.target){}});
   ({set a(b = new.target){}});
   function h(b = new.target){}
   class x {
      constructor(a = new.target){}
      a(b = new.target){}
      set b(c = new.target){}
   }
}
