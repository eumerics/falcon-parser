let c = 'u', f = 'v', g = 'w', h = 'x', i = {s: 0, t: 1}, o = 'y', r = 'z';
({
   a: 0, "b": 1, 123: 2, [c]: 3,
   d(){}, "e"(x){}, 456(x,y){}, [f + g](z){},
   h, ... i,
   *j(x){}, async k(y){},
   async* l(z){},
   get m(){}, get "n"(){}, get 78(){}, get [o](){},
   set p(x){}, set "q"(y){}, set 90(x){}, set [r](x){},
   await: 1, yield: 2, let: 3, static: 4, implements: 5,
   interface: 6, package: 7, private: 8, protected: 9,
   public: 1, as: 2, async: 3, from: 4, get: 5, of: 6,
   set: 7, target: 8, if: 9, else: 1, for: 2, while: 3
});
