let a, a; //<>

// VarDeclaredNames
{ var a; } let a; //<>
var a; let a; //<>
if(0){ var a; } let a; //<>
if(0); else{ var a; } let a; //<>
do{ var a; } while(0); let a; //<>
while(0){ var a; } let a; //<>
for(;;){ var a; } let a; //<>
for(var a;;){} let a; //<>
for(var a;;){ var b; } let b; //<>
for(let a;;){ var b; } let b; //<>
for(a in {}){ var b; } let b; //<>
for(var a in {}){} let a; //<>
for(var a in {}){ var b; } let b; //<>
for(let a in {}){ var b; } let b; //<>
for(a of []){ var b; } let b; //<>
for(var a of []){} let a; //<>
for(var a of []){ var b; } let b; //<>
for(let a of []){ var b; } let b; //<>
async function a(){ for await(a of []){ var b; } let b; } //<>
async function a(){ for await(var a of []){} let a; } //<>
async function a(){ for await(var a of []){ var b; } let b; } //<>
async function a(){ for await(let a of []){ var b; } let b; } //<>
switch(a){ case 0: { var b; } } let b; //<>
switch(a){ case 0: var b; } let b; //<>
switch(a){ default: { var b; } } let b; //<>
switch(a){ default: var b; } let b; //<>
with(a){ var a; } let a; //<>
a: var b; let b; //<>
a: { var b; } let b; //<>
a: function b(){} let b; //<>
try{ var a; } let a; //<>
try{} catch{ var a; } let a; //<>
try{} finally{ var a; } let a; //<>
function a(){} let a; //<>

{ function a(){} var a; } //<>
{ function a(){} function a(){} } //<>

try{} catch([a, a]){} //<>
try{} catch(a){ let a; } //<>
try{} catch([a]){ var a; } //<>
try{} catch([a]){ let a; } //<>
let a; let a; //<>
function a(){} let a; //<>
class a{} let a; //<>

let a; var a; //<>
let a; for(var a;;); //<>
for(let a;;) { var a; } //<>
let a; function a(){} //<>
let a; {var a;} //<>
let a; {for(var a;;);} //<>
{for(var a;;);} let a; //<>
{ var a; { var b; }} let b; //<>
{ var a; { for(var b;;); }} let b; //<>
{ let a; { let b; { var a; }}} //<>
{ let a; { let b; { for(var b;;); }}} //<>

for(let a in {}) { var a; } //<>
for(let a of []) { var a; } //<>

'use strict'; function a(b, b) {} //<>
