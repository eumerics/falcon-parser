/// declarative for statement
/// [NOTE] let a; cannot be a for body
for(var a;;) var a; //? <+>
for(var a;;) let a; //? <->
for(let a;;) var a; //? <->
for(let a;;) let a; //? <->
for(var a;;) { var a; } //? <+>
for(var a;;) { let a; } //? <+>
for(let a;;) { var a; } //? <->
for(let a;;) { let a; } //? <+>
///
for(var a;;); var a; //? <+>
for(var a;;); let a; //? <->
for(let a;;); var a; //? <+>
for(let a;;); let a; //? <+>
for(var a;;); { var a; } //? <+>
for(var a;;); { let a; } //? <+>
for(let a;;); { var a; } //? <+>
for(let a;;); { let a; } //? <+>
{ for(var a;;); } var a; //? <+>
{ for(var a;;); } let a; //? <->
{ for(let a;;); } var a; //? <+>
{ for(let a;;); } let a; //? <+>

/// declarative for-in statement
for(var a in {}) var a; //? <+^>
for(var a in {}) let a; //? <-^>
for(let a in {}) var a; //? <-^>
for(let a in {}) let a; //? <-^>
for(var a in {}) { var a; } //? <+^>
for(var a in {}) { let a; } //? <+^>
for(let a in {}) { var a; } //? <-^>
for(let a in {}) { let a; } //? <+^>
///
for(var a in {}); var a; //? <+^>
for(var a in {}); let a; //? <-^>
for(let a in {}); var a; //? <+^>
for(let a in {}); let a; //? <+^>
for(var a in {}); { var a; } //? <+^>
for(var a in {}); { let a; } //? <+^>
for(let a in {}); { var a; } //? <+^>
for(let a in {}); { let a; } //? <+^>
{ for(var a in {}); } var a; //? <+^>
{ for(var a in {}); } let a; //? <-^>
{ for(let a in {}); } var a; //? <+^>
{ for(let a in {}); } let a; //? <+^>

/// declarative for-in statement
for(var a of []) var a; //? <+^>
for(var a of []) let a; //? <-^>
for(let a of []) var a; //? <-^>
for(let a of []) let a; //? <-^>
for(var a of []) { var a; } //? <+^>
for(var a of []) { let a; } //? <+^>
for(let a of []) { var a; } //? <-^>
for(let a of []) { let a; } //? <+^>
///
for(var a of []); var a; //? <+^>
for(var a of []); let a; //? <-^>
for(let a of []); var a; //? <+^>
for(let a of []); let a; //? <+^>
for(var a of []); { var a; } //? <+^>
for(var a of []); { let a; } //? <+^>
for(let a of []); { var a; } //? <+^>
for(let a of []); { let a; } //? <+^>
{ for(var a of []); } var a; //? <+^>
{ for(var a of []); } let a; //? <-^>
{ for(let a of []); } var a; //? <+^>
{ for(let a of []); } let a; //? <+^>

/// declarative statements
!async function(){ var a; for await(let a of []){} } //? <+>
!async function(){ let a; for await(var a of []){} } //? <->

// declarative catch
try{} catch(a){}; var a; //? <+>
try{} catch(a){}; let a; //? <+>
try{} catch(a){ var a; } //? <+&>
try{} catch(a){ let a; } //? <->
try{} catch(a){ { let a; } } //? <+>
try{} catch([a]){}; var a; //? <+>
try{} catch([a]){}; let a; //? <+>
try{} catch([a]){ var a; } //? <->
try{} catch([a]){ let a; } //? <->
try{} catch([a]){ { let a; } } //? <+>
try{} catch([a, a]){}; //? <->
try{} catch([a, ...a]){}; //? <->

function a(){} let a; //? <->
class a{} let a; //? <->
