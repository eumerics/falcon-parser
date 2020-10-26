/// [NOTE] labeled functions are not allowed in strict mode
/// function at the top level of script
function a(){} var a; //? <+>
function a(){} let a; //? <->
function a(){} function a(){} //? <+>
function a(){} b: function a(){} //? <+&>
b: function a(){} var a; //? <+&>
b: function a(){} let a; //? <-&>
b: function a(){} function a(){} //? <+&>
b: function a(){} c: function a(){} //? <+&>
'use strict'; function a(){} var a; //? <+^>
'use strict'; function a(){} let a; //? <-^>
'use strict'; function a(){} function a(){} //? <+>
'use strict'; function a(){} b: function a(){} //? <-^>
/// function at the top level of module
function a(){} var a; //? <-#>
function a(){} let a; //? <-#>
function a(){} function a(){} //? <-#>
function a(){} b: function a(){} //? <-#>
/// function at the top level of function
!function(){ function a(){} var a; } //? <+>
!function(){ function a(){} let a; } //? <->
!function(){ function a(){} function a(){} } //? <+>
!function(){ function a(){} b: function a(){} } //? <+>
!function(){ 'use strict'; function a(){} var a; } //? <+>
!function(){ 'use strict'; function a(){} let a; } //? <->
!function(){ 'use strict'; function a(){} function a(){} } //? <+>
!function(){ 'use strict'; function a(){} b: function a(){} } //? <-^>
/// annex modifications of functions in block statements
{ function a(){} var a; } //? <-&>
{ function a(){} let a; } //? <-&>
{ function a(){} function a(){} } //? <+&>
{ function a(){} b: function a(){} } //? <+&>
'use strict'; { var a; function a(){} } //? <-&>
'use strict'; { let a; function a(){} } //? <-&>
'use strict'; { function a(){} function a(){} } //? <-&>
'use strict'; { function a(){} b: function a(){} } //? <-^>
/// annex modifications of functions in switch statements
switch(0){ default: function a(){} var a; } //? <-&>
switch(0){ default: function a(){} let a; } //? <-&>
switch(0){ default: function a(){} function a(){} } //? <+&>
switch(0){ default: function a(){} b: function a(){} }//? <+&>
switch(0){ case 0: function a(){} case 1: function a(){} } //? <+&>
'use strict'; switch(0){ default: function a(){} var a; } //? <->
'use strict'; switch(0){ default: function a(){} let a; } //? <->
'use strict'; switch(0){ default: function a(){} function a(){} } //? <->
'use strict'; switch(0){ default: function a(){} b: function a(){} }//? <-^>
'use strict'; switch(0){ case 0: function a(){} case 1: function a(){} } //? <->
