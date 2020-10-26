'use strict'; var a; var a; //? <+>
'use strict'; for(var a, a;;); //? <+>

var a, a; //? <+>
let a, a; //? <->

/// duplicate bindings
var a; var a; //? <+>
var a; let a; //? <->
let a; var a; //? <-^>
let a; let a; //? <->
/// hoisting of var bindings
var a; { var a; } //? <+^>
var a; { let a; } //? <+>
let a; { var a; } //? <->
let a; { let a; } //? <+>
{ var a; } var a; //? <+^>
{ var a; } let a; //? <-^>
{ let a; } var a; //? <+^>
{ let a; } let a; //? <+^>

/// hoisting of deeply nested var bindings
let a; {{ var a; }} //? <->
{{ var a; }} let a; //? <-^>
/// hoisting at all levels of nesting
{ let a; { var a; }} //? <->
{{ var a; } let a; } //? <-^>

/// hoisting through statements
let a; if(0) { var a; } //? <->
let a; if(0); else { var a; } //? <->
let a; do { var a; } while(0); //? <->
let a; while(0){ var a; } //? <->
let a; for(;;){ var a; } //? <->
let a; switch(0){ case 0: var a; } //? <->
let a; switch(0){ default: var a; } //? <->
let a; switch(0){ case 0: { var a; } } //? <->
let a; switch(0){ default: { var a; } } //? <->
let a; with({}){ var a; } //? <->
let a; b: var a; //? <->
let a; b: { var a; } //? <->
let a; try{} catch{ var a; } //? <->
let a; try{} finally{ var a; } //? <->
///   reversed
if(0) { var a; } let a; //? <-^>
if(0); else { var a; } let a; //? <-^>
do { var a; } while(0); let a; //? <-^>
while(0){ var a; } let a; //? <-^>
for(;;){ var a; } let a; //? <-^>
switch(0){ case 0: var a; } let a; //? <-^>
switch(0){ default: var a; } let a; //? <-^>
switch(0){ case 0: { var a; } } let a; //? <-^>
switch(0){ default: { var a; } } let a; //? <-^>
with({}){ var a; } let a; //? <-^>
b: var a; let a; //? <-^>
b: { var a; } let a; //? <-^>
try{} catch{ var a; } let a; //? <-^>
try{} finally{ var a; } let a; //? <-^>
///   scoped
{ let a; if(0) { var a; } } //? <-^>
{ let a; if(0); else { var a; } } //? <-^>
{ let a; do { var a; } while(0); } //? <-^>
{ let a; while(0){ var a; } } //? <-^>
{ let a; for(;;){ var a; } } //? <-^>
{ let a; switch(0){ case 0: var a; } } //? <-^>
{ let a; switch(0){ default: var a; } } //? <-^>
{ let a; switch(0){ case 0: { var a; } } } //? <-^>
{ let a; switch(0){ default: { var a; } } } //? <-^>
{ let a; with({}){ var a; } } //? <-^>
{ let a; b: var a; } //? <-^>
{ let a; b: { var a; } } //? <-^>
{ let a; try{} catch{ var a; } } //? <-^>
{ let a; try{} finally{ var a; } } //? <-^>
///   scoped-reversed
{ if(0) { var a; } let a; } //? <-^>
{ if(0); else { var a; } let a; } //? <-^>
{ do { var a; } while(0); let a; } //? <-^>
{ while(0){ var a; } let a; } //? <-^>
{ for(;;){ var a; } let a; } //? <-^>
{ switch(0){ case 0: var a; } let a; } //? <-^>
{ switch(0){ default: var a; } let a; } //? <-^>
{ switch(0){ case 0: { var a; } } let a; } //? <-^>
{ switch(0){ default: { var a; } } let a; } //? <-^>
{ with({}){ var a; } let a; } //? <-^>
{ b: var a; let a; } //? <-^>
{ b: { var a; } let a; } //? <-^>
{ try{} catch{ var a; } let a; } //? <-^>
{ try{} finally{ var a; } let a; } //? <-^>
///   deeply-nested
let a; { if(0) { var a; } } //? <-^>
let a; { if(0); else { var a; } } //? <-^>
let a; { do { var a; } while(0); } //? <-^>
let a; { while(0){ var a; } } //? <-^>
let a; { for(;;){ var a; } } //? <-^>
let a; { switch(0){ case 0: var a; } } //? <-^>
let a; { switch(0){ default: var a; } } //? <-^>
let a; { switch(0){ case 0: { var a; } } } //? <-^>
let a; { switch(0){ default: { var a; } } } //? <-^>
let a; { with({}){ var a; } } //? <-^>
let a; { b: var a; } //? <-^>
let a; { b: { var a; } } //? <-^>
let a; { try{} catch{ var a; } } //? <-^>
let a; { try{} finally{ var a; } } //? <-^>
///   deeply-nested-reversed
{ if(0) { var a; } } let a; //? <-^>
{ if(0); else { var a; } } let a; //? <-^>
{ do { var a; } while(0); } let a; //? <-^>
{ while(0){ var a; } } let a; //? <-^>
{ for(;;){ var a; } } let a; //? <-^>
{ switch(0){ case 0: var a; } } let a; //? <-^>
{ switch(0){ default: var a; } } let a; //? <-^>
{ switch(0){ case 0: { var a; } } } let a; //? <-^>
{ switch(0){ default: { var a; } } } let a; //? <-^>
{ with({}){ var a; } } let a; //? <-^>
{ b: var a; } let a; //? <-^>
{ b: { var a; } } let a; //? <-^>
{ try{} catch{ var a; } } let a; //? <-^>
{ try{} finally{ var a; } } let a; //? <-^>

/// masking let
let a; if(0) { let a; } //? <+^>
let a; if(0); else { let a; } //? <+^>
let a; do { let a; } while(0); //? <+^>
let a; while(0){ let a; } //? <+^>
let a; for(;;){ let a; } //? <+^>
let a; switch(0){ case 0: let a; } //? <+>
let a; switch(0){ default: let a; } //? <+>
let a; switch(0){ case 0: { let a; } } //? <+^>
let a; switch(0){ default: { let a; } } //? <+^>
let a; with({}){ let a; } //? <+^>
let a; b: let a; //? <->
let a; b: { let a; } //? <+^>
let a; try{} catch{ let a; } //? <+^>
let a; try{} finally{ let a; } //? <+^>

/// switch cases
switch(0){ case 0: var a; case 1: var a; } //? <+>
switch(0){ case 0: var a; case 1: let a; } //? <->
switch(0){ case 0: let a; case 1: var a; } //? <->
switch(0){ case 0: let a; case 1: let a; } //? <->
switch(0){ case 0: var a; default: var a; } //? <+>
switch(0){ case 0: var a; default: let a; } //? <->
switch(0){ case 0: let a; default: var a; } //? <->
switch(0){ case 0: let a; default: let a; } //? <->

/// labeled statements
var a; b: var a; //? <+>
var a; b: let a; //? <->

/// declarative statements
var a; for(let a;;){} //? <+>
var a; for(let a in {}){} //? <+>
var a; for(let a of []){} //? <+>
!async function(){ var a; for await(let a of []){} } //? <+>
///
let a; for(var a;;){} //? <->
let a; for(var a in {}){} //? <->
let a; for(var a of []){} //? <->
for(let a;;) { var a; } //? <->
for(let a in {}) { var a; } //? <->
for(let a of []) { var a; } //? <->
!async function(){ let a; for await(var a of []){} } //? <->

try{} catch([a, a]){} //? <->
try{} catch(a){ let a; } //? <->
try{} catch([a]){ var a; } //? <->
try{} catch([a]){ let a; } //? <->
function a(){} let a; //? <->
class a{} let a; //? <->

for(let a;;) { var a; } //? <->
let a; {for(var a;;);} //? <->
{for(var a;;);} let a; //? <->
{ var a; { for(var b;;); }} let b; //? <->
{ let a; { let b; { for(var b;;); }}} //? <->


'use strict'; function a(b, b) {} //? <->

let a; for(let a;;); //? <+>
for(let a;;); let a; //? <+>
var a; for(let a;;); //? <+>

// VarDeclaredNames
() => { var a; }; let a; //? <+>
!function a(){}; let a; //? <+>
!class a{}; let a; //? <+>
//{ a: function b(){} } let b; //? <+>
try{} catch(a){ var a; } //? <+>
{ let a; } let a; //? <+>
//{ function a(){} } let a; //? <+>
{ class a {} } let a; //? <+>
//function a(){} function a(){} //? <+>
//let a; if(0) function a(){} //? <+>
//var a; if(0) function a(){} //? <+>

//let a; {function a(){}} //? <+>
//{ var a; { function b(){} }} let b; //? <+>
//{ let a; { let b; { function a(){} }}} //? <+>
