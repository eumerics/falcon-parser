if(0) if(0); else; //? <+>
if(true) function a(){} //? <+>
if(false); else function a(){} //? <+>
if(true) function a(){ function* b(){} } //? <+>

//- default
'use strict'; if(true) function a(){} //? <-> @1:24
'use strict'; if(true); else function a(){} //? <-> @1:30
