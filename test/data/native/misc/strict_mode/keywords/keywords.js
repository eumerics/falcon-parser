//- eval_args_in_strict_mode
'use strict'; eval; //? <+>
'use strict'; [eval]; //? <+>
'use strict'; [...eval]; //? <+>
'use strict'; !{eval}; //? <+>
'use strict'; !{eval: 0}; //? <+>
'use strict'; !{[eval]: 0}; //? <+>
'use strict'; !{eval = 0}; //? <-> @1:17
'use strict'; !{ eval(){} } //? <+>
'use strict'; !{ [eval](){} }; //? <+>
'use strict'; !{ a(eval){} } //? <-> @1:20
'use strict'; !{ a([eval]){} } //? <-> @1:21
'use strict'; !{ a({eval}){} } //? <-> @1:21
'use strict'; !{ a([...eval]){} } //? <-> @1:24
'use strict'; !{ a({...eval}){} } //? <-> @1:24
'use strict'; !{ a(...eval){} } //? <-> @1:23
'use strict'; !{ set a(eval){} } //? <-> @1:24
'use strict'; !{ set a([eval]){} } //? <-> @1:25
'use strict'; !{ set a({eval}){} } //? <-> @1:25
'use strict'; !{ set a([...eval]){} } //? <-> @1:28
'use strict'; !{ set a({...eval}){} } //? <-> @1:28
'use strict'; !{ set a(...eval){} } //? <-> @1:24 -default
'use strict'; !function eval(){} //? <-> @1:25
'use strict'; !function a(b = eval){} //? <+>
'use strict'; !function a(eval){} //? <-> @1:27
'use strict'; !function a([eval]){} //? <-> @1:28
'use strict'; !function a({eval}){} //? <-> @1:28
'use strict'; !function a([...eval]){} //? <-> @1:31
'use strict'; !function a({...eval}){} //? <-> @1:31
'use strict'; !function a(...eval){} //? <-> @1:30
'use strict'; `${eval}`; //? <+>
'use strict'; a.eval; //? <+>
'use strict'; ``.eval; //? <+>
'use strict'; eval++; //? <-> @1:15
'use strict'; ++eval; //? <-> @1:17
'use strict'; eval = 0; //? <-> @1:15
'use strict'; eval *= 0; //? <-> @1:15
'use strict'; [eval] = []; //? <-> @1:16
'use strict'; ({eval} = {}); //? <-> @1:17
'use strict'; ({eval = 0} = {}); //? <-> @1:17
'use strict'; [...eval] = []; //? <-> @1:19
'use strict'; ({...eval} = {}); //? <-> @1:20
'use strict'; eval => {}; //? <-> @1:15
'use strict'; (eval) => {}; //? <-> @1:16
'use strict'; ([eval]) => {}; //? <-> @1:17
'use strict'; ({eval}) => {}; //? <-> @1:17
'use strict'; ([...eval]) => {}; //? <-> @1:20
'use strict'; ({...eval}) => {}; //? <-> @1:20
'use strict'; (...eval) => {}; //? <-> @1:19
'use strict'; async (eval) => {}; //? <-> @1:22
'use strict'; async ([eval]) => {}; //? <-> @1:23
'use strict'; async ({eval}) => {}; //? <-> @1:23
'use strict'; async ([...eval]) => {}; //? <-> @1:26
'use strict'; async ({...eval}) => {}; //? <-> @1:26
'use strict'; async (...eval) => {}; //? <-> @1:25
'use strict'; eval: ; //? <+>
'use strict'; var eval; //? <-> @1:19
'use strict'; var [eval] = []; //? <-> @1:20
'use strict'; var {eval} = {}; //? <-> @1:20
'use strict'; var [...eval] = []; //? <-> @1:23
'use strict'; var {...eval}= {}; //? <-> @1:23
'use strict'; let eval; //? <-> @1:19
'use strict'; let [eval] = []; //? <-> @1:20
'use strict'; let {eval} = {}; //? <-> @1:20
'use strict'; let [...eval] = []; //? <-> @1:23
'use strict'; let {...eval} = {}; //? <-> @1:23
'use strict'; const eval = 0; //? <-> @1:21
'use strict'; const [eval] = 0; //? <-> @1:22
'use strict'; const {eval} = 0; //? <-> @1:22
'use strict'; const [...eval] = 0; //? <-> @1:25
'use strict'; const {...eval} = 0; //? <-> @1:25
'use strict'; function eval(){} //? <-> @1:24
'use strict'; function a(eval){} //? <-> @1:26
'use strict'; function a(b = eval){} //? <+>
'use strict'; function a([eval]){} //? <-> @1:27
'use strict'; function a({eval}){} //? <-> @1:27
'use strict'; function a([...eval]){} //? <-> @1:30
'use strict'; function a({...eval}){} //? <-> @1:30
'use strict'; function a(...eval){} //? <-> @1:29
///
function eval(){ 'use strict'; } //? <-> @1:10
function a(eval){ 'use strict'; } //? <-> @1:12
function a(b, eval){ 'use strict'; } //? <-> @1:15
!function eval(){ 'use strict'; } //? <-> @1:11
!function a(eval){ 'use strict'; } //? <-> @1:13
!{ eval(){ 'use strict'; } } //? <+>
!{ a(eval){ 'use strict'; } } //? <-> @1:6
!{ set a(eval){ 'use strict'; } } //? <-> @1:10
eval => { 'use strict'; }; //? <-> @1:1
(eval) => { 'use strict'; }; //? <-> @1:2
async (eval) => { 'use strict'; }; //? <-> @1:8

//- eval_args_in_strict_mode
'use strict'; arguments; //? <+>
'use strict'; [arguments]; //? <+>
'use strict'; [...arguments]; //? <+>
'use strict'; !{arguments}; //? <+>
'use strict'; !{arguments: 0}; //? <+>
'use strict'; !{[arguments]: 0}; //? <+>
'use strict'; !{arguments = 0}; //? <-> @1:17
'use strict'; !{ arguments(){} } //? <+>
'use strict'; !{ [arguments](){} }; //? <+>
'use strict'; !{ a(arguments){} } //? <-> @1:20
'use strict'; !{ a([arguments]){} } //? <-> @1:21
'use strict'; !{ a({arguments}){} } //? <-> @1:21
'use strict'; !{ a([...arguments]){} } //? <-> @1:24
'use strict'; !{ a({...arguments}){} } //? <-> @1:24
'use strict'; !{ a(...arguments){} } //? <-> @1:23
'use strict'; !{ set a(arguments){} } //? <-> @1:24
'use strict'; !{ set a([arguments]){} } //? <-> @1:25
'use strict'; !{ set a({arguments}){} } //? <-> @1:25
'use strict'; !{ set a([...arguments]){} } //? <-> @1:28
'use strict'; !{ set a({...arguments}){} } //? <-> @1:28
'use strict'; !{ set a(...arguments){} } //? <-> @1:24 -default
'use strict'; !function arguments(){} //? <-> @1:25
'use strict'; !function a(b = arguments){} //? <+>
'use strict'; !function a(arguments){} //? <-> @1:27
'use strict'; !function a([arguments]){} //? <-> @1:28
'use strict'; !function a({arguments}){} //? <-> @1:28
'use strict'; !function a([...arguments]){} //? <-> @1:31
'use strict'; !function a({...arguments}){} //? <-> @1:31
'use strict'; !function a(...arguments){} //? <-> @1:30
'use strict'; `${arguments}`; //? <+>
'use strict'; a.arguments; //? <+>
'use strict'; ``.arguments; //? <+>
'use strict'; arguments++; //? <-> @1:15
'use strict'; ++arguments; //? <-> @1:17
'use strict'; arguments = 0; //? <-> @1:15
'use strict'; arguments *= 0; //? <-> @1:15
'use strict'; [arguments] = []; //? <-> @1:16
'use strict'; ({arguments} = {}); //? <-> @1:17
'use strict'; ({arguments = 0} = {}); //? <-> @1:17
'use strict'; [...arguments] = []; //? <-> @1:19
'use strict'; ({...arguments} = {}); //? <-> @1:20
'use strict'; arguments => {}; //? <-> @1:15
'use strict'; (arguments) => {}; //? <-> @1:16
'use strict'; ([arguments]) => {}; //? <-> @1:17
'use strict'; ({arguments}) => {}; //? <-> @1:17
'use strict'; ([...arguments]) => {}; //? <-> @1:20
'use strict'; ({...arguments}) => {}; //? <-> @1:20
'use strict'; (...arguments) => {}; //? <-> @1:19
'use strict'; async (arguments) => {}; //? <-> @1:22
'use strict'; async ([arguments]) => {}; //? <-> @1:23
'use strict'; async ({arguments}) => {}; //? <-> @1:23
'use strict'; async ([...arguments]) => {}; //? <-> @1:26
'use strict'; async ({...arguments}) => {}; //? <-> @1:26
'use strict'; async (...arguments) => {}; //? <-> @1:25
'use strict'; arguments: ; //? <+>
'use strict'; var arguments; //? <-> @1:19
'use strict'; var [arguments] = []; //? <-> @1:20
'use strict'; var {arguments} = {}; //? <-> @1:20
'use strict'; var [...arguments] = []; //? <-> @1:23
'use strict'; var {...arguments}= {}; //? <-> @1:23
'use strict'; let arguments; //? <-> @1:19
'use strict'; let [arguments] = []; //? <-> @1:20
'use strict'; let {arguments} = {}; //? <-> @1:20
'use strict'; let [...arguments] = []; //? <-> @1:23
'use strict'; let {...arguments} = {}; //? <-> @1:23
'use strict'; const arguments = 0; //? <-> @1:21
'use strict'; const [arguments] = 0; //? <-> @1:22
'use strict'; const {arguments} = 0; //? <-> @1:22
'use strict'; const [...arguments] = 0; //? <-> @1:25
'use strict'; const {...arguments} = 0; //? <-> @1:25
'use strict'; function arguments(){} //? <-> @1:24
'use strict'; function a(arguments){} //? <-> @1:26
'use strict'; function a(b = arguments){} //? <+>
'use strict'; function a([arguments]){} //? <-> @1:27
'use strict'; function a({arguments}){} //? <-> @1:27
'use strict'; function a([...arguments]){} //? <-> @1:30
'use strict'; function a({...arguments}){} //? <-> @1:30
'use strict'; function a(...arguments){} //? <-> @1:29
///
function arguments(){ 'use strict'; } //? <-> @1:10
function a(arguments){ 'use strict'; } //? <-> @1:12
function a(b, arguments){ 'use strict'; } //? <-> @1:15
!function arguments(){ 'use strict'; } //? <-> @1:11
!function a(arguments){ 'use strict'; } //? <-> @1:13
!{ arguments(){ 'use strict'; } } //? <+>
!{ a(arguments){ 'use strict'; } } //? <-> @1:6
!{ set a(arguments){ 'use strict'; } } //? <-> @1:10
arguments => { 'use strict'; }; //? <-> @1:1
(arguments) => { 'use strict'; }; //? <-> @1:2
async (arguments) => { 'use strict'; }; //? <-> @1:8

//- yield_in_strict_mode
'use strict'; yield; //? <-> @1:15
'use strict'; [yield]; //? <-> @1:16
'use strict'; [...yield]; //? <-> @1:19
'use strict'; !{yield}; //? <-> @1:17
'use strict'; !{yield: 0}; //? <+>
'use strict'; !{[yield]: 0}; //? <-> @1:18
'use strict'; !{yield = 0}; //? <-> @1:17
'use strict'; !{ yield(){} } //? <+>
'use strict'; !{ [yield](){} }; //? <-> @1:19
'use strict'; !{ a(yield){} } //? <-> @1:20
'use strict'; !{ a([yield]){} } //? <-> @1:21
'use strict'; !{ a({yield}){} } //? <-> @1:21
'use strict'; !{ a([...yield]){} } //? <-> @1:24
'use strict'; !{ a({...yield}){} } //? <-> @1:24
'use strict'; !{ a(...yield){} } //? <-> @1:23
'use strict'; !{ set a(yield){} } //? <-> @1:24
'use strict'; !{ set a([yield]){} } //? <-> @1:25
'use strict'; !{ set a({yield}){} } //? <-> @1:25
'use strict'; !{ set a([...yield]){} } //? <-> @1:28
'use strict'; !{ set a({...yield}){} } //? <-> @1:28
'use strict'; !{ set a(...yield){} } //? <-> @1:24 -default
'use strict'; !function yield(){} //? <-> @1:25
'use strict'; !function a(b = yield){} //? <-> @1:31
'use strict'; !function a(yield){} //? <-> @1:27
'use strict'; !function a([yield]){} //? <-> @1:28
'use strict'; !function a({yield}){} //? <-> @1:28
'use strict'; !function a([...yield]){} //? <-> @1:31
'use strict'; !function a({...yield}){} //? <-> @1:31
'use strict'; !function a(...yield){} //? <-> @1:30
'use strict'; `${yield}`; //? <-> @1:18
'use strict'; a.yield; //? <+>
'use strict'; ``.yield; //? <+>
'use strict'; yield++; //? <-> @1:15
'use strict'; ++yield; //? <-> @1:17
'use strict'; yield = 0; //? <-> @1:15
'use strict'; yield *= 0; //? <-> @1:15
'use strict'; [yield] = []; //? <-> @1:16
'use strict'; ({yield} = {}); //? <-> @1:17
'use strict'; ({yield = 0} = {}); //? <-> @1:17
'use strict'; [...yield] = []; //? <-> @1:19
'use strict'; ({...yield} = {}); //? <-> @1:20
'use strict'; yield => {}; //? <-> @1:15
'use strict'; (yield) => {}; //? <-> @1:16
'use strict'; ([yield]) => {}; //? <-> @1:17
'use strict'; ({yield}) => {}; //? <-> @1:17
'use strict'; ([...yield]) => {}; //? <-> @1:20
'use strict'; ({...yield}) => {}; //? <-> @1:20
'use strict'; (...yield) => {}; //? <-> @1:19
'use strict'; async (yield) => {}; //? <-> @1:22
'use strict'; async ([yield]) => {}; //? <-> @1:23
'use strict'; async ({yield}) => {}; //? <-> @1:23
'use strict'; async ([...yield]) => {}; //? <-> @1:26
'use strict'; async ({...yield}) => {}; //? <-> @1:26
'use strict'; async (...yield) => {}; //? <-> @1:25
'use strict'; yield: ; //? <-> @1:15
'use strict'; var yield; //? <-> @1:19
'use strict'; var [yield] = []; //? <-> @1:20
'use strict'; var {yield} = {}; //? <-> @1:20
'use strict'; var [...yield] = []; //? <-> @1:23
'use strict'; var {...yield}= {}; //? <-> @1:23
'use strict'; let yield; //? <-> @1:19
'use strict'; let [yield] = []; //? <-> @1:20
'use strict'; let {yield} = {}; //? <-> @1:20
'use strict'; let [...yield] = []; //? <-> @1:23
'use strict'; let {...yield} = {}; //? <-> @1:23
'use strict'; const yield = 0; //? <-> @1:21
'use strict'; const [yield] = 0; //? <-> @1:22
'use strict'; const {yield} = 0; //? <-> @1:22
'use strict'; const [...yield] = 0; //? <-> @1:25
'use strict'; const {...yield} = 0; //? <-> @1:25
'use strict'; function yield(){} //? <-> @1:24
'use strict'; function a(yield){} //? <-> @1:26
'use strict'; function a(b = yield){} //? <-> @1:30
'use strict'; function a([yield]){} //? <-> @1:27
'use strict'; function a({yield}){} //? <-> @1:27
'use strict'; function a([...yield]){} //? <-> @1:30
'use strict'; function a({...yield}){} //? <-> @1:30
'use strict'; function a(...yield){} //? <-> @1:29
///
function yield(){ 'use strict'; } //? <-> @1:10
function a(yield){ 'use strict'; } //? <-> @1:12
function a(b, yield){ 'use strict'; } //? <-> @1:15
!function yield(){ 'use strict'; } //? <-> @1:11
!function a(yield){ 'use strict'; } //? <-> @1:13
!{ yield(){ 'use strict'; } } //? <+>
!{ a(yield){ 'use strict'; } } //? <-> @1:6
!{ set a(yield){ 'use strict'; } } //? <-> @1:10
yield => { 'use strict'; }; //? <-> @1:1
(yield) => { 'use strict'; }; //? <-> @1:2
async (yield) => { 'use strict'; }; //? <-> @1:8

//- await_in_module
'use strict'; await; //? <+>
'use strict'; [await]; //? <+>
'use strict'; [...await]; //? <+>
'use strict'; !{await}; //? <+>
'use strict'; !{await: 0}; //? <+>
'use strict'; !{[await]: 0}; //? <+>
'use strict'; !{await = 0}; //? <-> @1:17 -invalid_cover_grammar
'use strict'; !{ await(){} } //? <+>
'use strict'; !{ [await](){} }; //? <+>
'use strict'; !{ a(await){} } //? <+>
'use strict'; !{ a([await]){} } //? <+>
'use strict'; !{ a({await}){} } //? <+>
'use strict'; !{ a([...await]){} } //? <+>
'use strict'; !{ a({...await}){} } //? <+>
'use strict'; !{ a(...await){} } //? <+>
'use strict'; !{ set a(await){} } //? <+>
'use strict'; !{ set a([await]){} } //? <+>
'use strict'; !{ set a({await}){} } //? <+>
'use strict'; !{ set a([...await]){} } //? <+>
'use strict'; !{ set a({...await}){} } //? <+>
'use strict'; !{ set a(...await){} } //? <-> @1:24 -default
'use strict'; !function await(){} //? <+>
'use strict'; !function a(b = await){} //? <+>
'use strict'; !function a(await){} //? <+>
'use strict'; !function a([await]){} //? <+>
'use strict'; !function a({await}){} //? <+>
'use strict'; !function a([...await]){} //? <+>
'use strict'; !function a({...await}){} //? <+>
'use strict'; !function a(...await){} //? <+>
'use strict'; `${await}`; //? <+>
'use strict'; a.await; //? <+>
'use strict'; ``.await; //? <+>
'use strict'; await++; //? <+>
'use strict'; ++await; //? <+>
'use strict'; await = 0; //? <+>
'use strict'; await *= 0; //? <+>
'use strict'; [await] = []; //? <+>
'use strict'; ({await} = {}); //? <+>
'use strict'; ({await = 0} = {}); //? <+>
'use strict'; [...await] = []; //? <+>
'use strict'; ({...await} = {}); //? <+>
'use strict'; await => {}; //? <+>
'use strict'; (await) => {}; //? <+>
'use strict'; ([await]) => {}; //? <+>
'use strict'; ({await}) => {}; //? <+>
'use strict'; ([...await]) => {}; //? <+>
'use strict'; ({...await}) => {}; //? <+>
'use strict'; (...await) => {}; //? <+>
'use strict'; async (await) => {}; //? <-> @1:22 -yield_await_in_arrow_params
'use strict'; async ([await]) => {}; //? <-> @1:23 -yield_await_in_arrow_params
'use strict'; async ({await}) => {}; //? <-> @1:23 -yield_await_in_arrow_params
'use strict'; async ([...await]) => {}; //? <-> @1:26 -yield_await_in_arrow_params
'use strict'; async ({...await}) => {}; //? <-> @1:26 -yield_await_in_arrow_params
'use strict'; async (...await) => {}; //? <-> @1:25 -yield_await_in_arrow_params
'use strict'; await: ; //? <+>
'use strict'; var await; //? <+>
'use strict'; var [await] = []; //? <+>
'use strict'; var {await} = {}; //? <+>
'use strict'; var [...await] = []; //? <+>
'use strict'; var {...await}= {}; //? <+>
'use strict'; let await; //? <+>
'use strict'; let [await] = []; //? <+>
'use strict'; let {await} = {}; //? <+>
'use strict'; let [...await] = []; //? <+>
'use strict'; let {...await} = {}; //? <+>
'use strict'; const await = 0; //? <+>
'use strict'; const [await] = 0; //? <+>
'use strict'; const {await} = 0; //? <+>
'use strict'; const [...await] = 0; //? <+>
'use strict'; const {...await} = 0; //? <+>
'use strict'; function await(){} //? <+>
'use strict'; function a(await){} //? <+>
'use strict'; function a(b = await){} //? <+>
'use strict'; function a([await]){} //? <+>
'use strict'; function a({await}){} //? <+>
'use strict'; function a([...await]){} //? <+>
'use strict'; function a({...await}){} //? <+>
'use strict'; function a(...await){} //? <+>
///
function await(){ 'use strict'; } //? <+>
function a(await){ 'use strict'; } //? <+>
function a(b, await){ 'use strict'; } //? <+>
!function await(){ 'use strict'; } //? <+>
!function a(await){ 'use strict'; } //? <+>
!{ await(){ 'use strict'; } } //? <+>
!{ a(await){ 'use strict'; } } //? <+>
!{ set a(await){ 'use strict'; } } //? <+>
await => { 'use strict'; }; //? <+>
(await) => { 'use strict'; }; //? <+>
async (await) => { 'use strict'; }; //? <-> @1:8 -yield_await_in_arrow_params

//- invalid_strict_mode_identifier
'use strict'; let; //? <-> @1:15
'use strict'; [let]; //? <-> @1:16
'use strict'; [...let]; //? <-> @1:19
'use strict'; !{let}; //? <-> @1:17
'use strict'; !{let: 0}; //? <+>
'use strict'; !{[let]: 0}; //? <-> @1:18
'use strict'; !{let = 0}; //? <-> @1:17
'use strict'; !{ let(){} } //? <+>
'use strict'; !{ [let](){} }; //? <-> @1:19
'use strict'; !{ a(let){} } //? <-> @1:20
'use strict'; !{ a([let]){} } //? <-> @1:21
'use strict'; !{ a({let}){} } //? <-> @1:21
'use strict'; !{ a([...let]){} } //? <-> @1:24
'use strict'; !{ a({...let}){} } //? <-> @1:24
'use strict'; !{ a(...let){} } //? <-> @1:23
'use strict'; !{ set a(let){} } //? <-> @1:24
'use strict'; !{ set a([let]){} } //? <-> @1:25
'use strict'; !{ set a({let}){} } //? <-> @1:25
'use strict'; !{ set a([...let]){} } //? <-> @1:28
'use strict'; !{ set a({...let}){} } //? <-> @1:28
'use strict'; !{ set a(...let){} } //? <-> @1:24 -default
'use strict'; !function let(){} //? <-> @1:25
'use strict'; !function a(b = let){} //? <-> @1:31
'use strict'; !function a(let){} //? <-> @1:27
'use strict'; !function a([let]){} //? <-> @1:28
'use strict'; !function a({let}){} //? <-> @1:28
'use strict'; !function a([...let]){} //? <-> @1:31
'use strict'; !function a({...let}){} //? <-> @1:31
'use strict'; !function a(...let){} //? <-> @1:30
'use strict'; `${let}`; //? <-> @1:18
'use strict'; a.let; //? <+>
'use strict'; ``.let; //? <+>
'use strict'; let++; //? <-> @1:15
'use strict'; ++let; //? <-> @1:17
'use strict'; let = 0; //? <-> @1:15
'use strict'; let *= 0; //? <-> @1:15
'use strict'; [let] = []; //? <-> @1:16
'use strict'; ({let} = {}); //? <-> @1:17
'use strict'; ({let = 0} = {}); //? <-> @1:17
'use strict'; [...let] = []; //? <-> @1:19
'use strict'; ({...let} = {}); //? <-> @1:20
'use strict'; let => {}; //? <-> @1:15
'use strict'; (let) => {}; //? <-> @1:16
'use strict'; ([let]) => {}; //? <-> @1:17
'use strict'; ({let}) => {}; //? <-> @1:17
'use strict'; ([...let]) => {}; //? <-> @1:20
'use strict'; ({...let}) => {}; //? <-> @1:20
'use strict'; (...let) => {}; //? <-> @1:19
'use strict'; async (let) => {}; //? <-> @1:22
'use strict'; async ([let]) => {}; //? <-> @1:23
'use strict'; async ({let}) => {}; //? <-> @1:23
'use strict'; async ([...let]) => {}; //? <-> @1:26
'use strict'; async ({...let}) => {}; //? <-> @1:26
'use strict'; async (...let) => {}; //? <-> @1:25
'use strict'; let: ; //? <-> @1:15
'use strict'; var let; //? <-> @1:19
'use strict'; var [let] = []; //? <-> @1:20
'use strict'; var {let} = {}; //? <-> @1:20
'use strict'; var [...let] = []; //? <-> @1:23
'use strict'; var {...let}= {}; //? <-> @1:23
'use strict'; let let; //? <-> @1:19 -let_in_lexical
'use strict'; let [let] = []; //? <-> @1:20 -let_in_lexical
'use strict'; let {let} = {}; //? <-> @1:20 -let_in_lexical
'use strict'; let [...let] = []; //? <-> @1:23 -let_in_lexical
'use strict'; let {...let} = {}; //? <-> @1:23 -let_in_lexical
'use strict'; const let = 0; //? <-> @1:21 -let_in_lexical
'use strict'; const [let] = 0; //? <-> @1:22 -let_in_lexical
'use strict'; const {let} = 0; //? <-> @1:22 -let_in_lexical
'use strict'; const [...let] = 0; //? <-> @1:25 -let_in_lexical
'use strict'; const {...let} = 0; //? <-> @1:25 -let_in_lexical
'use strict'; function let(){} //? <-> @1:24
'use strict'; function a(let){} //? <-> @1:26
'use strict'; function a(b = let){} //? <-> @1:30
'use strict'; function a([let]){} //? <-> @1:27
'use strict'; function a({let}){} //? <-> @1:27
'use strict'; function a([...let]){} //? <-> @1:30
'use strict'; function a({...let}){} //? <-> @1:30
'use strict'; function a(...let){} //? <-> @1:29
///
function let(){ 'use strict'; } //? <-> @1:10
function a(let){ 'use strict'; } //? <-> @1:12
function a(b, let){ 'use strict'; } //? <-> @1:15
!function let(){ 'use strict'; } //? <-> @1:11
!function a(let){ 'use strict'; } //? <-> @1:13
!{ let(){ 'use strict'; } } //? <+>
!{ a(let){ 'use strict'; } } //? <-> @1:6
!{ set a(let){ 'use strict'; } } //? <-> @1:10
let => { 'use strict'; }; //? <-> @1:1
(let) => { 'use strict'; }; //? <-> @1:2
async (let) => { 'use strict'; }; //? <-> @1:8

//- invalid_strict_mode_identifier
'use strict'; static; //? <-> @1:15
'use strict'; [static]; //? <-> @1:16
'use strict'; [...static]; //? <-> @1:19
'use strict'; !{static}; //? <-> @1:17
'use strict'; !{static: 0}; //? <+>
'use strict'; !{[static]: 0}; //? <-> @1:18
'use strict'; !{static = 0}; //? <-> @1:17
'use strict'; !{ static(){} } //? <+>
'use strict'; !{ [static](){} }; //? <-> @1:19
'use strict'; !{ a(static){} } //? <-> @1:20
'use strict'; !{ a([static]){} } //? <-> @1:21
'use strict'; !{ a({static}){} } //? <-> @1:21
'use strict'; !{ a([...static]){} } //? <-> @1:24
'use strict'; !{ a({...static}){} } //? <-> @1:24
'use strict'; !{ a(...static){} } //? <-> @1:23
'use strict'; !{ set a(static){} } //? <-> @1:24
'use strict'; !{ set a([static]){} } //? <-> @1:25
'use strict'; !{ set a({static}){} } //? <-> @1:25
'use strict'; !{ set a([...static]){} } //? <-> @1:28
'use strict'; !{ set a({...static}){} } //? <-> @1:28
'use strict'; !{ set a(...static){} } //? <-> @1:24 -default
'use strict'; !function static(){} //? <-> @1:25
'use strict'; !function a(b = static){} //? <-> @1:31
'use strict'; !function a(static){} //? <-> @1:27
'use strict'; !function a([static]){} //? <-> @1:28
'use strict'; !function a({static}){} //? <-> @1:28
'use strict'; !function a([...static]){} //? <-> @1:31
'use strict'; !function a({...static}){} //? <-> @1:31
'use strict'; !function a(...static){} //? <-> @1:30
'use strict'; `${static}`; //? <-> @1:18
'use strict'; a.static; //? <+>
'use strict'; ``.static; //? <+>
'use strict'; static++; //? <-> @1:15
'use strict'; ++static; //? <-> @1:17
'use strict'; static = 0; //? <-> @1:15
'use strict'; static *= 0; //? <-> @1:15
'use strict'; [static] = []; //? <-> @1:16
'use strict'; ({static} = {}); //? <-> @1:17
'use strict'; ({static = 0} = {}); //? <-> @1:17
'use strict'; [...static] = []; //? <-> @1:19
'use strict'; ({...static} = {}); //? <-> @1:20
'use strict'; static => {}; //? <-> @1:15
'use strict'; (static) => {}; //? <-> @1:16
'use strict'; ([static]) => {}; //? <-> @1:17
'use strict'; ({static}) => {}; //? <-> @1:17
'use strict'; ([...static]) => {}; //? <-> @1:20
'use strict'; ({...static}) => {}; //? <-> @1:20
'use strict'; (...static) => {}; //? <-> @1:19
'use strict'; async (static) => {}; //? <-> @1:22
'use strict'; async ([static]) => {}; //? <-> @1:23
'use strict'; async ({static}) => {}; //? <-> @1:23
'use strict'; async ([...static]) => {}; //? <-> @1:26
'use strict'; async ({...static}) => {}; //? <-> @1:26
'use strict'; async (...static) => {}; //? <-> @1:25
'use strict'; static: ; //? <-> @1:15
'use strict'; var static; //? <-> @1:19
'use strict'; var [static] = []; //? <-> @1:20
'use strict'; var {static} = {}; //? <-> @1:20
'use strict'; var [...static] = []; //? <-> @1:23
'use strict'; var {...static}= {}; //? <-> @1:23
'use strict'; let static; //? <-> @1:19
'use strict'; let [static] = []; //? <-> @1:20
'use strict'; let {static} = {}; //? <-> @1:20
'use strict'; let [...static] = []; //? <-> @1:23
'use strict'; let {...static} = {}; //? <-> @1:23
'use strict'; const static = 0; //? <-> @1:21
'use strict'; const [static] = 0; //? <-> @1:22
'use strict'; const {static} = 0; //? <-> @1:22
'use strict'; const [...static] = 0; //? <-> @1:25
'use strict'; const {...static} = 0; //? <-> @1:25
'use strict'; function static(){} //? <-> @1:24
'use strict'; function a(static){} //? <-> @1:26
'use strict'; function a(b = static){} //? <-> @1:30
'use strict'; function a([static]){} //? <-> @1:27
'use strict'; function a({static}){} //? <-> @1:27
'use strict'; function a([...static]){} //? <-> @1:30
'use strict'; function a({...static}){} //? <-> @1:30
'use strict'; function a(...static){} //? <-> @1:29
///
function static(){ 'use strict'; } //? <-> @1:10
function a(static){ 'use strict'; } //? <-> @1:12
function a(b, static){ 'use strict'; } //? <-> @1:15
!function static(){ 'use strict'; } //? <-> @1:11
!function a(static){ 'use strict'; } //? <-> @1:13
!{ static(){ 'use strict'; } } //? <+>
!{ a(static){ 'use strict'; } } //? <-> @1:6
!{ set a(static){ 'use strict'; } } //? <-> @1:10
static => { 'use strict'; }; //? <-> @1:1
(static) => { 'use strict'; }; //? <-> @1:2
async (static) => { 'use strict'; }; //? <-> @1:8

//- invalid_strict_mode_identifier
'use strict'; implements; //? <-> @1:15
'use strict'; [implements]; //? <-> @1:16
'use strict'; [...implements]; //? <-> @1:19
'use strict'; !{implements}; //? <-> @1:17
'use strict'; !{implements: 0}; //? <+>
'use strict'; !{[implements]: 0}; //? <-> @1:18
'use strict'; !{implements = 0}; //? <-> @1:17
'use strict'; !{ implements(){} } //? <+>
'use strict'; !{ [implements](){} }; //? <-> @1:19
'use strict'; !{ a(implements){} } //? <-> @1:20
'use strict'; !{ a([implements]){} } //? <-> @1:21
'use strict'; !{ a({implements}){} } //? <-> @1:21
'use strict'; !{ a([...implements]){} } //? <-> @1:24
'use strict'; !{ a({...implements}){} } //? <-> @1:24
'use strict'; !{ a(...implements){} } //? <-> @1:23
'use strict'; !{ set a(implements){} } //? <-> @1:24
'use strict'; !{ set a([implements]){} } //? <-> @1:25
'use strict'; !{ set a({implements}){} } //? <-> @1:25
'use strict'; !{ set a([...implements]){} } //? <-> @1:28
'use strict'; !{ set a({...implements}){} } //? <-> @1:28
'use strict'; !{ set a(...implements){} } //? <-> @1:24 -default
'use strict'; !function implements(){} //? <-> @1:25
'use strict'; !function a(b = implements){} //? <-> @1:31
'use strict'; !function a(implements){} //? <-> @1:27
'use strict'; !function a([implements]){} //? <-> @1:28
'use strict'; !function a({implements}){} //? <-> @1:28
'use strict'; !function a([...implements]){} //? <-> @1:31
'use strict'; !function a({...implements}){} //? <-> @1:31
'use strict'; !function a(...implements){} //? <-> @1:30
'use strict'; `${implements}`; //? <-> @1:18
'use strict'; a.implements; //? <+>
'use strict'; ``.implements; //? <+>
'use strict'; implements++; //? <-> @1:15
'use strict'; ++implements; //? <-> @1:17
'use strict'; implements = 0; //? <-> @1:15
'use strict'; implements *= 0; //? <-> @1:15
'use strict'; [implements] = []; //? <-> @1:16
'use strict'; ({implements} = {}); //? <-> @1:17
'use strict'; ({implements = 0} = {}); //? <-> @1:17
'use strict'; [...implements] = []; //? <-> @1:19
'use strict'; ({...implements} = {}); //? <-> @1:20
'use strict'; implements => {}; //? <-> @1:15
'use strict'; (implements) => {}; //? <-> @1:16
'use strict'; ([implements]) => {}; //? <-> @1:17
'use strict'; ({implements}) => {}; //? <-> @1:17
'use strict'; ([...implements]) => {}; //? <-> @1:20
'use strict'; ({...implements}) => {}; //? <-> @1:20
'use strict'; (...implements) => {}; //? <-> @1:19
'use strict'; async (implements) => {}; //? <-> @1:22
'use strict'; async ([implements]) => {}; //? <-> @1:23
'use strict'; async ({implements}) => {}; //? <-> @1:23
'use strict'; async ([...implements]) => {}; //? <-> @1:26
'use strict'; async ({...implements}) => {}; //? <-> @1:26
'use strict'; async (...implements) => {}; //? <-> @1:25
'use strict'; implements: ; //? <-> @1:15
'use strict'; var implements; //? <-> @1:19
'use strict'; var [implements] = []; //? <-> @1:20
'use strict'; var {implements} = {}; //? <-> @1:20
'use strict'; var [...implements] = []; //? <-> @1:23
'use strict'; var {...implements}= {}; //? <-> @1:23
'use strict'; let implements; //? <-> @1:19
'use strict'; let [implements] = []; //? <-> @1:20
'use strict'; let {implements} = {}; //? <-> @1:20
'use strict'; let [...implements] = []; //? <-> @1:23
'use strict'; let {...implements} = {}; //? <-> @1:23
'use strict'; const implements = 0; //? <-> @1:21
'use strict'; const [implements] = 0; //? <-> @1:22
'use strict'; const {implements} = 0; //? <-> @1:22
'use strict'; const [...implements] = 0; //? <-> @1:25
'use strict'; const {...implements} = 0; //? <-> @1:25
'use strict'; function implements(){} //? <-> @1:24
'use strict'; function a(implements){} //? <-> @1:26
'use strict'; function a(b = implements){} //? <-> @1:30
'use strict'; function a([implements]){} //? <-> @1:27
'use strict'; function a({implements}){} //? <-> @1:27
'use strict'; function a([...implements]){} //? <-> @1:30
'use strict'; function a({...implements}){} //? <-> @1:30
'use strict'; function a(...implements){} //? <-> @1:29
///
function implements(){ 'use strict'; } //? <-> @1:10
function a(implements){ 'use strict'; } //? <-> @1:12
function a(b, implements){ 'use strict'; } //? <-> @1:15
!function implements(){ 'use strict'; } //? <-> @1:11
!function a(implements){ 'use strict'; } //? <-> @1:13
!{ implements(){ 'use strict'; } } //? <+>
!{ a(implements){ 'use strict'; } } //? <-> @1:6
!{ set a(implements){ 'use strict'; } } //? <-> @1:10
implements => { 'use strict'; }; //? <-> @1:1
(implements) => { 'use strict'; }; //? <-> @1:2
async (implements) => { 'use strict'; }; //? <-> @1:8

//- invalid_strict_mode_identifier
'use strict'; interface; //? <-> @1:15
'use strict'; [interface]; //? <-> @1:16
'use strict'; [...interface]; //? <-> @1:19
'use strict'; !{interface}; //? <-> @1:17
'use strict'; !{interface: 0}; //? <+>
'use strict'; !{[interface]: 0}; //? <-> @1:18
'use strict'; !{interface = 0}; //? <-> @1:17
'use strict'; !{ interface(){} } //? <+>
'use strict'; !{ [interface](){} }; //? <-> @1:19
'use strict'; !{ a(interface){} } //? <-> @1:20
'use strict'; !{ a([interface]){} } //? <-> @1:21
'use strict'; !{ a({interface}){} } //? <-> @1:21
'use strict'; !{ a([...interface]){} } //? <-> @1:24
'use strict'; !{ a({...interface}){} } //? <-> @1:24
'use strict'; !{ a(...interface){} } //? <-> @1:23
'use strict'; !{ set a(interface){} } //? <-> @1:24
'use strict'; !{ set a([interface]){} } //? <-> @1:25
'use strict'; !{ set a({interface}){} } //? <-> @1:25
'use strict'; !{ set a([...interface]){} } //? <-> @1:28
'use strict'; !{ set a({...interface}){} } //? <-> @1:28
'use strict'; !{ set a(...interface){} } //? <-> @1:24 -default
'use strict'; !function interface(){} //? <-> @1:25
'use strict'; !function a(b = interface){} //? <-> @1:31
'use strict'; !function a(interface){} //? <-> @1:27
'use strict'; !function a([interface]){} //? <-> @1:28
'use strict'; !function a({interface}){} //? <-> @1:28
'use strict'; !function a([...interface]){} //? <-> @1:31
'use strict'; !function a({...interface}){} //? <-> @1:31
'use strict'; !function a(...interface){} //? <-> @1:30
'use strict'; `${interface}`; //? <-> @1:18
'use strict'; a.interface; //? <+>
'use strict'; ``.interface; //? <+>
'use strict'; interface++; //? <-> @1:15
'use strict'; ++interface; //? <-> @1:17
'use strict'; interface = 0; //? <-> @1:15
'use strict'; interface *= 0; //? <-> @1:15
'use strict'; [interface] = []; //? <-> @1:16
'use strict'; ({interface} = {}); //? <-> @1:17
'use strict'; ({interface = 0} = {}); //? <-> @1:17
'use strict'; [...interface] = []; //? <-> @1:19
'use strict'; ({...interface} = {}); //? <-> @1:20
'use strict'; interface => {}; //? <-> @1:15
'use strict'; (interface) => {}; //? <-> @1:16
'use strict'; ([interface]) => {}; //? <-> @1:17
'use strict'; ({interface}) => {}; //? <-> @1:17
'use strict'; ([...interface]) => {}; //? <-> @1:20
'use strict'; ({...interface}) => {}; //? <-> @1:20
'use strict'; (...interface) => {}; //? <-> @1:19
'use strict'; async (interface) => {}; //? <-> @1:22
'use strict'; async ([interface]) => {}; //? <-> @1:23
'use strict'; async ({interface}) => {}; //? <-> @1:23
'use strict'; async ([...interface]) => {}; //? <-> @1:26
'use strict'; async ({...interface}) => {}; //? <-> @1:26
'use strict'; async (...interface) => {}; //? <-> @1:25
'use strict'; interface: ; //? <-> @1:15
'use strict'; var interface; //? <-> @1:19
'use strict'; var [interface] = []; //? <-> @1:20
'use strict'; var {interface} = {}; //? <-> @1:20
'use strict'; var [...interface] = []; //? <-> @1:23
'use strict'; var {...interface}= {}; //? <-> @1:23
'use strict'; let interface; //? <-> @1:19
'use strict'; let [interface] = []; //? <-> @1:20
'use strict'; let {interface} = {}; //? <-> @1:20
'use strict'; let [...interface] = []; //? <-> @1:23
'use strict'; let {...interface} = {}; //? <-> @1:23
'use strict'; const interface = 0; //? <-> @1:21
'use strict'; const [interface] = 0; //? <-> @1:22
'use strict'; const {interface} = 0; //? <-> @1:22
'use strict'; const [...interface] = 0; //? <-> @1:25
'use strict'; const {...interface} = 0; //? <-> @1:25
'use strict'; function interface(){} //? <-> @1:24
'use strict'; function a(interface){} //? <-> @1:26
'use strict'; function a(b = interface){} //? <-> @1:30
'use strict'; function a([interface]){} //? <-> @1:27
'use strict'; function a({interface}){} //? <-> @1:27
'use strict'; function a([...interface]){} //? <-> @1:30
'use strict'; function a({...interface}){} //? <-> @1:30
'use strict'; function a(...interface){} //? <-> @1:29
///
function interface(){ 'use strict'; } //? <-> @1:10
function a(interface){ 'use strict'; } //? <-> @1:12
function a(b, interface){ 'use strict'; } //? <-> @1:15
!function interface(){ 'use strict'; } //? <-> @1:11
!function a(interface){ 'use strict'; } //? <-> @1:13
!{ interface(){ 'use strict'; } } //? <+>
!{ a(interface){ 'use strict'; } } //? <-> @1:6
!{ set a(interface){ 'use strict'; } } //? <-> @1:10
interface => { 'use strict'; }; //? <-> @1:1
(interface) => { 'use strict'; }; //? <-> @1:2
async (interface) => { 'use strict'; }; //? <-> @1:8

//- invalid_strict_mode_identifier
'use strict'; package; //? <-> @1:15
'use strict'; [package]; //? <-> @1:16
'use strict'; [...package]; //? <-> @1:19
'use strict'; !{package}; //? <-> @1:17
'use strict'; !{package: 0}; //? <+>
'use strict'; !{[package]: 0}; //? <-> @1:18
'use strict'; !{package = 0}; //? <-> @1:17
'use strict'; !{ package(){} } //? <+>
'use strict'; !{ [package](){} }; //? <-> @1:19
'use strict'; !{ a(package){} } //? <-> @1:20
'use strict'; !{ a([package]){} } //? <-> @1:21
'use strict'; !{ a({package}){} } //? <-> @1:21
'use strict'; !{ a([...package]){} } //? <-> @1:24
'use strict'; !{ a({...package}){} } //? <-> @1:24
'use strict'; !{ a(...package){} } //? <-> @1:23
'use strict'; !{ set a(package){} } //? <-> @1:24
'use strict'; !{ set a([package]){} } //? <-> @1:25
'use strict'; !{ set a({package}){} } //? <-> @1:25
'use strict'; !{ set a([...package]){} } //? <-> @1:28
'use strict'; !{ set a({...package}){} } //? <-> @1:28
'use strict'; !{ set a(...package){} } //? <-> @1:24 -default
'use strict'; !function package(){} //? <-> @1:25
'use strict'; !function a(b = package){} //? <-> @1:31
'use strict'; !function a(package){} //? <-> @1:27
'use strict'; !function a([package]){} //? <-> @1:28
'use strict'; !function a({package}){} //? <-> @1:28
'use strict'; !function a([...package]){} //? <-> @1:31
'use strict'; !function a({...package}){} //? <-> @1:31
'use strict'; !function a(...package){} //? <-> @1:30
'use strict'; `${package}`; //? <-> @1:18
'use strict'; a.package; //? <+>
'use strict'; ``.package; //? <+>
'use strict'; package++; //? <-> @1:15
'use strict'; ++package; //? <-> @1:17
'use strict'; package = 0; //? <-> @1:15
'use strict'; package *= 0; //? <-> @1:15
'use strict'; [package] = []; //? <-> @1:16
'use strict'; ({package} = {}); //? <-> @1:17
'use strict'; ({package = 0} = {}); //? <-> @1:17
'use strict'; [...package] = []; //? <-> @1:19
'use strict'; ({...package} = {}); //? <-> @1:20
'use strict'; package => {}; //? <-> @1:15
'use strict'; (package) => {}; //? <-> @1:16
'use strict'; ([package]) => {}; //? <-> @1:17
'use strict'; ({package}) => {}; //? <-> @1:17
'use strict'; ([...package]) => {}; //? <-> @1:20
'use strict'; ({...package}) => {}; //? <-> @1:20
'use strict'; (...package) => {}; //? <-> @1:19
'use strict'; async (package) => {}; //? <-> @1:22
'use strict'; async ([package]) => {}; //? <-> @1:23
'use strict'; async ({package}) => {}; //? <-> @1:23
'use strict'; async ([...package]) => {}; //? <-> @1:26
'use strict'; async ({...package}) => {}; //? <-> @1:26
'use strict'; async (...package) => {}; //? <-> @1:25
'use strict'; package: ; //? <-> @1:15
'use strict'; var package; //? <-> @1:19
'use strict'; var [package] = []; //? <-> @1:20
'use strict'; var {package} = {}; //? <-> @1:20
'use strict'; var [...package] = []; //? <-> @1:23
'use strict'; var {...package}= {}; //? <-> @1:23
'use strict'; let package; //? <-> @1:19
'use strict'; let [package] = []; //? <-> @1:20
'use strict'; let {package} = {}; //? <-> @1:20
'use strict'; let [...package] = []; //? <-> @1:23
'use strict'; let {...package} = {}; //? <-> @1:23
'use strict'; const package = 0; //? <-> @1:21
'use strict'; const [package] = 0; //? <-> @1:22
'use strict'; const {package} = 0; //? <-> @1:22
'use strict'; const [...package] = 0; //? <-> @1:25
'use strict'; const {...package} = 0; //? <-> @1:25
'use strict'; function package(){} //? <-> @1:24
'use strict'; function a(package){} //? <-> @1:26
'use strict'; function a(b = package){} //? <-> @1:30
'use strict'; function a([package]){} //? <-> @1:27
'use strict'; function a({package}){} //? <-> @1:27
'use strict'; function a([...package]){} //? <-> @1:30
'use strict'; function a({...package}){} //? <-> @1:30
'use strict'; function a(...package){} //? <-> @1:29
///
function package(){ 'use strict'; } //? <-> @1:10
function a(package){ 'use strict'; } //? <-> @1:12
function a(b, package){ 'use strict'; } //? <-> @1:15
!function package(){ 'use strict'; } //? <-> @1:11
!function a(package){ 'use strict'; } //? <-> @1:13
!{ package(){ 'use strict'; } } //? <+>
!{ a(package){ 'use strict'; } } //? <-> @1:6
!{ set a(package){ 'use strict'; } } //? <-> @1:10
package => { 'use strict'; }; //? <-> @1:1
(package) => { 'use strict'; }; //? <-> @1:2
async (package) => { 'use strict'; }; //? <-> @1:8

//- invalid_strict_mode_identifier
'use strict'; private; //? <-> @1:15
'use strict'; [private]; //? <-> @1:16
'use strict'; [...private]; //? <-> @1:19
'use strict'; !{private}; //? <-> @1:17
'use strict'; !{private: 0}; //? <+>
'use strict'; !{[private]: 0}; //? <-> @1:18
'use strict'; !{private = 0}; //? <-> @1:17
'use strict'; !{ private(){} } //? <+>
'use strict'; !{ [private](){} }; //? <-> @1:19
'use strict'; !{ a(private){} } //? <-> @1:20
'use strict'; !{ a([private]){} } //? <-> @1:21
'use strict'; !{ a({private}){} } //? <-> @1:21
'use strict'; !{ a([...private]){} } //? <-> @1:24
'use strict'; !{ a({...private}){} } //? <-> @1:24
'use strict'; !{ a(...private){} } //? <-> @1:23
'use strict'; !{ set a(private){} } //? <-> @1:24
'use strict'; !{ set a([private]){} } //? <-> @1:25
'use strict'; !{ set a({private}){} } //? <-> @1:25
'use strict'; !{ set a([...private]){} } //? <-> @1:28
'use strict'; !{ set a({...private}){} } //? <-> @1:28
'use strict'; !{ set a(...private){} } //? <-> @1:24 -default
'use strict'; !function private(){} //? <-> @1:25
'use strict'; !function a(b = private){} //? <-> @1:31
'use strict'; !function a(private){} //? <-> @1:27
'use strict'; !function a([private]){} //? <-> @1:28
'use strict'; !function a({private}){} //? <-> @1:28
'use strict'; !function a([...private]){} //? <-> @1:31
'use strict'; !function a({...private}){} //? <-> @1:31
'use strict'; !function a(...private){} //? <-> @1:30
'use strict'; `${private}`; //? <-> @1:18
'use strict'; a.private; //? <+>
'use strict'; ``.private; //? <+>
'use strict'; private++; //? <-> @1:15
'use strict'; ++private; //? <-> @1:17
'use strict'; private = 0; //? <-> @1:15
'use strict'; private *= 0; //? <-> @1:15
'use strict'; [private] = []; //? <-> @1:16
'use strict'; ({private} = {}); //? <-> @1:17
'use strict'; ({private = 0} = {}); //? <-> @1:17
'use strict'; [...private] = []; //? <-> @1:19
'use strict'; ({...private} = {}); //? <-> @1:20
'use strict'; private => {}; //? <-> @1:15
'use strict'; (private) => {}; //? <-> @1:16
'use strict'; ([private]) => {}; //? <-> @1:17
'use strict'; ({private}) => {}; //? <-> @1:17
'use strict'; ([...private]) => {}; //? <-> @1:20
'use strict'; ({...private}) => {}; //? <-> @1:20
'use strict'; (...private) => {}; //? <-> @1:19
'use strict'; async (private) => {}; //? <-> @1:22
'use strict'; async ([private]) => {}; //? <-> @1:23
'use strict'; async ({private}) => {}; //? <-> @1:23
'use strict'; async ([...private]) => {}; //? <-> @1:26
'use strict'; async ({...private}) => {}; //? <-> @1:26
'use strict'; async (...private) => {}; //? <-> @1:25
'use strict'; private: ; //? <-> @1:15
'use strict'; var private; //? <-> @1:19
'use strict'; var [private] = []; //? <-> @1:20
'use strict'; var {private} = {}; //? <-> @1:20
'use strict'; var [...private] = []; //? <-> @1:23
'use strict'; var {...private}= {}; //? <-> @1:23
'use strict'; let private; //? <-> @1:19
'use strict'; let [private] = []; //? <-> @1:20
'use strict'; let {private} = {}; //? <-> @1:20
'use strict'; let [...private] = []; //? <-> @1:23
'use strict'; let {...private} = {}; //? <-> @1:23
'use strict'; const private = 0; //? <-> @1:21
'use strict'; const [private] = 0; //? <-> @1:22
'use strict'; const {private} = 0; //? <-> @1:22
'use strict'; const [...private] = 0; //? <-> @1:25
'use strict'; const {...private} = 0; //? <-> @1:25
'use strict'; function private(){} //? <-> @1:24
'use strict'; function a(private){} //? <-> @1:26
'use strict'; function a(b = private){} //? <-> @1:30
'use strict'; function a([private]){} //? <-> @1:27
'use strict'; function a({private}){} //? <-> @1:27
'use strict'; function a([...private]){} //? <-> @1:30
'use strict'; function a({...private}){} //? <-> @1:30
'use strict'; function a(...private){} //? <-> @1:29
///
function private(){ 'use strict'; } //? <-> @1:10
function a(private){ 'use strict'; } //? <-> @1:12
function a(b, private){ 'use strict'; } //? <-> @1:15
!function private(){ 'use strict'; } //? <-> @1:11
!function a(private){ 'use strict'; } //? <-> @1:13
!{ private(){ 'use strict'; } } //? <+>
!{ a(private){ 'use strict'; } } //? <-> @1:6
!{ set a(private){ 'use strict'; } } //? <-> @1:10
private => { 'use strict'; }; //? <-> @1:1
(private) => { 'use strict'; }; //? <-> @1:2
async (private) => { 'use strict'; }; //? <-> @1:8

//- invalid_strict_mode_identifier
'use strict'; protected; //? <-> @1:15
'use strict'; [protected]; //? <-> @1:16
'use strict'; [...protected]; //? <-> @1:19
'use strict'; !{protected}; //? <-> @1:17
'use strict'; !{protected: 0}; //? <+>
'use strict'; !{[protected]: 0}; //? <-> @1:18
'use strict'; !{protected = 0}; //? <-> @1:17
'use strict'; !{ protected(){} } //? <+>
'use strict'; !{ [protected](){} }; //? <-> @1:19
'use strict'; !{ a(protected){} } //? <-> @1:20
'use strict'; !{ a([protected]){} } //? <-> @1:21
'use strict'; !{ a({protected}){} } //? <-> @1:21
'use strict'; !{ a([...protected]){} } //? <-> @1:24
'use strict'; !{ a({...protected}){} } //? <-> @1:24
'use strict'; !{ a(...protected){} } //? <-> @1:23
'use strict'; !{ set a(protected){} } //? <-> @1:24
'use strict'; !{ set a([protected]){} } //? <-> @1:25
'use strict'; !{ set a({protected}){} } //? <-> @1:25
'use strict'; !{ set a([...protected]){} } //? <-> @1:28
'use strict'; !{ set a({...protected}){} } //? <-> @1:28
'use strict'; !{ set a(...protected){} } //? <-> @1:24 -default
'use strict'; !function protected(){} //? <-> @1:25
'use strict'; !function a(b = protected){} //? <-> @1:31
'use strict'; !function a(protected){} //? <-> @1:27
'use strict'; !function a([protected]){} //? <-> @1:28
'use strict'; !function a({protected}){} //? <-> @1:28
'use strict'; !function a([...protected]){} //? <-> @1:31
'use strict'; !function a({...protected}){} //? <-> @1:31
'use strict'; !function a(...protected){} //? <-> @1:30
'use strict'; `${protected}`; //? <-> @1:18
'use strict'; a.protected; //? <+>
'use strict'; ``.protected; //? <+>
'use strict'; protected++; //? <-> @1:15
'use strict'; ++protected; //? <-> @1:17
'use strict'; protected = 0; //? <-> @1:15
'use strict'; protected *= 0; //? <-> @1:15
'use strict'; [protected] = []; //? <-> @1:16
'use strict'; ({protected} = {}); //? <-> @1:17
'use strict'; ({protected = 0} = {}); //? <-> @1:17
'use strict'; [...protected] = []; //? <-> @1:19
'use strict'; ({...protected} = {}); //? <-> @1:20
'use strict'; protected => {}; //? <-> @1:15
'use strict'; (protected) => {}; //? <-> @1:16
'use strict'; ([protected]) => {}; //? <-> @1:17
'use strict'; ({protected}) => {}; //? <-> @1:17
'use strict'; ([...protected]) => {}; //? <-> @1:20
'use strict'; ({...protected}) => {}; //? <-> @1:20
'use strict'; (...protected) => {}; //? <-> @1:19
'use strict'; async (protected) => {}; //? <-> @1:22
'use strict'; async ([protected]) => {}; //? <-> @1:23
'use strict'; async ({protected}) => {}; //? <-> @1:23
'use strict'; async ([...protected]) => {}; //? <-> @1:26
'use strict'; async ({...protected}) => {}; //? <-> @1:26
'use strict'; async (...protected) => {}; //? <-> @1:25
'use strict'; protected: ; //? <-> @1:15
'use strict'; var protected; //? <-> @1:19
'use strict'; var [protected] = []; //? <-> @1:20
'use strict'; var {protected} = {}; //? <-> @1:20
'use strict'; var [...protected] = []; //? <-> @1:23
'use strict'; var {...protected}= {}; //? <-> @1:23
'use strict'; let protected; //? <-> @1:19
'use strict'; let [protected] = []; //? <-> @1:20
'use strict'; let {protected} = {}; //? <-> @1:20
'use strict'; let [...protected] = []; //? <-> @1:23
'use strict'; let {...protected} = {}; //? <-> @1:23
'use strict'; const protected = 0; //? <-> @1:21
'use strict'; const [protected] = 0; //? <-> @1:22
'use strict'; const {protected} = 0; //? <-> @1:22
'use strict'; const [...protected] = 0; //? <-> @1:25
'use strict'; const {...protected} = 0; //? <-> @1:25
'use strict'; function protected(){} //? <-> @1:24
'use strict'; function a(protected){} //? <-> @1:26
'use strict'; function a(b = protected){} //? <-> @1:30
'use strict'; function a([protected]){} //? <-> @1:27
'use strict'; function a({protected}){} //? <-> @1:27
'use strict'; function a([...protected]){} //? <-> @1:30
'use strict'; function a({...protected}){} //? <-> @1:30
'use strict'; function a(...protected){} //? <-> @1:29
///
function protected(){ 'use strict'; } //? <-> @1:10
function a(protected){ 'use strict'; } //? <-> @1:12
function a(b, protected){ 'use strict'; } //? <-> @1:15
!function protected(){ 'use strict'; } //? <-> @1:11
!function a(protected){ 'use strict'; } //? <-> @1:13
!{ protected(){ 'use strict'; } } //? <+>
!{ a(protected){ 'use strict'; } } //? <-> @1:6
!{ set a(protected){ 'use strict'; } } //? <-> @1:10
protected => { 'use strict'; }; //? <-> @1:1
(protected) => { 'use strict'; }; //? <-> @1:2
async (protected) => { 'use strict'; }; //? <-> @1:8

//- invalid_strict_mode_identifier
'use strict'; public; //? <-> @1:15
'use strict'; [public]; //? <-> @1:16
'use strict'; [...public]; //? <-> @1:19
'use strict'; !{public}; //? <-> @1:17
'use strict'; !{public: 0}; //? <+>
'use strict'; !{[public]: 0}; //? <-> @1:18
'use strict'; !{public = 0}; //? <-> @1:17
'use strict'; !{ public(){} } //? <+>
'use strict'; !{ [public](){} }; //? <-> @1:19
'use strict'; !{ a(public){} } //? <-> @1:20
'use strict'; !{ a([public]){} } //? <-> @1:21
'use strict'; !{ a({public}){} } //? <-> @1:21
'use strict'; !{ a([...public]){} } //? <-> @1:24
'use strict'; !{ a({...public}){} } //? <-> @1:24
'use strict'; !{ a(...public){} } //? <-> @1:23
'use strict'; !{ set a(public){} } //? <-> @1:24
'use strict'; !{ set a([public]){} } //? <-> @1:25
'use strict'; !{ set a({public}){} } //? <-> @1:25
'use strict'; !{ set a([...public]){} } //? <-> @1:28
'use strict'; !{ set a({...public}){} } //? <-> @1:28
'use strict'; !{ set a(...public){} } //? <-> @1:24 -default
'use strict'; !function public(){} //? <-> @1:25
'use strict'; !function a(b = public){} //? <-> @1:31
'use strict'; !function a(public){} //? <-> @1:27
'use strict'; !function a([public]){} //? <-> @1:28
'use strict'; !function a({public}){} //? <-> @1:28
'use strict'; !function a([...public]){} //? <-> @1:31
'use strict'; !function a({...public}){} //? <-> @1:31
'use strict'; !function a(...public){} //? <-> @1:30
'use strict'; `${public}`; //? <-> @1:18
'use strict'; a.public; //? <+>
'use strict'; ``.public; //? <+>
'use strict'; public++; //? <-> @1:15
'use strict'; ++public; //? <-> @1:17
'use strict'; public = 0; //? <-> @1:15
'use strict'; public *= 0; //? <-> @1:15
'use strict'; [public] = []; //? <-> @1:16
'use strict'; ({public} = {}); //? <-> @1:17
'use strict'; ({public = 0} = {}); //? <-> @1:17
'use strict'; [...public] = []; //? <-> @1:19
'use strict'; ({...public} = {}); //? <-> @1:20
'use strict'; public => {}; //? <-> @1:15
'use strict'; (public) => {}; //? <-> @1:16
'use strict'; ([public]) => {}; //? <-> @1:17
'use strict'; ({public}) => {}; //? <-> @1:17
'use strict'; ([...public]) => {}; //? <-> @1:20
'use strict'; ({...public}) => {}; //? <-> @1:20
'use strict'; (...public) => {}; //? <-> @1:19
'use strict'; async (public) => {}; //? <-> @1:22
'use strict'; async ([public]) => {}; //? <-> @1:23
'use strict'; async ({public}) => {}; //? <-> @1:23
'use strict'; async ([...public]) => {}; //? <-> @1:26
'use strict'; async ({...public}) => {}; //? <-> @1:26
'use strict'; async (...public) => {}; //? <-> @1:25
'use strict'; public: ; //? <-> @1:15
'use strict'; var public; //? <-> @1:19
'use strict'; var [public] = []; //? <-> @1:20
'use strict'; var {public} = {}; //? <-> @1:20
'use strict'; var [...public] = []; //? <-> @1:23
'use strict'; var {...public}= {}; //? <-> @1:23
'use strict'; let public; //? <-> @1:19
'use strict'; let [public] = []; //? <-> @1:20
'use strict'; let {public} = {}; //? <-> @1:20
'use strict'; let [...public] = []; //? <-> @1:23
'use strict'; let {...public} = {}; //? <-> @1:23
'use strict'; const public = 0; //? <-> @1:21
'use strict'; const [public] = 0; //? <-> @1:22
'use strict'; const {public} = 0; //? <-> @1:22
'use strict'; const [...public] = 0; //? <-> @1:25
'use strict'; const {...public} = 0; //? <-> @1:25
'use strict'; function public(){} //? <-> @1:24
'use strict'; function a(public){} //? <-> @1:26
'use strict'; function a(b = public){} //? <-> @1:30
'use strict'; function a([public]){} //? <-> @1:27
'use strict'; function a({public}){} //? <-> @1:27
'use strict'; function a([...public]){} //? <-> @1:30
'use strict'; function a({...public}){} //? <-> @1:30
'use strict'; function a(...public){} //? <-> @1:29
///
function public(){ 'use strict'; } //? <-> @1:10
function a(public){ 'use strict'; } //? <-> @1:12
function a(b, public){ 'use strict'; } //? <-> @1:15
!function public(){ 'use strict'; } //? <-> @1:11
!function a(public){ 'use strict'; } //? <-> @1:13
!{ public(){ 'use strict'; } } //? <+>
!{ a(public){ 'use strict'; } } //? <-> @1:6
!{ set a(public){ 'use strict'; } } //? <-> @1:10
public => { 'use strict'; }; //? <-> @1:1
(public) => { 'use strict'; }; //? <-> @1:2
async (public) => { 'use strict'; }; //? <-> @1:8

