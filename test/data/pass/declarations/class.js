let computed = 'computed';
let generator_computed = 'generator_computed';
let async_computed = 'async_computed';
let async_generator_computed = 'async_generator_computed';
let get_computed = 'get_computed';
let set_computed = 'set_computed';
let static_computed = 'static_computed';
let static_generator_computed = 'static_generator_computed';
let static_async_computed = 'static_async_computed';
let static_async_generator_computed = 'static_async_generator_computed';
let static_get_computed = 'static_get_computed';
let static_set_computed = 'static_set_computed';
class Empty {}
class EmptyElement {;}
class Inherited extends Empty {}
class NonEmpty {
   constructor(){}

   regular(){}
   "string"(a){}
   [computed](a, b){}
   1(a, b, c){}

   * generator_regular(a){}
   * "generator_string"(a,b){}
   * [generator_computed](a,b,c){}
   * 2(){}

   async async_regular(a,b){}
   async "async_string"(a,b,c){}
   async [async_computed](){}
   async 3(a){}

   async* async_generator_regular(a,b,c){}
   async* "async_generator_string"(){}
   async* [async_generator_computed](a){}
   async* 4(a,b){}

   get get_regular(){}
   get "get_string"(){}
   get [get_computed](){}
   get 5(){}

   set set_regular(a){}
   set "set_string"(a){}
   set [set_computed](a){}
   set 6(a){}

   static static_regular(a, b, c){}
   static "static_string"(a, b){}
   static [static_computed](a){}
   static 7(){}

   static * static_generator_regular(a){}
   static * "static_generator_string"(a,b){}
   static * [static_generator_computed](a,b,c){}
   static * 8(){}

   static async static_async_regular(a,b){}
   static async "static_async_string"(a,b,c){}
   static async [static_async_computed](){}
   static async 9(a){}

   static async* static_async_generator_regular(a,b,c){}
   static async* "static_async_generator_string"(){}
   static async* [static_async_generator_computed](a){}
   static async* 10(a,b){}

   static get static_get_regular(){}
   static get "static_get_string"(){}
   static get [static_get_computed](){}
   static get 11(){}

   static set static_set_regular(a){}
   static set "static_set_string"(a){}
   static set [static_set_computed](a){}
   static set 12(a){}

   get(){}
   set(){}
   static(){}

   ; // empty element
}
