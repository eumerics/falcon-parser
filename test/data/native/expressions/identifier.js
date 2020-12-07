let \u0061wait; // let await; //? <+?a>
\u0061wait = 0; // await = 0; //? <+?>
\u0061wait: ; // await: ; //? <+?>

let yiel\u0064; // let yield; //? <+?>
yiel\u0064 = 0; // yield = 0; //? <+?>
yiel\u0064: ; // yield: ; //? <+?>

'use strict'; ev\u0061l: ; //? <+>
'use strict'; \u0061rguments: ; //? <+>

//- unicode_keyword
\u0069f(true){} // if(true){} //? <-> @1:1
for(;;) \u0062reak; // for(;;) break; //? <-> @1:9
switch(a) { c\u0061se 0: } // switch(a) { case 0: } //? <-> @1:13
//- default
l\u0065t a = 0; //? <-?> @1:1
'use strict'; l\u0065t a = 0; // let a = 0; //? <-?> @1:15
'use strict'; p\u0061ckage: ; // package: //? <-?> @1:15
'use strict'; let yi\u0065ld; // let yield; //? <-?> @1:19

//- contextual_identifier
function* a(){ let yi\u0065ld; } //? <-?> @1:20
function* a(){ yi\u0065ld = 0; } //? <-?> @1:27 -default
function* a(){ yi\u0065ld: ; } //? <-?> @1:16

//- eval_args_in_strict_mode
'use strict'; let ev\u0061l; //? <-?> @1:19
'use strict'; let \u0061rguments; //? <-?> @1:19
