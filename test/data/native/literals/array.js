!{__proto__: [], __proto__: []} //? <->
!{__proto__: [], "__proto__": []} //? <->
!{"__proto__": [], __proto__: []} //? <->
!{__proto__: [], ["__proto__"]: []} //? <+>
!{["__proto__"]: [], __proto__: []} //? <+>
!{"__proto__": [], ["__proto__"]: []} //? <+>
!{["__proto__"]: [], "__proto__": []} //? <+>
!{__proto__: [], get __proto__(){}} //? <+>
!{get __proto__(){}, __proto__: []} //? <+>
!{__proto__: [], set __proto__(a){}} //? <+>
!{set __proto__(a){}, __proto__: []} //? <+>