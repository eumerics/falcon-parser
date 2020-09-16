let a, b = {c: null, d:{prop: function(){return 1;}}};
let e = {f: function(){ return {g: 'g'};}};

a?.prop;
b?.c?.prop;
b.c?.prop;
b?.d.prop;
b?.d?.prop;

a?.();
b?.c?.();
b.c?.();
b?.d.prop();
b?.d?.prop();
e.f?.().g.h();
