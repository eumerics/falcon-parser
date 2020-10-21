this++; //? <->
this--; //? <->
++this; //? <->
--this; //? <->
++a; //? <+>
++null; //? <->
++true; //? <->
++false; //? <->
++0; //? <->
++'a'; //? <->
++[]; //? <->
++{}; //? <->
++function(){}; //? <->
++function*(){}; //? <->
++async function(){}; //? <->
++async function*(){}; //? <->
++class{}; //? <->
++/a/; //? <->
++`a`; //? <->
++a.b; //? <+>
++a[b]; //? <+>
++a`b`; //? <->
!{a(){ ++super.b; }}; //? <+>
!{a(){ ++super[b]; }}; //? <+>
!function(){ ++new.target; } //? <->
++import.meta; //? <-#>
++new a; //? <->
++a(); //? <->
++a().b; //? <+>
++a()[b]; //? <+>
class a extends b { constructor(){ ++super(); }}; //? <->
++import('a'); //? <-#>
++a?.b; //? <->
++ ++a; //? <->
///
++(a); //? <+>
++(a.b); //? <+>
++(a[b]); //? <+>
++(a().b); //? <+>
++(a()[b]); //? <+>
++(((a()[b]))); //? <+>
///
'use strict'; var a; delete a; //? <->
'use strict'; var a; delete (a); //? <->
'use strict'; var a; delete ((((a)))); //? <->
