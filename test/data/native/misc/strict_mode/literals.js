!class { 001(){} }; //? <-> @1:10
'use strict'; '\0'; //? <+>
//- annex_numeral
'use strict'; 001; //? <-> @1:15
'use strict'; 08; //? <-> @1:15
'use strict'; 09; //? <-> @1:15
'use strict'; 018; //? <-> @1:15
'use strict'; !{ 001(){} }; //? <-> @1:18
'use strict'; !{ 08(){} }; //? <-> @1:18
'use strict'; !{ 09(){} }; //? <-> @1:18
!class { 001(){} }; //? <-> @1:10
!class { 08(){} }; //? <-> @1:10
!class { 09(){} }; //? <-> @1:10
/// look back strict mode is not imposed on property names
!{ 001(){ 'use strict'; } }; //? <+>
!{ 08(){ 'use strict'; } }; //? <+>
!{ 09(){ 'use strict'; } }; //? <+>
