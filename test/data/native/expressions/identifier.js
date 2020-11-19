await; //? <+>
yield; //? <+>
let; //? <+>
static; //? <+>
implements; //? <+>
interface; //? <+>
package; //? <+>
private; //? <+>
protected; //? <+>
public; //? <+>
as; //? <+>
async; //? <+>
from; //? <+>
get; //? <+>
of; //? <+>
set; //? <+>
target; //? <+>

let \u0061wait; // let await; //? <+?a>
\u0061wait = 0; // await = 0; //? <+?>
\u0061wait: ; // await: ; //? <+?>

let yiel\u0064; // let yield; //? <+?>
yiel\u0064 = 0; // yield = 0; //? <+?>
yiel\u0064: ; // yield: ; //? <+?>

//- await_in_module
let await; //? <-#> @1:5
await = 0; //? <-#> @1:1
await: ; //? <-#> @1:1

function a() { 'use strict'; eval + 0; } //? <+>
function a() { 'use strict'; arguments + 0; } //? <+>
function a() { 'use strict'; eval: ; } //? <+>
function a() { 'use strict'; arguments: ; } //? <+>
function a() { 'use strict'; ev\u0061l: ; } //? <+>
function a() { 'use strict'; \u0061rguments: ; } //? <+>

/// BindingIdentifier
//- expect ;
let break; //? <-> @1:5
let case; //? <-> @1:5
let catch; //? <-> @1:5
let class; //? <-> @1:5
let const; //? <-> @1:5
let debugger; //? <-> @1:5
let continue; //? <-> @1:5
let default; //? <-> @1:5
let delete; //? <-> @1:5
let do; //? <-> @1:5
let else; //? <-> @1:5
let enum; //? <-> @1:5
let export; //? <-> @1:5
let extends; //? <-> @1:5
let false; //? <-> @1:5
let finally; //? <-> @1:5
let for; //? <-> @1:5
let function; //? <-> @1:5
let if; //? <-> @1:5
let import; //? <-> @1:5
let in; //? <-> @1:7 -default
let instanceof; //? <-> @1:15 -default
let new; //? <-> @1:5
let null; //? <-> @1:5
let return; //? <-> @1:5
let super; //? <-> @1:5
let switch; //? <-> @1:5
let this; //? <-> @1:5
let throw; //? <-> @1:5
let true; //? <-> @1:5
let try; //? <-> @1:5
let typeof; //? <-> @1:5
let var; //? <-> @1:5
let void; //? <-> @1:5
let while; //? <-> @1:5
let with; //? <-> @1:5

/// IdentifierReference
//- default
break = 0; //? <-> @1:1 -unsyntatic_break
case = 0; //? <-> @1:1
catch = 0; //? <-> @1:1
class = 0; //? <-> @1:7
const = 0; //? <-> @1:7
continue = 0; //? <-> @1:1 -unsyntatic_continue
debugger = 0; //? <-> @1:10
default = 0; //? <-> @1:1
delete = 0; //? <-> @1:8
do = 0; //? <-> @1:4
else = 0; //? <-> @1:1
enum = 0; //? <-> @1:1
export = 0; //? <-#> @1:8
extends = 0; //? <-> @1:1
false = 0; //? <-> @1:1 -invalid_assignment_target
finally = 0; //? <-> @1:1
for = 0; //? <-> @1:5
function = 0; //? <-> @1:10
if = 0; //? <-> @1:4
import = 0; //? <-#> @1:8
in = 0; //? <-> @1:1
instanceof = 0; //? <-> @1:1
new = 0; //? <-> @1:5
null = 0; //? <-> @1:1 -invalid_assignment_target
return = 0; //? <-> @1:1 -unsyntatic_return
super = 0; //? <-> @1:1 -standalone_super
switch = 0; //? <-> @1:8
this = 0; //? <-> @1:1 -invalid_assignment_target
throw = 0; //? <-> @1:7
true = 0; //? <-> @1:1 -invalid_assignment_target
try = 0; //? <-> @1:5
typeof = 0; //? <-> @1:8
var = 0; //? <-> @1:5
void = 0; //? <-> @1:6
while = 0; //? <-> @1:7
with = 0; //? <-> @1:6

/// LabelIdentifier
//- default
break: ; //? <-> @1:1 -unsyntatic_break
case: ; //? <-> @1:1
catch: ; //? <-> @1:1
class: ; //? <-> @1:6
const: ; //? <-> @1:6
continue: ; //? <-> @1:1 -unsyntatic_continue
debugger: ; //? <-> @1:9
default: ; //? <-> @1:1
delete: ; //? <-> @1:7
do: ; //? <-> @1:3
else: ; //? <-> @1:1
enum: ; //? <-> @1:1
export: ; //? <-#> @1:7
extends: ; //? <-> @1:1
false: ; //? <-> @1:6
finally: ; //? <-> @1:1
for: ; //? <-> @1:4
function: ; //? <-> @1:9
if: ; //? <-> @1:3
import: ; //? <-#> @1:7
in: ; //? <-> @1:1
instanceof: ; //? <-> @1:1
new: ; //? <-> @1:4
null: ; //? <-> @1:5
return: ; //? <-> @1:1 -unsyntatic_return
super: ; //? <-> @1:1 -standalone_super
switch: ; //? <-> @1:7
this: ; //? <-> @1:5
throw: ; //? <-> @1:6
true: ; //? <-> @1:5
try: ; //? <-> @1:4
typeof: ; //? <-> @1:7
var: ; //? <-> @1:4
void: ; //? <-> @1:5
while: ; //? <-> @1:6
with: ; //? <-> @1:5

//- unicode_keyword
\u0069f(true){} // if(true){} //? <-> @1:1
for(;;) \u0062reak; // for(;;) break; //? <-> @1:9
switch(a) { c\u0061se 0: } // switch(a) { case 0: } //? <-> @1:13
//- default
l\u0065t a = 0; //? <-?> @1:1
'use strict'; l\u0065t a = 0; // let a = 0; //? <-?> @1:15
'use strict'; p\u0061ckage: ; // package: //? <-?> @1:15
'use strict'; let yi\u0065ld; // let yield; //? <-?> @1:19
'use strict'; let yield; //? <-?> @1:19

//- invalid_strict_mode_identifier
'use strict'; var let; //? <-> @1:19
'use strict'; var static; //? <-> @1:19
'use strict'; var implements; //? <-> @1:19
'use strict'; var interface; //? <-> @1:19
'use strict'; var package; //? <-> @1:19
'use strict'; var private; //? <-> @1:19
'use strict'; var protected; //? <-> @1:19
'use strict'; var public; //? <-> @1:19
//- default
'use strict'; let = 0; //? <-> @1:19
'use strict'; static = 0; //? <-> @1:15
'use strict'; implements = 0; //? <-> @1:15
'use strict'; interface = 0; //? <-> @1:15
'use strict'; package = 0; //? <-> @1:15
'use strict'; private = 0; //? <-> @1:15
'use strict'; protected = 0; //? <-> @1:15
'use strict'; public = 0; //? <-> @1:15
///
'use strict'; let: ; //? <-> @1:18
'use strict'; static: ; //? <-> @1:15
'use strict'; implements: ; //? <-> @1:15
'use strict'; interface: ; //? <-> @1:15
'use strict'; package: ; //? <-> @1:15
'use strict'; private: ; //? <-> @1:15
'use strict'; protected: ; //? <-> @1:15
'use strict'; public: ; //? <-> @1:15

//- contextual_identifier
function* a(){ let yield; } //? <-> @1:20
function* a(){ yield = 0; } //? <-> @1:22 -default
function* a(){ yield: 0; } //? <-> @1:16
function* a(){ let yi\u0065ld; } //? <-?> @1:20
function* a(){ yi\u0065ld = 0; } //? <-?> @1:27 -default
function* a(){ yi\u0065ld: ; } //? <-?> @1:16

//- eval_args_in_strict_mode
'use strict'; let eval; //? <-> @1:19
'use strict'; let arguments; //? <-> @1:19
'use strict'; let ev\u0061l; //? <-?> @1:19
'use strict'; let \u0061rguments; //? <-?> @1:19
