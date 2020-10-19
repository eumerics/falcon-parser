{ var a, a; } //<>
{ var a; var a; } //<>
{ let a; { let a; } } //<>
{ let a; for(let a;;); } //<>
{ for(let a;;); let a; } //<>
{ var a; for(let a;;); } //<>

// VarDeclaredNames
{ () => { var a; }; let a; } //<>
{ !function a(){}; let a; } //<>
{ !class a{}; let a; } //<>
//{ { a: function b(){} } let b; } //<>
try{} catch(a){ var a; } //<>
{ { let a; } let a; } //<>
//{ { function a(){} } let a; } //<>
{ { class a {} } let a; } //<>
//function a(){} function a(){} //<>
//let a; if(0) function a(){} //<>
//var a; if(0) function a(){} //<>

//{ let a; {function a(){}} } //<>
//{ { var a; { function b(){} }} let b; } //<>
//{ { let a; { let b; { function a(){} }}} } //<>

function a(b, b) {} //<>
function a(b) { var b; } //<>
function a([b]) { var b; } //<>
function a() { 'use strict'; var b; var b; } //<>
function a() { 'use strict'; for(var a, a;;); } //<>
