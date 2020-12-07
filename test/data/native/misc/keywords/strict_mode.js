//- eval_args_in_strict_mode
eval; //? <+>
[eval]; //? <+>
[...eval]; //? <+>
!{eval}; //? <+>
!{eval: 0}; //? <+>
!{[eval]: 0}; //? <+>
!{eval = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ eval(){} } //? <+>
!{ [eval](){} } //? <+>
!{ a(eval){} } //? <+>
!{ a([eval]){} } //? <+>
!{ a({eval}){} } //? <+>
!{ a([...eval]){} } //? <+>
!{ a({...eval}){} } //? <+>
!{ a(...eval){} } //? <+>
!{ set a(eval){} } //? <+>
!{ set a([eval]){} } //? <+>
!{ set a({eval}){} } //? <+>
!{ set a([...eval]){} } //? <+>
!{ set a({...eval}){} } //? <+>
!{ set a(...eval){} } //? <-> @1:10 -default
!function eval(){} //? <+>
!function a(eval){} //? <+>
!function a(b = eval){} //? <+>
!function a([eval]){} //? <+>
!function a({eval}){} //? <+>
!function a([...eval]){} //? <+>
!function a({...eval}){} //? <+>
!function a(...eval){} //? <+>
!class eval {} //? <-> @1:8
!class a extends eval {} //? <+>
!class a { eval(){} } //? <+>
!class a { [eval](){} } //? <+>
!class a { b(eval){} } //? <-> @1:14
!class a { b([eval]){} } //? <-> @1:15
!class a { b({eval}){} } //? <-> @1:15
!class a { b([...eval]){} } //? <-> @1:18
!class a { b({...eval}){} } //? <-> @1:18
!class a { b(...eval){} } //? <-> @1:17
`${eval}`; //? <+>
a.eval; //? <+>
``.eval; //? <+>
eval++; //? <+>
++eval; //? <+>
eval = 0; //? <+>
eval *= 0; //? <+>
[eval] = []; //? <+>
({eval} = {}); //? <+>
({eval = 0} = {}); //? <+>
[...eval] = []; //? <+>
({...eval} = {}); //? <+>
eval => {}; //? <+>
(eval) => {}; //? <+>
([eval]) => {}; //? <+>
({eval}) => {}; //? <+>
([...eval]) => {}; //? <+>
({...eval}) => {}; //? <+>
(...eval) => {}; //? <+>
async (eval) => {}; //? <+>
async ([eval]) => {}; //? <+>
async ({eval}) => {}; //? <+>
async ([...eval]) => {}; //? <+>
async ({...eval}) => {}; //? <+>
async (...eval) => {}; //? <+>
eval: ; //? <+>
var eval; //? <+>
var [eval] = []; //? <+>
var {eval} = {}; //? <+>
var [...eval] = []; //? <+>
var {...eval} = {}; //? <+>
let eval; //? <+>
let [eval] = []; //? <+>
let {eval} = {}; //? <+>
let [...eval] = []; //? <+>
let {...eval} = {}; //? <+>
const eval = 0; //? <+>
const [eval] = 0; //? <+>
const {eval} = 0; //? <+>
const [...eval] = 0; //? <+>
const {...eval} = 0; //? <+>
function eval(){} //? <+>
function a(eval){} //? <+>
function a(b = eval){} //? <+>
function a([eval]){} //? <+>
function a({eval}){} //? <+>
function a([...eval]){} //? <+>
function a({...eval}){} //? <+>
function a(...eval){} //? <+>
class eval {} //? <-> @1:7
class a extends eval {} //? <+>
class a { eval(){} } //? <+>
class a { [eval](){} } //? <+>
class a { b(eval){} } //? <-> @1:13
class a { b([eval]){} } //? <-> @1:14
class a { b({eval}){} } //? <-> @1:14
class a { b([...eval]){} } //? <-> @1:17
class a { b({...eval}){} } //? <-> @1:17
class a { b(...eval){} } //? <-> @1:16

//- eval_args_in_strict_mode
arguments; //? <+>
[arguments]; //? <+>
[...arguments]; //? <+>
!{arguments}; //? <+>
!{arguments: 0}; //? <+>
!{[arguments]: 0}; //? <+>
!{arguments = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ arguments(){} } //? <+>
!{ [arguments](){} } //? <+>
!{ a(arguments){} } //? <+>
!{ a([arguments]){} } //? <+>
!{ a({arguments}){} } //? <+>
!{ a([...arguments]){} } //? <+>
!{ a({...arguments}){} } //? <+>
!{ a(...arguments){} } //? <+>
!{ set a(arguments){} } //? <+>
!{ set a([arguments]){} } //? <+>
!{ set a({arguments}){} } //? <+>
!{ set a([...arguments]){} } //? <+>
!{ set a({...arguments}){} } //? <+>
!{ set a(...arguments){} } //? <-> @1:10 -default
!function arguments(){} //? <+>
!function a(arguments){} //? <+>
!function a(b = arguments){} //? <+>
!function a([arguments]){} //? <+>
!function a({arguments}){} //? <+>
!function a([...arguments]){} //? <+>
!function a({...arguments}){} //? <+>
!function a(...arguments){} //? <+>
!class arguments {} //? <-> @1:8
!class a extends arguments {} //? <+>
!class a { arguments(){} } //? <+>
!class a { [arguments](){} } //? <+>
!class a { b(arguments){} } //? <-> @1:14
!class a { b([arguments]){} } //? <-> @1:15
!class a { b({arguments}){} } //? <-> @1:15
!class a { b([...arguments]){} } //? <-> @1:18
!class a { b({...arguments}){} } //? <-> @1:18
!class a { b(...arguments){} } //? <-> @1:17
`${arguments}`; //? <+>
a.arguments; //? <+>
``.arguments; //? <+>
arguments++; //? <+>
++arguments; //? <+>
arguments = 0; //? <+>
arguments *= 0; //? <+>
[arguments] = []; //? <+>
({arguments} = {}); //? <+>
({arguments = 0} = {}); //? <+>
[...arguments] = []; //? <+>
({...arguments} = {}); //? <+>
arguments => {}; //? <+>
(arguments) => {}; //? <+>
([arguments]) => {}; //? <+>
({arguments}) => {}; //? <+>
([...arguments]) => {}; //? <+>
({...arguments}) => {}; //? <+>
(...arguments) => {}; //? <+>
async (arguments) => {}; //? <+>
async ([arguments]) => {}; //? <+>
async ({arguments}) => {}; //? <+>
async ([...arguments]) => {}; //? <+>
async ({...arguments}) => {}; //? <+>
async (...arguments) => {}; //? <+>
arguments: ; //? <+>
var arguments; //? <+>
var [arguments] = []; //? <+>
var {arguments} = {}; //? <+>
var [...arguments] = []; //? <+>
var {...arguments} = {}; //? <+>
let arguments; //? <+>
let [arguments] = []; //? <+>
let {arguments} = {}; //? <+>
let [...arguments] = []; //? <+>
let {...arguments} = {}; //? <+>
const arguments = 0; //? <+>
const [arguments] = 0; //? <+>
const {arguments} = 0; //? <+>
const [...arguments] = 0; //? <+>
const {...arguments} = 0; //? <+>
function arguments(){} //? <+>
function a(arguments){} //? <+>
function a(b = arguments){} //? <+>
function a([arguments]){} //? <+>
function a({arguments}){} //? <+>
function a([...arguments]){} //? <+>
function a({...arguments}){} //? <+>
function a(...arguments){} //? <+>
class arguments {} //? <-> @1:7
class a extends arguments {} //? <+>
class a { arguments(){} } //? <+>
class a { [arguments](){} } //? <+>
class a { b(arguments){} } //? <-> @1:13
class a { b([arguments]){} } //? <-> @1:14
class a { b({arguments}){} } //? <-> @1:14
class a { b([...arguments]){} } //? <-> @1:17
class a { b({...arguments}){} } //? <-> @1:17
class a { b(...arguments){} } //? <-> @1:16

//- yield_in_strict_mode
yield; //? <+>
[yield]; //? <+>
[...yield]; //? <+>
!{yield}; //? <+>
!{yield: 0}; //? <+>
!{[yield]: 0}; //? <+>
!{yield = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ yield(){} } //? <+>
!{ [yield](){} } //? <+>
!{ a(yield){} } //? <+>
!{ a([yield]){} } //? <+>
!{ a({yield}){} } //? <+>
!{ a([...yield]){} } //? <+>
!{ a({...yield}){} } //? <+>
!{ a(...yield){} } //? <+>
!{ set a(yield){} } //? <+>
!{ set a([yield]){} } //? <+>
!{ set a({yield}){} } //? <+>
!{ set a([...yield]){} } //? <+>
!{ set a({...yield}){} } //? <+>
!{ set a(...yield){} } //? <-> @1:10 -default
!function yield(){} //? <+>
!function a(yield){} //? <+>
!function a(b = yield){} //? <+>
!function a([yield]){} //? <+>
!function a({yield}){} //? <+>
!function a([...yield]){} //? <+>
!function a({...yield}){} //? <+>
!function a(...yield){} //? <+>
!class yield {} //? <-> @1:8
!class a extends yield {} //? <-> @1:18
!class a { yield(){} } //? <+>
!class a { [yield](){} } //? <-> @1:13
!class a { b(yield){} } //? <-> @1:14
!class a { b([yield]){} } //? <-> @1:15
!class a { b({yield}){} } //? <-> @1:15
!class a { b([...yield]){} } //? <-> @1:18
!class a { b({...yield}){} } //? <-> @1:18
!class a { b(...yield){} } //? <-> @1:17
`${yield}`; //? <+>
a.yield; //? <+>
``.yield; //? <+>
yield++; //? <+>
++yield; //? <+>
yield = 0; //? <+>
yield *= 0; //? <+>
[yield] = []; //? <+>
({yield} = {}); //? <+>
({yield = 0} = {}); //? <+>
[...yield] = []; //? <+>
({...yield} = {}); //? <+>
yield => {}; //? <+>
(yield) => {}; //? <+>
([yield]) => {}; //? <+>
({yield}) => {}; //? <+>
([...yield]) => {}; //? <+>
({...yield}) => {}; //? <+>
(...yield) => {}; //? <+>
async (yield) => {}; //? <+>
async ([yield]) => {}; //? <+>
async ({yield}) => {}; //? <+>
async ([...yield]) => {}; //? <+>
async ({...yield}) => {}; //? <+>
async (...yield) => {}; //? <+>
yield: ; //? <+>
var yield; //? <+>
var [yield] = []; //? <+>
var {yield} = {}; //? <+>
var [...yield] = []; //? <+>
var {...yield} = {}; //? <+>
let yield; //? <+>
let [yield] = []; //? <+>
let {yield} = {}; //? <+>
let [...yield] = []; //? <+>
let {...yield} = {}; //? <+>
const yield = 0; //? <+>
const [yield] = 0; //? <+>
const {yield} = 0; //? <+>
const [...yield] = 0; //? <+>
const {...yield} = 0; //? <+>
function yield(){} //? <+>
function a(yield){} //? <+>
function a(b = yield){} //? <+>
function a([yield]){} //? <+>
function a({yield}){} //? <+>
function a([...yield]){} //? <+>
function a({...yield}){} //? <+>
function a(...yield){} //? <+>
class yield {} //? <-> @1:7
class a extends yield {} //? <-> @1:17
class a { yield(){} } //? <+>
class a { [yield](){} } //? <-> @1:12
class a { b(yield){} } //? <-> @1:13
class a { b([yield]){} } //? <-> @1:14
class a { b({yield}){} } //? <-> @1:14
class a { b([...yield]){} } //? <-> @1:17
class a { b({...yield}){} } //? <-> @1:17
class a { b(...yield){} } //? <-> @1:16

//- await_in_module
await; //? <+>
[await]; //? <+>
[...await]; //? <+>
!{await}; //? <+>
!{await: 0}; //? <+>
!{[await]: 0}; //? <+>
!{await = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ await(){} } //? <+>
!{ [await](){} } //? <+>
!{ a(await){} } //? <+>
!{ a([await]){} } //? <+>
!{ a({await}){} } //? <+>
!{ a([...await]){} } //? <+>
!{ a({...await}){} } //? <+>
!{ a(...await){} } //? <+>
!{ set a(await){} } //? <+>
!{ set a([await]){} } //? <+>
!{ set a({await}){} } //? <+>
!{ set a([...await]){} } //? <+>
!{ set a({...await}){} } //? <+>
!{ set a(...await){} } //? <-> @1:10 -default
!function await(){} //? <+>
!function a(await){} //? <+>
!function a(b = await){} //? <+>
!function a([await]){} //? <+>
!function a({await}){} //? <+>
!function a([...await]){} //? <+>
!function a({...await}){} //? <+>
!function a(...await){} //? <+>
!class await {} //? <+>
!class a extends await {} //? <+>
!class a { await(){} } //? <+>
!class a { [await](){} } //? <+>
!class a { b(await){} } //? <+>
!class a { b([await]){} } //? <+>
!class a { b({await}){} } //? <+>
!class a { b([...await]){} } //? <+>
!class a { b({...await}){} } //? <+>
!class a { b(...await){} } //? <+>
`${await}`; //? <+>
a.await; //? <+>
``.await; //? <+>
await++; //? <+>
++await; //? <+>
await = 0; //? <+>
await *= 0; //? <+>
[await] = []; //? <+>
({await} = {}); //? <+>
({await = 0} = {}); //? <+>
[...await] = []; //? <+>
({...await} = {}); //? <+>
await => {}; //? <+>
(await) => {}; //? <+>
([await]) => {}; //? <+>
({await}) => {}; //? <+>
([...await]) => {}; //? <+>
({...await}) => {}; //? <+>
(...await) => {}; //? <+>
async (await) => {}; //? <-> @1:8 -yield_await_in_arrow_params
async ([await]) => {}; //? <-> @1:9 -yield_await_in_arrow_params
async ({await}) => {}; //? <-> @1:9 -yield_await_in_arrow_params
async ([...await]) => {}; //? <-> @1:12 -yield_await_in_arrow_params
async ({...await}) => {}; //? <-> @1:12 -yield_await_in_arrow_params
async (...await) => {}; //? <-> @1:11 -yield_await_in_arrow_params
await: ; //? <+>
var await; //? <+>
var [await] = []; //? <+>
var {await} = {}; //? <+>
var [...await] = []; //? <+>
var {...await} = {}; //? <+>
let await; //? <+>
let [await] = []; //? <+>
let {await} = {}; //? <+>
let [...await] = []; //? <+>
let {...await} = {}; //? <+>
const await = 0; //? <+>
const [await] = 0; //? <+>
const {await} = 0; //? <+>
const [...await] = 0; //? <+>
const {...await} = 0; //? <+>
function await(){} //? <+>
function a(await){} //? <+>
function a(b = await){} //? <+>
function a([await]){} //? <+>
function a({await}){} //? <+>
function a([...await]){} //? <+>
function a({...await}){} //? <+>
function a(...await){} //? <+>
class await {} //? <+>
class a extends await {} //? <+>
class a { await(){} } //? <+>
class a { [await](){} } //? <+>
class a { b(await){} } //? <+>
class a { b([await]){} } //? <+>
class a { b({await}){} } //? <+>
class a { b([...await]){} } //? <+>
class a { b({...await}){} } //? <+>
class a { b(...await){} } //? <+>

//- invalid_strict_mode_identifier
let; //? <+>
[let]; //? <+>
[...let]; //? <+>
!{let}; //? <+>
!{let: 0}; //? <+>
!{[let]: 0}; //? <+>
!{let = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ let(){} } //? <+>
!{ [let](){} } //? <+>
!{ a(let){} } //? <+>
!{ a([let]){} } //? <+>
!{ a({let}){} } //? <+>
!{ a([...let]){} } //? <+>
!{ a({...let}){} } //? <+>
!{ a(...let){} } //? <+>
!{ set a(let){} } //? <+>
!{ set a([let]){} } //? <+>
!{ set a({let}){} } //? <+>
!{ set a([...let]){} } //? <+>
!{ set a({...let}){} } //? <+>
!{ set a(...let){} } //? <-> @1:10 -default
!function let(){} //? <+>
!function a(let){} //? <+>
!function a(b = let){} //? <+>
!function a([let]){} //? <+>
!function a({let}){} //? <+>
!function a([...let]){} //? <+>
!function a({...let}){} //? <+>
!function a(...let){} //? <+>
!class let {} //? <-> @1:8
!class a extends let {} //? <-> @1:18
!class a { let(){} } //? <+>
!class a { [let](){} } //? <-> @1:13
!class a { b(let){} } //? <-> @1:14
!class a { b([let]){} } //? <-> @1:15
!class a { b({let}){} } //? <-> @1:15
!class a { b([...let]){} } //? <-> @1:18
!class a { b({...let}){} } //? <-> @1:18
!class a { b(...let){} } //? <-> @1:17
`${let}`; //? <+>
a.let; //? <+>
``.let; //? <+>
let++; //? <+>
++let; //? <+>
let = 0; //? <+>
let *= 0; //? <+>
[let] = []; //? <+>
({let} = {}); //? <+>
({let = 0} = {}); //? <+>
[...let] = []; //? <+>
({...let} = {}); //? <+>
let => {}; //? <+>
(let) => {}; //? <+>
([let]) => {}; //? <+>
({let}) => {}; //? <+>
([...let]) => {}; //? <+>
({...let}) => {}; //? <+>
(...let) => {}; //? <+>
async (let) => {}; //? <+>
async ([let]) => {}; //? <+>
async ({let}) => {}; //? <+>
async ([...let]) => {}; //? <+>
async ({...let}) => {}; //? <+>
async (...let) => {}; //? <+>
let: ; //? <+>
var let; //? <+>
var [let] = []; //? <+>
var {let} = {}; //? <+>
var [...let] = []; //? <+>
var {...let} = {}; //? <+>
let let; //? <-> @1:5 -let_in_lexical
let [let] = []; //? <-> @1:6 -let_in_lexical
let {let} = {}; //? <-> @1:6 -let_in_lexical
let [...let] = []; //? <-> @1:9 -let_in_lexical
let {...let} = {}; //? <-> @1:9 -let_in_lexical
const let = 0; //? <-> @1:7 -let_in_lexical
const [let] = 0; //? <-> @1:8 -let_in_lexical
const {let} = 0; //? <-> @1:8 -let_in_lexical
const [...let] = 0; //? <-> @1:11 -let_in_lexical
const {...let} = 0; //? <-> @1:11 -let_in_lexical
function let(){} //? <+>
function a(let){} //? <+>
function a(b = let){} //? <+>
function a([let]){} //? <+>
function a({let}){} //? <+>
function a([...let]){} //? <+>
function a({...let}){} //? <+>
function a(...let){} //? <+>
class let {} //? <-> @1:7
class a extends let {} //? <-> @1:17
class a { let(){} } //? <+>
class a { [let](){} } //? <-> @1:12
class a { b(let){} } //? <-> @1:13
class a { b([let]){} } //? <-> @1:14
class a { b({let}){} } //? <-> @1:14
class a { b([...let]){} } //? <-> @1:17
class a { b({...let}){} } //? <-> @1:17
class a { b(...let){} } //? <-> @1:16

//- invalid_strict_mode_identifier
static; //? <+>
[static]; //? <+>
[...static]; //? <+>
!{static}; //? <+>
!{static: 0}; //? <+>
!{[static]: 0}; //? <+>
!{static = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ static(){} } //? <+>
!{ [static](){} } //? <+>
!{ a(static){} } //? <+>
!{ a([static]){} } //? <+>
!{ a({static}){} } //? <+>
!{ a([...static]){} } //? <+>
!{ a({...static}){} } //? <+>
!{ a(...static){} } //? <+>
!{ set a(static){} } //? <+>
!{ set a([static]){} } //? <+>
!{ set a({static}){} } //? <+>
!{ set a([...static]){} } //? <+>
!{ set a({...static}){} } //? <+>
!{ set a(...static){} } //? <-> @1:10 -default
!function static(){} //? <+>
!function a(static){} //? <+>
!function a(b = static){} //? <+>
!function a([static]){} //? <+>
!function a({static}){} //? <+>
!function a([...static]){} //? <+>
!function a({...static}){} //? <+>
!function a(...static){} //? <+>
!class static {} //? <-> @1:8
!class a extends static {} //? <-> @1:18
!class a { static(){} } //? <+>
!class a { [static](){} } //? <-> @1:13
!class a { b(static){} } //? <-> @1:14
!class a { b([static]){} } //? <-> @1:15
!class a { b({static}){} } //? <-> @1:15
!class a { b([...static]){} } //? <-> @1:18
!class a { b({...static}){} } //? <-> @1:18
!class a { b(...static){} } //? <-> @1:17
`${static}`; //? <+>
a.static; //? <+>
``.static; //? <+>
static++; //? <+>
++static; //? <+>
static = 0; //? <+>
static *= 0; //? <+>
[static] = []; //? <+>
({static} = {}); //? <+>
({static = 0} = {}); //? <+>
[...static] = []; //? <+>
({...static} = {}); //? <+>
static => {}; //? <+>
(static) => {}; //? <+>
([static]) => {}; //? <+>
({static}) => {}; //? <+>
([...static]) => {}; //? <+>
({...static}) => {}; //? <+>
(...static) => {}; //? <+>
async (static) => {}; //? <+>
async ([static]) => {}; //? <+>
async ({static}) => {}; //? <+>
async ([...static]) => {}; //? <+>
async ({...static}) => {}; //? <+>
async (...static) => {}; //? <+>
static: ; //? <+>
var static; //? <+>
var [static] = []; //? <+>
var {static} = {}; //? <+>
var [...static] = []; //? <+>
var {...static} = {}; //? <+>
let static; //? <+>
let [static] = []; //? <+>
let {static} = {}; //? <+>
let [...static] = []; //? <+>
let {...static} = {}; //? <+>
const static = 0; //? <+>
const [static] = 0; //? <+>
const {static} = 0; //? <+>
const [...static] = 0; //? <+>
const {...static} = 0; //? <+>
function static(){} //? <+>
function a(static){} //? <+>
function a(b = static){} //? <+>
function a([static]){} //? <+>
function a({static}){} //? <+>
function a([...static]){} //? <+>
function a({...static}){} //? <+>
function a(...static){} //? <+>
class static {} //? <-> @1:7
class a extends static {} //? <-> @1:17
class a { static(){} } //? <+>
class a { [static](){} } //? <-> @1:12
class a { b(static){} } //? <-> @1:13
class a { b([static]){} } //? <-> @1:14
class a { b({static}){} } //? <-> @1:14
class a { b([...static]){} } //? <-> @1:17
class a { b({...static}){} } //? <-> @1:17
class a { b(...static){} } //? <-> @1:16

//- invalid_strict_mode_identifier
implements; //? <+>
[implements]; //? <+>
[...implements]; //? <+>
!{implements}; //? <+>
!{implements: 0}; //? <+>
!{[implements]: 0}; //? <+>
!{implements = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ implements(){} } //? <+>
!{ [implements](){} } //? <+>
!{ a(implements){} } //? <+>
!{ a([implements]){} } //? <+>
!{ a({implements}){} } //? <+>
!{ a([...implements]){} } //? <+>
!{ a({...implements}){} } //? <+>
!{ a(...implements){} } //? <+>
!{ set a(implements){} } //? <+>
!{ set a([implements]){} } //? <+>
!{ set a({implements}){} } //? <+>
!{ set a([...implements]){} } //? <+>
!{ set a({...implements}){} } //? <+>
!{ set a(...implements){} } //? <-> @1:10 -default
!function implements(){} //? <+>
!function a(implements){} //? <+>
!function a(b = implements){} //? <+>
!function a([implements]){} //? <+>
!function a({implements}){} //? <+>
!function a([...implements]){} //? <+>
!function a({...implements}){} //? <+>
!function a(...implements){} //? <+>
!class implements {} //? <-> @1:8
!class a extends implements {} //? <-> @1:18
!class a { implements(){} } //? <+>
!class a { [implements](){} } //? <-> @1:13
!class a { b(implements){} } //? <-> @1:14
!class a { b([implements]){} } //? <-> @1:15
!class a { b({implements}){} } //? <-> @1:15
!class a { b([...implements]){} } //? <-> @1:18
!class a { b({...implements}){} } //? <-> @1:18
!class a { b(...implements){} } //? <-> @1:17
`${implements}`; //? <+>
a.implements; //? <+>
``.implements; //? <+>
implements++; //? <+>
++implements; //? <+>
implements = 0; //? <+>
implements *= 0; //? <+>
[implements] = []; //? <+>
({implements} = {}); //? <+>
({implements = 0} = {}); //? <+>
[...implements] = []; //? <+>
({...implements} = {}); //? <+>
implements => {}; //? <+>
(implements) => {}; //? <+>
([implements]) => {}; //? <+>
({implements}) => {}; //? <+>
([...implements]) => {}; //? <+>
({...implements}) => {}; //? <+>
(...implements) => {}; //? <+>
async (implements) => {}; //? <+>
async ([implements]) => {}; //? <+>
async ({implements}) => {}; //? <+>
async ([...implements]) => {}; //? <+>
async ({...implements}) => {}; //? <+>
async (...implements) => {}; //? <+>
implements: ; //? <+>
var implements; //? <+>
var [implements] = []; //? <+>
var {implements} = {}; //? <+>
var [...implements] = []; //? <+>
var {...implements} = {}; //? <+>
let implements; //? <+>
let [implements] = []; //? <+>
let {implements} = {}; //? <+>
let [...implements] = []; //? <+>
let {...implements} = {}; //? <+>
const implements = 0; //? <+>
const [implements] = 0; //? <+>
const {implements} = 0; //? <+>
const [...implements] = 0; //? <+>
const {...implements} = 0; //? <+>
function implements(){} //? <+>
function a(implements){} //? <+>
function a(b = implements){} //? <+>
function a([implements]){} //? <+>
function a({implements}){} //? <+>
function a([...implements]){} //? <+>
function a({...implements}){} //? <+>
function a(...implements){} //? <+>
class implements {} //? <-> @1:7
class a extends implements {} //? <-> @1:17
class a { implements(){} } //? <+>
class a { [implements](){} } //? <-> @1:12
class a { b(implements){} } //? <-> @1:13
class a { b([implements]){} } //? <-> @1:14
class a { b({implements}){} } //? <-> @1:14
class a { b([...implements]){} } //? <-> @1:17
class a { b({...implements}){} } //? <-> @1:17
class a { b(...implements){} } //? <-> @1:16

//- invalid_strict_mode_identifier
interface; //? <+>
[interface]; //? <+>
[...interface]; //? <+>
!{interface}; //? <+>
!{interface: 0}; //? <+>
!{[interface]: 0}; //? <+>
!{interface = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ interface(){} } //? <+>
!{ [interface](){} } //? <+>
!{ a(interface){} } //? <+>
!{ a([interface]){} } //? <+>
!{ a({interface}){} } //? <+>
!{ a([...interface]){} } //? <+>
!{ a({...interface}){} } //? <+>
!{ a(...interface){} } //? <+>
!{ set a(interface){} } //? <+>
!{ set a([interface]){} } //? <+>
!{ set a({interface}){} } //? <+>
!{ set a([...interface]){} } //? <+>
!{ set a({...interface}){} } //? <+>
!{ set a(...interface){} } //? <-> @1:10 -default
!function interface(){} //? <+>
!function a(interface){} //? <+>
!function a(b = interface){} //? <+>
!function a([interface]){} //? <+>
!function a({interface}){} //? <+>
!function a([...interface]){} //? <+>
!function a({...interface}){} //? <+>
!function a(...interface){} //? <+>
!class interface {} //? <-> @1:8
!class a extends interface {} //? <-> @1:18
!class a { interface(){} } //? <+>
!class a { [interface](){} } //? <-> @1:13
!class a { b(interface){} } //? <-> @1:14
!class a { b([interface]){} } //? <-> @1:15
!class a { b({interface}){} } //? <-> @1:15
!class a { b([...interface]){} } //? <-> @1:18
!class a { b({...interface}){} } //? <-> @1:18
!class a { b(...interface){} } //? <-> @1:17
`${interface}`; //? <+>
a.interface; //? <+>
``.interface; //? <+>
interface++; //? <+>
++interface; //? <+>
interface = 0; //? <+>
interface *= 0; //? <+>
[interface] = []; //? <+>
({interface} = {}); //? <+>
({interface = 0} = {}); //? <+>
[...interface] = []; //? <+>
({...interface} = {}); //? <+>
interface => {}; //? <+>
(interface) => {}; //? <+>
([interface]) => {}; //? <+>
({interface}) => {}; //? <+>
([...interface]) => {}; //? <+>
({...interface}) => {}; //? <+>
(...interface) => {}; //? <+>
async (interface) => {}; //? <+>
async ([interface]) => {}; //? <+>
async ({interface}) => {}; //? <+>
async ([...interface]) => {}; //? <+>
async ({...interface}) => {}; //? <+>
async (...interface) => {}; //? <+>
interface: ; //? <+>
var interface; //? <+>
var [interface] = []; //? <+>
var {interface} = {}; //? <+>
var [...interface] = []; //? <+>
var {...interface} = {}; //? <+>
let interface; //? <+>
let [interface] = []; //? <+>
let {interface} = {}; //? <+>
let [...interface] = []; //? <+>
let {...interface} = {}; //? <+>
const interface = 0; //? <+>
const [interface] = 0; //? <+>
const {interface} = 0; //? <+>
const [...interface] = 0; //? <+>
const {...interface} = 0; //? <+>
function interface(){} //? <+>
function a(interface){} //? <+>
function a(b = interface){} //? <+>
function a([interface]){} //? <+>
function a({interface}){} //? <+>
function a([...interface]){} //? <+>
function a({...interface}){} //? <+>
function a(...interface){} //? <+>
class interface {} //? <-> @1:7
class a extends interface {} //? <-> @1:17
class a { interface(){} } //? <+>
class a { [interface](){} } //? <-> @1:12
class a { b(interface){} } //? <-> @1:13
class a { b([interface]){} } //? <-> @1:14
class a { b({interface}){} } //? <-> @1:14
class a { b([...interface]){} } //? <-> @1:17
class a { b({...interface}){} } //? <-> @1:17
class a { b(...interface){} } //? <-> @1:16

//- invalid_strict_mode_identifier
package; //? <+>
[package]; //? <+>
[...package]; //? <+>
!{package}; //? <+>
!{package: 0}; //? <+>
!{[package]: 0}; //? <+>
!{package = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ package(){} } //? <+>
!{ [package](){} } //? <+>
!{ a(package){} } //? <+>
!{ a([package]){} } //? <+>
!{ a({package}){} } //? <+>
!{ a([...package]){} } //? <+>
!{ a({...package}){} } //? <+>
!{ a(...package){} } //? <+>
!{ set a(package){} } //? <+>
!{ set a([package]){} } //? <+>
!{ set a({package}){} } //? <+>
!{ set a([...package]){} } //? <+>
!{ set a({...package}){} } //? <+>
!{ set a(...package){} } //? <-> @1:10 -default
!function package(){} //? <+>
!function a(package){} //? <+>
!function a(b = package){} //? <+>
!function a([package]){} //? <+>
!function a({package}){} //? <+>
!function a([...package]){} //? <+>
!function a({...package}){} //? <+>
!function a(...package){} //? <+>
!class package {} //? <-> @1:8
!class a extends package {} //? <-> @1:18
!class a { package(){} } //? <+>
!class a { [package](){} } //? <-> @1:13
!class a { b(package){} } //? <-> @1:14
!class a { b([package]){} } //? <-> @1:15
!class a { b({package}){} } //? <-> @1:15
!class a { b([...package]){} } //? <-> @1:18
!class a { b({...package}){} } //? <-> @1:18
!class a { b(...package){} } //? <-> @1:17
`${package}`; //? <+>
a.package; //? <+>
``.package; //? <+>
package++; //? <+>
++package; //? <+>
package = 0; //? <+>
package *= 0; //? <+>
[package] = []; //? <+>
({package} = {}); //? <+>
({package = 0} = {}); //? <+>
[...package] = []; //? <+>
({...package} = {}); //? <+>
package => {}; //? <+>
(package) => {}; //? <+>
([package]) => {}; //? <+>
({package}) => {}; //? <+>
([...package]) => {}; //? <+>
({...package}) => {}; //? <+>
(...package) => {}; //? <+>
async (package) => {}; //? <+>
async ([package]) => {}; //? <+>
async ({package}) => {}; //? <+>
async ([...package]) => {}; //? <+>
async ({...package}) => {}; //? <+>
async (...package) => {}; //? <+>
package: ; //? <+>
var package; //? <+>
var [package] = []; //? <+>
var {package} = {}; //? <+>
var [...package] = []; //? <+>
var {...package} = {}; //? <+>
let package; //? <+>
let [package] = []; //? <+>
let {package} = {}; //? <+>
let [...package] = []; //? <+>
let {...package} = {}; //? <+>
const package = 0; //? <+>
const [package] = 0; //? <+>
const {package} = 0; //? <+>
const [...package] = 0; //? <+>
const {...package} = 0; //? <+>
function package(){} //? <+>
function a(package){} //? <+>
function a(b = package){} //? <+>
function a([package]){} //? <+>
function a({package}){} //? <+>
function a([...package]){} //? <+>
function a({...package}){} //? <+>
function a(...package){} //? <+>
class package {} //? <-> @1:7
class a extends package {} //? <-> @1:17
class a { package(){} } //? <+>
class a { [package](){} } //? <-> @1:12
class a { b(package){} } //? <-> @1:13
class a { b([package]){} } //? <-> @1:14
class a { b({package}){} } //? <-> @1:14
class a { b([...package]){} } //? <-> @1:17
class a { b({...package}){} } //? <-> @1:17
class a { b(...package){} } //? <-> @1:16

//- invalid_strict_mode_identifier
private; //? <+>
[private]; //? <+>
[...private]; //? <+>
!{private}; //? <+>
!{private: 0}; //? <+>
!{[private]: 0}; //? <+>
!{private = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ private(){} } //? <+>
!{ [private](){} } //? <+>
!{ a(private){} } //? <+>
!{ a([private]){} } //? <+>
!{ a({private}){} } //? <+>
!{ a([...private]){} } //? <+>
!{ a({...private}){} } //? <+>
!{ a(...private){} } //? <+>
!{ set a(private){} } //? <+>
!{ set a([private]){} } //? <+>
!{ set a({private}){} } //? <+>
!{ set a([...private]){} } //? <+>
!{ set a({...private}){} } //? <+>
!{ set a(...private){} } //? <-> @1:10 -default
!function private(){} //? <+>
!function a(private){} //? <+>
!function a(b = private){} //? <+>
!function a([private]){} //? <+>
!function a({private}){} //? <+>
!function a([...private]){} //? <+>
!function a({...private}){} //? <+>
!function a(...private){} //? <+>
!class private {} //? <-> @1:8
!class a extends private {} //? <-> @1:18
!class a { private(){} } //? <+>
!class a { [private](){} } //? <-> @1:13
!class a { b(private){} } //? <-> @1:14
!class a { b([private]){} } //? <-> @1:15
!class a { b({private}){} } //? <-> @1:15
!class a { b([...private]){} } //? <-> @1:18
!class a { b({...private}){} } //? <-> @1:18
!class a { b(...private){} } //? <-> @1:17
`${private}`; //? <+>
a.private; //? <+>
``.private; //? <+>
private++; //? <+>
++private; //? <+>
private = 0; //? <+>
private *= 0; //? <+>
[private] = []; //? <+>
({private} = {}); //? <+>
({private = 0} = {}); //? <+>
[...private] = []; //? <+>
({...private} = {}); //? <+>
private => {}; //? <+>
(private) => {}; //? <+>
([private]) => {}; //? <+>
({private}) => {}; //? <+>
([...private]) => {}; //? <+>
({...private}) => {}; //? <+>
(...private) => {}; //? <+>
async (private) => {}; //? <+>
async ([private]) => {}; //? <+>
async ({private}) => {}; //? <+>
async ([...private]) => {}; //? <+>
async ({...private}) => {}; //? <+>
async (...private) => {}; //? <+>
private: ; //? <+>
var private; //? <+>
var [private] = []; //? <+>
var {private} = {}; //? <+>
var [...private] = []; //? <+>
var {...private} = {}; //? <+>
let private; //? <+>
let [private] = []; //? <+>
let {private} = {}; //? <+>
let [...private] = []; //? <+>
let {...private} = {}; //? <+>
const private = 0; //? <+>
const [private] = 0; //? <+>
const {private} = 0; //? <+>
const [...private] = 0; //? <+>
const {...private} = 0; //? <+>
function private(){} //? <+>
function a(private){} //? <+>
function a(b = private){} //? <+>
function a([private]){} //? <+>
function a({private}){} //? <+>
function a([...private]){} //? <+>
function a({...private}){} //? <+>
function a(...private){} //? <+>
class private {} //? <-> @1:7
class a extends private {} //? <-> @1:17
class a { private(){} } //? <+>
class a { [private](){} } //? <-> @1:12
class a { b(private){} } //? <-> @1:13
class a { b([private]){} } //? <-> @1:14
class a { b({private}){} } //? <-> @1:14
class a { b([...private]){} } //? <-> @1:17
class a { b({...private}){} } //? <-> @1:17
class a { b(...private){} } //? <-> @1:16

//- invalid_strict_mode_identifier
protected; //? <+>
[protected]; //? <+>
[...protected]; //? <+>
!{protected}; //? <+>
!{protected: 0}; //? <+>
!{[protected]: 0}; //? <+>
!{protected = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ protected(){} } //? <+>
!{ [protected](){} } //? <+>
!{ a(protected){} } //? <+>
!{ a([protected]){} } //? <+>
!{ a({protected}){} } //? <+>
!{ a([...protected]){} } //? <+>
!{ a({...protected}){} } //? <+>
!{ a(...protected){} } //? <+>
!{ set a(protected){} } //? <+>
!{ set a([protected]){} } //? <+>
!{ set a({protected}){} } //? <+>
!{ set a([...protected]){} } //? <+>
!{ set a({...protected}){} } //? <+>
!{ set a(...protected){} } //? <-> @1:10 -default
!function protected(){} //? <+>
!function a(protected){} //? <+>
!function a(b = protected){} //? <+>
!function a([protected]){} //? <+>
!function a({protected}){} //? <+>
!function a([...protected]){} //? <+>
!function a({...protected}){} //? <+>
!function a(...protected){} //? <+>
!class protected {} //? <-> @1:8
!class a extends protected {} //? <-> @1:18
!class a { protected(){} } //? <+>
!class a { [protected](){} } //? <-> @1:13
!class a { b(protected){} } //? <-> @1:14
!class a { b([protected]){} } //? <-> @1:15
!class a { b({protected}){} } //? <-> @1:15
!class a { b([...protected]){} } //? <-> @1:18
!class a { b({...protected}){} } //? <-> @1:18
!class a { b(...protected){} } //? <-> @1:17
`${protected}`; //? <+>
a.protected; //? <+>
``.protected; //? <+>
protected++; //? <+>
++protected; //? <+>
protected = 0; //? <+>
protected *= 0; //? <+>
[protected] = []; //? <+>
({protected} = {}); //? <+>
({protected = 0} = {}); //? <+>
[...protected] = []; //? <+>
({...protected} = {}); //? <+>
protected => {}; //? <+>
(protected) => {}; //? <+>
([protected]) => {}; //? <+>
({protected}) => {}; //? <+>
([...protected]) => {}; //? <+>
({...protected}) => {}; //? <+>
(...protected) => {}; //? <+>
async (protected) => {}; //? <+>
async ([protected]) => {}; //? <+>
async ({protected}) => {}; //? <+>
async ([...protected]) => {}; //? <+>
async ({...protected}) => {}; //? <+>
async (...protected) => {}; //? <+>
protected: ; //? <+>
var protected; //? <+>
var [protected] = []; //? <+>
var {protected} = {}; //? <+>
var [...protected] = []; //? <+>
var {...protected} = {}; //? <+>
let protected; //? <+>
let [protected] = []; //? <+>
let {protected} = {}; //? <+>
let [...protected] = []; //? <+>
let {...protected} = {}; //? <+>
const protected = 0; //? <+>
const [protected] = 0; //? <+>
const {protected} = 0; //? <+>
const [...protected] = 0; //? <+>
const {...protected} = 0; //? <+>
function protected(){} //? <+>
function a(protected){} //? <+>
function a(b = protected){} //? <+>
function a([protected]){} //? <+>
function a({protected}){} //? <+>
function a([...protected]){} //? <+>
function a({...protected}){} //? <+>
function a(...protected){} //? <+>
class protected {} //? <-> @1:7
class a extends protected {} //? <-> @1:17
class a { protected(){} } //? <+>
class a { [protected](){} } //? <-> @1:12
class a { b(protected){} } //? <-> @1:13
class a { b([protected]){} } //? <-> @1:14
class a { b({protected}){} } //? <-> @1:14
class a { b([...protected]){} } //? <-> @1:17
class a { b({...protected}){} } //? <-> @1:17
class a { b(...protected){} } //? <-> @1:16

//- invalid_strict_mode_identifier
public; //? <+>
[public]; //? <+>
[...public]; //? <+>
!{public}; //? <+>
!{public: 0}; //? <+>
!{[public]: 0}; //? <+>
!{public = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ public(){} } //? <+>
!{ [public](){} } //? <+>
!{ a(public){} } //? <+>
!{ a([public]){} } //? <+>
!{ a({public}){} } //? <+>
!{ a([...public]){} } //? <+>
!{ a({...public}){} } //? <+>
!{ a(...public){} } //? <+>
!{ set a(public){} } //? <+>
!{ set a([public]){} } //? <+>
!{ set a({public}){} } //? <+>
!{ set a([...public]){} } //? <+>
!{ set a({...public}){} } //? <+>
!{ set a(...public){} } //? <-> @1:10 -default
!function public(){} //? <+>
!function a(public){} //? <+>
!function a(b = public){} //? <+>
!function a([public]){} //? <+>
!function a({public}){} //? <+>
!function a([...public]){} //? <+>
!function a({...public}){} //? <+>
!function a(...public){} //? <+>
!class public {} //? <-> @1:8
!class a extends public {} //? <-> @1:18
!class a { public(){} } //? <+>
!class a { [public](){} } //? <-> @1:13
!class a { b(public){} } //? <-> @1:14
!class a { b([public]){} } //? <-> @1:15
!class a { b({public}){} } //? <-> @1:15
!class a { b([...public]){} } //? <-> @1:18
!class a { b({...public}){} } //? <-> @1:18
!class a { b(...public){} } //? <-> @1:17
`${public}`; //? <+>
a.public; //? <+>
``.public; //? <+>
public++; //? <+>
++public; //? <+>
public = 0; //? <+>
public *= 0; //? <+>
[public] = []; //? <+>
({public} = {}); //? <+>
({public = 0} = {}); //? <+>
[...public] = []; //? <+>
({...public} = {}); //? <+>
public => {}; //? <+>
(public) => {}; //? <+>
([public]) => {}; //? <+>
({public}) => {}; //? <+>
([...public]) => {}; //? <+>
({...public}) => {}; //? <+>
(...public) => {}; //? <+>
async (public) => {}; //? <+>
async ([public]) => {}; //? <+>
async ({public}) => {}; //? <+>
async ([...public]) => {}; //? <+>
async ({...public}) => {}; //? <+>
async (...public) => {}; //? <+>
public: ; //? <+>
var public; //? <+>
var [public] = []; //? <+>
var {public} = {}; //? <+>
var [...public] = []; //? <+>
var {...public} = {}; //? <+>
let public; //? <+>
let [public] = []; //? <+>
let {public} = {}; //? <+>
let [...public] = []; //? <+>
let {...public} = {}; //? <+>
const public = 0; //? <+>
const [public] = 0; //? <+>
const {public} = 0; //? <+>
const [...public] = 0; //? <+>
const {...public} = 0; //? <+>
function public(){} //? <+>
function a(public){} //? <+>
function a(b = public){} //? <+>
function a([public]){} //? <+>
function a({public}){} //? <+>
function a([...public]){} //? <+>
function a({...public}){} //? <+>
function a(...public){} //? <+>
class public {} //? <-> @1:7
class a extends public {} //? <-> @1:17
class a { public(){} } //? <+>
class a { [public](){} } //? <-> @1:12
class a { b(public){} } //? <-> @1:13
class a { b([public]){} } //? <-> @1:14
class a { b({public}){} } //? <-> @1:14
class a { b([...public]){} } //? <-> @1:17
class a { b({...public}){} } //? <-> @1:17
class a { b(...public){} } //? <-> @1:16

