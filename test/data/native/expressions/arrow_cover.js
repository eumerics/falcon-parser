(a.b) => {}; //? <-> @1:2 -invalid_binding_target
(); //? <-> @1:2 -empty_parenthetical
(a); //? <+>
(a.b); //? <+>
(a,); //? <-> @1:3 -trailing_comma
(...a); //? <-> @1:2 -invalid_cover_grammar
(...a,); //? <-> @1:6 -missing_parenthesis
(...a, ...b); //? <-> @1:6 -missing_parenthesis
///
([]); //? <+>
([a]); //? <+>
([a,]); //? <+>
([a,,b]); //? <+>
([a.b]); //? <+>
([...a]); //? <+>
([...a,]); //? <+>
([...a, ...b]); //? <+>
///
({}); //? <+>
({a}); //? <+>
({a,}); //? <+>
({a.b}); //? <-> @1:4 -default
({...a}); //? <+>
({...a,}); //? <+>
({...a, ...b}); //? <+>
///
() => {}; //? <+>
(a) => {}; //? <+>
(a.b) => {}; //? <-> @1:2 -invalid_binding_target
(a,) => {}; //? <+>
(...a) => {}; //? <+>
(...(a)) => {}; //? <-> @1:5 -invalid_binding_target
(...a,) => {}; //? <-> @1:6 -missing_parenthesis
(...a, ...b) => {}; //? <-> @1:6 -missing_parenthesis
///
([]) => {}; //? <+>
([a]) => {}; //? <+>
([a,]) => {}; //? <+>
([a,,b]) => {}; //? <+>
([a.b]) => {}; //? <-> @1:3 -invalid_binding_target
([...a]) => {}; //? <+>
([...(a)]) => {}; //? <-> @1:6 -invalid_binding_target
([...a,]) => {}; //? <-> @1:3 -middle_rest
([...a, ...b]) => {}; //? <-> @1:3 -middle_rest
///
({}) => {}; //? <+>
({a}) => {}; //? <+>
({a,}) => {}; //? <+>
({a.b}) => {}; //? <-> @1:4 -default
({...a}) => {}; //? <+>
({...(a)}) => {}; //? <-> @1:6 -invalid_binding_target
({...a,}) => {}; //? <-> @1:3 -middle_rest
({...a, ...b}) => {}; //? <-> @1:3 -middle_rest
///
(a = yield); //? <+>
!function*(){ (a = yield); } //? <+>
!async function(){ (a = await 0); } //? <+>
!function*(){ (a = !function(){ yield; }); } //? <+>
!function*(){ (a = () => { yield; }) } //? <+>
///
(a = yield) => {}; //? <+>
!function*(){ (a = yield) => {}; } //? <-> @1:20 -yield_await_in_arrow_params
!function*(){ (a = (yield)) => {}; } //? <-> @1:21 -yield_await_in_arrow_params
!function*(){ (a = yield, b = ([])) => {}; } //? <-> @1:20 -yield_await_in_arrow_params
!function*(){ (a = !function(){ yield; }) => {}; } //? <+>
!function*(){ (a = !function*(){ yield; }) => {}; } //? <+>
!function*(){ (a = () => { yield; }) => {} } //? <+>
///
!async function(){ (a = await 0) => {}; } //? <-> @1:25 -yield_await_in_arrow_params
!async function(){ (a = (await 0)) => {}; } //? <-> @1:26 -yield_await_in_arrow_params
!async function(){ (a = await 0, b = ([])) => {}; } //? <-> @1:25 -yield_await_in_arrow_params
!async function(){ (a = !function(){ await; }) => {}; } //? <+>
!async function(){ (a = !async function(){ await 0; }) => {}; } //? <+>
!async function(){ (a = async() => { await 0; }) => {} } //? <+>
///
///!function*(){ (a, a, b = yield) => {}; } //? <-> @1:19 -duplicate_symbol
!function*(){ (a, b = yield, a) => {}; } //? <-> @1:23 -yield_await_in_arrow_params

async(a, a); //? <+>

async(await); //? <+>
async(await 0); //? <-> @1:13 -default
async(a = await); //? <+>
async(a = await 0); //? <-> @1:17 -default
!async function(){ async(await); } //? <-> @1:31 -default
!async function(){ async(await 0); } //? <+>
!async function(){ async(a = await); } //? <-> @1:35 -default
!async function(){ async(a = await 0); } //? <+>

(yield) => {}; //? <+>
(yield 0) => {}; //? <-> @1:8 -default
(a = yield) => {}; //? <+>
(a = yield 0) => {}; //? <-> @1:12 -default
(a = !function yield(){}) => {}; //? <+>
(a = !class yield{}) => {}; //? <-> @1:13 -yield_in_strict_mode
(a = {yield(){}}); //? <+>
(a = {*b(){ yield 0; }}); //? <+>
(a = !function*(){ yield 0; }) => {}; //? <+>
(a = !class{*b(){ yield 0; }}) => {}; //? <+>

async (yield) => {}; //? <+>
async (yield 0) => {}; //? <-> @1:14 -default
async (a = yield) => {}; //? <+>
async (a = yield 0) => {}; //? <-> @1:18 -default
async (a = !function yield(){}) => {}; //? <+>
async (a = !class yield{}) => {}; //? <-> @1:19 -yield_in_strict_mode
async (a = {yield(){}}); //? <+>
async (a = {*b(){ yield 0; }}); //? <+>
async (a = !function*(){ yield 0; }) => {}; //? <+>
async (a = !class{*b(){ yield 0; }}) => {}; //? <+>

(await) => {}; //? <+>
(await 0) => {}; //? <-> @1:8 -default
(a = await) => {}; //? <+>
(a = await 0) => {}; //? <-> @1:12 -default
(a = !function await(){}) => {}; //? <+>
(a = !class await{}) => {}; //? <+>
(a = {await(){}}); //? <+>
(a = {async b(){ await 0; }}); //? <+>
(a = !async function(){ await 0; }) => {}; //? <+>
(a = !class{async b(){ await 0; }}) => {}; //? <+>

async (await) => {}; //? <-> @1:8 -yield_await_in_arrow_params
async (await 0) => {}; //? <-> @1:14 -default
async (a = await) => {}; //? <-> @1:12 -yield_await_in_arrow_params
async (a = await 0) => {}; //? <-> @1:18 -default
async (a = !function await(){}) => {}; //? <-> @1:22 -yield_await_in_arrow_params
async (a = !class await{}) => {}; //? <-> @1:19 -yield_await_in_arrow_params
async (a = {await(){}}); //? <+>
async (a = {async b(){ await 0; }}); //? <+>
async (a = !async function(){ await 0; }) => {}; //? <+>
async (a = !class{async b(){ await 0; }}) => {}; //? <+>

async
() => {}; //? <-> @2:4 -default
() => {} /./ //? <-> @1:10 -default
async ()
=> {}; //? <-> @2:1 -default
