var eval; //? <+>
var arguments; //? <+>
var yield; //? <+>
var await; //? <+>
var let; //? <+>
var static; //? <+>
var implements; //? <+>
var interface; //? <+>
var package; //? <+>
var private; //? <+>
var protected; //? <+>
var public; //? <+>

//- let_in_lexical
let eval; //? <+>
let arguments; //? <+>
let yield; //? <+>
let await; //? <+>
let let; //? <-> @1:5
let static; //? <+>
let implements; //? <+>
let interface; //? <+>
let package; //? <+>
let private; //? <+>
let protected; //? <+>
let public; //? <+>

//- let_in_lexical
const eval = 0; //? <+>
const arguments = 0; //? <+>
const yield = 0; //? <+>
const await = 0; //? <+>
const let = 0; //? <-> @1:7
const static = 0; //? <+>
const implements = 0; //? <+>
const interface = 0; //? <+>
const package = 0; //? <+>
const private = 0; //? <+>
const protected = 0; //? <+>
const public = 0; //? <+>

//- await_in_module
var await; //? <-#> @1:5
let await; //? <-#> @1:5
const await = 0; //? <-#> @1:7

//- eval_args_in_strict_mode
'use strict'; var eval; //? <-> @1:19
'use strict'; var arguments; //? <-> @1:19
///
'use strict'; let eval; //? <-> @1:19
'use strict'; let arguments; //? <-> @1:19
///
'use strict'; const eval = 0; //? <-> @1:21
'use strict'; const arguments = 0; //? <-> @1:21
//- yield_in_strict_mode
'use strict'; var yield; //? <-> @1:19
'use strict'; let yield; //? <-> @1:19
'use strict'; const yield = 0; //? <-> @1:21
//- invalid_strict_mode_identifier
'use strict'; var await; //? <+>
'use strict'; var let; //? <-> @1:19
'use strict'; var static; //? <-> @1:19
'use strict'; var implements; //? <-> @1:19
'use strict'; var interface; //? <-> @1:19
'use strict'; var package; //? <-> @1:19
'use strict'; var private; //? <-> @1:19
'use strict'; var protected; //? <-> @1:19
'use strict'; var public; //? <-> @1:19
///
'use strict'; let await; //? <+>
'use strict'; let let; //? <-> @1:19 -let_in_lexical
'use strict'; let static; //? <-> @1:19
'use strict'; let implements; //? <-> @1:19
'use strict'; let interface; //? <-> @1:19
'use strict'; let package; //? <-> @1:19
'use strict'; let private; //? <-> @1:19
'use strict'; let protected; //? <-> @1:19
'use strict'; let public; //? <-> @1:19
///
'use strict'; const await = 0; //? <+>
'use strict'; const let = 0; //? <-> @1:21 -let_in_lexical
'use strict'; const static = 0; //? <-> @1:21
'use strict'; const implements = 0; //? <-> @1:21
'use strict'; const interface = 0; //? <-> @1:21
'use strict'; const package = 0; //? <-> @1:21
'use strict'; const private = 0; //? <-> @1:21
'use strict'; const protected = 0; //? <-> @1:21
'use strict'; const public = 0; //? <-> @1:21
