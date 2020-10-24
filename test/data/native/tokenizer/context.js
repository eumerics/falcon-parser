!{} / 1; //? <+>
!function(){} / 1; //? <+>
!class{} / 1; //? <+>
function a(){} /./; //? <+>
class a {} /./; //? <+>

a.in / 1; //? <+>

await / 1; //? <+>
yield / 1; //? <+>
let / 1; //? <+>
of / 1; //? <+>

!function*(){ yield /./; } //? <+>
!async function(){ await /./; } //? <+>
for(of of []); //? <+>
for(of of /./); //? <+>

if(0) /./; //? <+>
for(;;) /./; //? <+>
while(0) /./; //? <+>

/// test parenthesis stack exhaustion
if(0) /./; (0) /./; //? <->
for(;;) /./; (0) /./; //? <->
while(0) /./; (0) /./; //? <->

if((0)) /./; //? <+>
for((0);;) /./; //? <+>
while((0)) /./; //? <+>

/// test parenthesis stack push and pop
if(!function(){ if(0) /./; }) /./; //? <+>
for(!function(){ if(0) /./; };;) /./; //? <+>
while(!function(){ if(0) /./; }) /./; //? <+>
