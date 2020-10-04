"use strict";
if(true) function f(){}
//<>
"use strict";
if(true); else function f(){}
//<>
function strict(){
   "use strict";
   if(true) function f(){}
}
//<>
function strict(){
   "use strict";
   if(true); else function f(){}
}
