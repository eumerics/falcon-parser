!{ a: 0 }; //? <+>
!{ 'a': 0 }; //? <+>
!{ 123: 0 }; //? <+>
!{ [a]: 0 }; //? <+>
!{ [(a)]: 0 }; //? <+>
!{ a(){} }; //? <+>
!{ 'a'(x){} }; //? <+>
!{ 123(a, b){} }; //? <+>
!{ [a + b](c){} }; //? <+>
!{ [(a)](b){} }; //? <+>
!{ a }; //? <+>
!{ ...a }; //? <+>
!{ *a(b){} }; //? <+>
!{ async a(b){} }; //? <+>
!{ async* a(b){} }; //? <+>
!{ get a(){} }; //? <+>
!{ get 'a'(){} }; //? <+>
!{ get 123(){} }; //? <+>
!{ get [a](){} }; //? <+>
!{ get [(a)](){} }; //? <+>
!{ set a(b){} }; //? <+>
!{ set 'a'(b){} }; //? <+>
!{ set 123(b){} }; //? <+>
!{ set [a](b){} }; //? <+>
!{ set [(a)](b){} }; //? <+>

/// keywords
!{ await: 0 }; //? <+>
!{ yield: 0 }; //? <+>
///
!{ let: 0 }; //? <+>
!{ static: 0 }; //? <+>
!{ implements: 0 }; //? <+>
!{ interface: 0 }; //? <+>
!{ package: 0 }; //? <+>
!{ private: 0 }; //? <+>
!{ protected: 0 }; //? <+>
!{ public: 0 }; //? <+>
///
!{ as: 0 }; //? <+>
!{ async: 0 }; //? <+>
!{ from: 0 }; //? <+>
!{ get: 0 }; //? <+>
!{ of: 0 }; //? <+>
!{ set: 0 }; //? <+>
!{ target: 0 }; //? <+>
///
!{ break: 0 }; //? <+>
!{ case: 0 }; //? <+>
!{ catch: 0 }; //? <+>
!{ class: 0 }; //? <+>
!{ const: 0 }; //? <+>
!{ continue: 0 }; //? <+>
!{ debugger: 0 }; //? <+>
!{ default: 0 }; //? <+>
!{ delete: 0 }; //? <+>
!{ do: 0 }; //? <+>
!{ else: 0 }; //? <+>
!{ enum: 0 }; //? <+>
!{ export: 0 }; //? <+>
!{ extends: 0 }; //? <+>
!{ false: 0 }; //? <+>
!{ finally: 0 }; //? <+>
!{ for: 0 }; //? <+>
!{ function: 0 }; //? <+>
!{ if: 0 }; //? <+>
!{ import: 0 }; //? <+>
!{ in: 0 }; //? <+>
!{ instanceof: 0 }; //? <+>
!{ new: 0 }; //? <+>
!{ null: 0 }; //? <+>
!{ return: 0 }; //? <+>
!{ super: 0 }; //? <+>
!{ switch: 0 }; //? <+>
!{ this: 0 }; //? <+>
!{ throw: 0 }; //? <+>
!{ true: 0 }; //? <+>
!{ try: 0 }; //? <+>
!{ typeof: 0 }; //? <+>
!{ var: 0 }; //? <+>
!{ void: 0 }; //? <+>
!{ while: 0 }; //? <+>
!{ with: 0 }; //? <+>

/// class early errors that are not applicable to object literals
!{ constructor(){}, constructor(){} }; //? <+>
!{ * constructor(){} }; //? <+>
!{ async constructor(){} }; //? <+>
!{ async* constructor(){} }; //? <+>
!{ get constructor(){} }; //? <+>
!{ set constructor(b){} }; //? <+>

//- duplicate_prototype
!{__proto__: [], __proto__: []} //? <-&> @1:18
!{__proto__: [], "__proto__": []} //? <-&> @1:18
!{"__proto__": [], __proto__: []} //? <-&> @1:20
!{__proto__: [], ["__proto__"]: []} //? <+>
!{["__proto__"]: [], __proto__: []} //? <+>
!{"__proto__": [], ["__proto__"]: []} //? <+>
!{["__proto__"]: [], "__proto__": []} //? <+>
!{__proto__: [], get __proto__(){}} //? <+>
!{get __proto__(){}, __proto__: []} //? <+>
!{__proto__: [], set __proto__(a){}} //? <+>
!{set __proto__(a){}, __proto__: []} //? <+>
