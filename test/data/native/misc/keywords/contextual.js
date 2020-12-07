//- default
as; //? <+>
[as]; //? <+>
[...as]; //? <+>
!{as}; //? <+>
!{as: 0}; //? <+>
!{[as]: 0}; //? <+>
!{as = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ as(){} } //? <+>
!{ [as](){} } //? <+>
!{ a(as){} } //? <+>
!{ a([as]){} } //? <+>
!{ a({as}){} } //? <+>
!{ a([...as]){} } //? <+>
!{ a({...as}){} } //? <+>
!{ a(...as){} } //? <+>
!{ set a(as){} } //? <+>
!{ set a([as]){} } //? <+>
!{ set a({as}){} } //? <+>
!{ set a([...as]){} } //? <+>
!{ set a({...as}){} } //? <+>
!{ set a(...as){} } //? <-> @1:10 -default
!function as(){} //? <+>
!function a(as){} //? <+>
!function a(b = as){} //? <+>
!function a([as]){} //? <+>
!function a({as}){} //? <+>
!function a([...as]){} //? <+>
!function a({...as}){} //? <+>
!function a(...as){} //? <+>
!class as {} //? <+>
!class a extends as {} //? <+>
!class a { as(){} } //? <+>
!class a { [as](){} } //? <+>
!class a { b(as){} } //? <+>
!class a { b([as]){} } //? <+>
!class a { b({as}){} } //? <+>
!class a { b([...as]){} } //? <+>
!class a { b({...as}){} } //? <+>
!class a { b(...as){} } //? <+>
`${as}`; //? <+>
a.as; //? <+>
``.as; //? <+>
as++; //? <+>
++as; //? <+>
as = 0; //? <+>
as *= 0; //? <+>
[as] = []; //? <+>
({as} = {}); //? <+>
({as = 0} = {}); //? <+>
[...as] = []; //? <+>
({...as} = {}); //? <+>
as => {}; //? <+>
(as) => {}; //? <+>
([as]) => {}; //? <+>
({as}) => {}; //? <+>
([...as]) => {}; //? <+>
({...as}) => {}; //? <+>
(...as) => {}; //? <+>
async (as) => {}; //? <+>
async ([as]) => {}; //? <+>
async ({as}) => {}; //? <+>
async ([...as]) => {}; //? <+>
async ({...as}) => {}; //? <+>
async (...as) => {}; //? <+>
as: ; //? <+>
var as; //? <+>
var [as] = []; //? <+>
var {as} = {}; //? <+>
var [...as] = []; //? <+>
var {...as} = {}; //? <+>
let as; //? <+>
let [as] = []; //? <+>
let {as} = {}; //? <+>
let [...as] = []; //? <+>
let {...as} = {}; //? <+>
const as = 0; //? <+>
const [as] = 0; //? <+>
const {as} = 0; //? <+>
const [...as] = 0; //? <+>
const {...as} = 0; //? <+>
function as(){} //? <+>
function a(as){} //? <+>
function a(b = as){} //? <+>
function a([as]){} //? <+>
function a({as}){} //? <+>
function a([...as]){} //? <+>
function a({...as}){} //? <+>
function a(...as){} //? <+>
class as {} //? <+>
class a extends as {} //? <+>
class a { as(){} } //? <+>
class a { [as](){} } //? <+>
class a { b(as){} } //? <+>
class a { b([as]){} } //? <+>
class a { b({as}){} } //? <+>
class a { b([...as]){} } //? <+>
class a { b({...as}){} } //? <+>
class a { b(...as){} } //? <+>

//- default
async; //? <+>
[async]; //? <+>
[...async]; //? <+>
!{async}; //? <+>
!{async: 0}; //? <+>
!{[async]: 0}; //? <+>
!{async = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ async(){} } //? <+>
!{ [async](){} } //? <+>
!{ a(async){} } //? <+>
!{ a([async]){} } //? <+>
!{ a({async}){} } //? <+>
!{ a([...async]){} } //? <+>
!{ a({...async}){} } //? <+>
!{ a(...async){} } //? <+>
!{ set a(async){} } //? <+>
!{ set a([async]){} } //? <+>
!{ set a({async}){} } //? <+>
!{ set a([...async]){} } //? <+>
!{ set a({...async}){} } //? <+>
!{ set a(...async){} } //? <-> @1:10 -default
!function async(){} //? <+>
!function a(async){} //? <+>
!function a(b = async){} //? <+>
!function a([async]){} //? <+>
!function a({async}){} //? <+>
!function a([...async]){} //? <+>
!function a({...async}){} //? <+>
!function a(...async){} //? <+>
!class async {} //? <+>
!class a extends async {} //? <+>
!class a { async(){} } //? <+>
!class a { [async](){} } //? <+>
!class a { b(async){} } //? <+>
!class a { b([async]){} } //? <+>
!class a { b({async}){} } //? <+>
!class a { b([...async]){} } //? <+>
!class a { b({...async}){} } //? <+>
!class a { b(...async){} } //? <+>
`${async}`; //? <+>
a.async; //? <+>
``.async; //? <+>
async++; //? <+>
++async; //? <+>
async = 0; //? <+>
async *= 0; //? <+>
[async] = []; //? <+>
({async} = {}); //? <+>
({async = 0} = {}); //? <+>
[...async] = []; //? <+>
({...async} = {}); //? <+>
async => {}; //? <+>
(async) => {}; //? <+>
([async]) => {}; //? <+>
({async}) => {}; //? <+>
([...async]) => {}; //? <+>
({...async}) => {}; //? <+>
(...async) => {}; //? <+>
async (async) => {}; //? <+>
async ([async]) => {}; //? <+>
async ({async}) => {}; //? <+>
async ([...async]) => {}; //? <+>
async ({...async}) => {}; //? <+>
async (...async) => {}; //? <+>
async: ; //? <+>
var async; //? <+>
var [async] = []; //? <+>
var {async} = {}; //? <+>
var [...async] = []; //? <+>
var {...async} = {}; //? <+>
let async; //? <+>
let [async] = []; //? <+>
let {async} = {}; //? <+>
let [...async] = []; //? <+>
let {...async} = {}; //? <+>
const async = 0; //? <+>
const [async] = 0; //? <+>
const {async} = 0; //? <+>
const [...async] = 0; //? <+>
const {...async} = 0; //? <+>
function async(){} //? <+>
function a(async){} //? <+>
function a(b = async){} //? <+>
function a([async]){} //? <+>
function a({async}){} //? <+>
function a([...async]){} //? <+>
function a({...async}){} //? <+>
function a(...async){} //? <+>
class async {} //? <+>
class a extends async {} //? <+>
class a { async(){} } //? <+>
class a { [async](){} } //? <+>
class a { b(async){} } //? <+>
class a { b([async]){} } //? <+>
class a { b({async}){} } //? <+>
class a { b([...async]){} } //? <+>
class a { b({...async}){} } //? <+>
class a { b(...async){} } //? <+>

//- default
from; //? <+>
[from]; //? <+>
[...from]; //? <+>
!{from}; //? <+>
!{from: 0}; //? <+>
!{[from]: 0}; //? <+>
!{from = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ from(){} } //? <+>
!{ [from](){} } //? <+>
!{ a(from){} } //? <+>
!{ a([from]){} } //? <+>
!{ a({from}){} } //? <+>
!{ a([...from]){} } //? <+>
!{ a({...from}){} } //? <+>
!{ a(...from){} } //? <+>
!{ set a(from){} } //? <+>
!{ set a([from]){} } //? <+>
!{ set a({from}){} } //? <+>
!{ set a([...from]){} } //? <+>
!{ set a({...from}){} } //? <+>
!{ set a(...from){} } //? <-> @1:10 -default
!function from(){} //? <+>
!function a(from){} //? <+>
!function a(b = from){} //? <+>
!function a([from]){} //? <+>
!function a({from}){} //? <+>
!function a([...from]){} //? <+>
!function a({...from}){} //? <+>
!function a(...from){} //? <+>
!class from {} //? <+>
!class a extends from {} //? <+>
!class a { from(){} } //? <+>
!class a { [from](){} } //? <+>
!class a { b(from){} } //? <+>
!class a { b([from]){} } //? <+>
!class a { b({from}){} } //? <+>
!class a { b([...from]){} } //? <+>
!class a { b({...from}){} } //? <+>
!class a { b(...from){} } //? <+>
`${from}`; //? <+>
a.from; //? <+>
``.from; //? <+>
from++; //? <+>
++from; //? <+>
from = 0; //? <+>
from *= 0; //? <+>
[from] = []; //? <+>
({from} = {}); //? <+>
({from = 0} = {}); //? <+>
[...from] = []; //? <+>
({...from} = {}); //? <+>
from => {}; //? <+>
(from) => {}; //? <+>
([from]) => {}; //? <+>
({from}) => {}; //? <+>
([...from]) => {}; //? <+>
({...from}) => {}; //? <+>
(...from) => {}; //? <+>
async (from) => {}; //? <+>
async ([from]) => {}; //? <+>
async ({from}) => {}; //? <+>
async ([...from]) => {}; //? <+>
async ({...from}) => {}; //? <+>
async (...from) => {}; //? <+>
from: ; //? <+>
var from; //? <+>
var [from] = []; //? <+>
var {from} = {}; //? <+>
var [...from] = []; //? <+>
var {...from} = {}; //? <+>
let from; //? <+>
let [from] = []; //? <+>
let {from} = {}; //? <+>
let [...from] = []; //? <+>
let {...from} = {}; //? <+>
const from = 0; //? <+>
const [from] = 0; //? <+>
const {from} = 0; //? <+>
const [...from] = 0; //? <+>
const {...from} = 0; //? <+>
function from(){} //? <+>
function a(from){} //? <+>
function a(b = from){} //? <+>
function a([from]){} //? <+>
function a({from}){} //? <+>
function a([...from]){} //? <+>
function a({...from}){} //? <+>
function a(...from){} //? <+>
class from {} //? <+>
class a extends from {} //? <+>
class a { from(){} } //? <+>
class a { [from](){} } //? <+>
class a { b(from){} } //? <+>
class a { b([from]){} } //? <+>
class a { b({from}){} } //? <+>
class a { b([...from]){} } //? <+>
class a { b({...from}){} } //? <+>
class a { b(...from){} } //? <+>

//- default
get; //? <+>
[get]; //? <+>
[...get]; //? <+>
!{get}; //? <+>
!{get: 0}; //? <+>
!{[get]: 0}; //? <+>
!{get = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ get(){} } //? <+>
!{ [get](){} } //? <+>
!{ a(get){} } //? <+>
!{ a([get]){} } //? <+>
!{ a({get}){} } //? <+>
!{ a([...get]){} } //? <+>
!{ a({...get}){} } //? <+>
!{ a(...get){} } //? <+>
!{ set a(get){} } //? <+>
!{ set a([get]){} } //? <+>
!{ set a({get}){} } //? <+>
!{ set a([...get]){} } //? <+>
!{ set a({...get}){} } //? <+>
!{ set a(...get){} } //? <-> @1:10 -default
!function get(){} //? <+>
!function a(get){} //? <+>
!function a(b = get){} //? <+>
!function a([get]){} //? <+>
!function a({get}){} //? <+>
!function a([...get]){} //? <+>
!function a({...get}){} //? <+>
!function a(...get){} //? <+>
!class get {} //? <+>
!class a extends get {} //? <+>
!class a { get(){} } //? <+>
!class a { [get](){} } //? <+>
!class a { b(get){} } //? <+>
!class a { b([get]){} } //? <+>
!class a { b({get}){} } //? <+>
!class a { b([...get]){} } //? <+>
!class a { b({...get}){} } //? <+>
!class a { b(...get){} } //? <+>
`${get}`; //? <+>
a.get; //? <+>
``.get; //? <+>
get++; //? <+>
++get; //? <+>
get = 0; //? <+>
get *= 0; //? <+>
[get] = []; //? <+>
({get} = {}); //? <+>
({get = 0} = {}); //? <+>
[...get] = []; //? <+>
({...get} = {}); //? <+>
get => {}; //? <+>
(get) => {}; //? <+>
([get]) => {}; //? <+>
({get}) => {}; //? <+>
([...get]) => {}; //? <+>
({...get}) => {}; //? <+>
(...get) => {}; //? <+>
async (get) => {}; //? <+>
async ([get]) => {}; //? <+>
async ({get}) => {}; //? <+>
async ([...get]) => {}; //? <+>
async ({...get}) => {}; //? <+>
async (...get) => {}; //? <+>
get: ; //? <+>
var get; //? <+>
var [get] = []; //? <+>
var {get} = {}; //? <+>
var [...get] = []; //? <+>
var {...get} = {}; //? <+>
let get; //? <+>
let [get] = []; //? <+>
let {get} = {}; //? <+>
let [...get] = []; //? <+>
let {...get} = {}; //? <+>
const get = 0; //? <+>
const [get] = 0; //? <+>
const {get} = 0; //? <+>
const [...get] = 0; //? <+>
const {...get} = 0; //? <+>
function get(){} //? <+>
function a(get){} //? <+>
function a(b = get){} //? <+>
function a([get]){} //? <+>
function a({get}){} //? <+>
function a([...get]){} //? <+>
function a({...get}){} //? <+>
function a(...get){} //? <+>
class get {} //? <+>
class a extends get {} //? <+>
class a { get(){} } //? <+>
class a { [get](){} } //? <+>
class a { b(get){} } //? <+>
class a { b([get]){} } //? <+>
class a { b({get}){} } //? <+>
class a { b([...get]){} } //? <+>
class a { b({...get}){} } //? <+>
class a { b(...get){} } //? <+>

//- default
of; //? <+>
[of]; //? <+>
[...of]; //? <+>
!{of}; //? <+>
!{of: 0}; //? <+>
!{[of]: 0}; //? <+>
!{of = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ of(){} } //? <+>
!{ [of](){} } //? <+>
!{ a(of){} } //? <+>
!{ a([of]){} } //? <+>
!{ a({of}){} } //? <+>
!{ a([...of]){} } //? <+>
!{ a({...of}){} } //? <+>
!{ a(...of){} } //? <+>
!{ set a(of){} } //? <+>
!{ set a([of]){} } //? <+>
!{ set a({of}){} } //? <+>
!{ set a([...of]){} } //? <+>
!{ set a({...of}){} } //? <+>
!{ set a(...of){} } //? <-> @1:10 -default
!function of(){} //? <+>
!function a(of){} //? <+>
!function a(b = of){} //? <+>
!function a([of]){} //? <+>
!function a({of}){} //? <+>
!function a([...of]){} //? <+>
!function a({...of}){} //? <+>
!function a(...of){} //? <+>
!class of {} //? <+>
!class a extends of {} //? <+>
!class a { of(){} } //? <+>
!class a { [of](){} } //? <+>
!class a { b(of){} } //? <+>
!class a { b([of]){} } //? <+>
!class a { b({of}){} } //? <+>
!class a { b([...of]){} } //? <+>
!class a { b({...of}){} } //? <+>
!class a { b(...of){} } //? <+>
`${of}`; //? <+>
a.of; //? <+>
``.of; //? <+>
of++; //? <+>
++of; //? <+>
of = 0; //? <+>
of *= 0; //? <+>
[of] = []; //? <+>
({of} = {}); //? <+>
({of = 0} = {}); //? <+>
[...of] = []; //? <+>
({...of} = {}); //? <+>
of => {}; //? <+>
(of) => {}; //? <+>
([of]) => {}; //? <+>
({of}) => {}; //? <+>
([...of]) => {}; //? <+>
({...of}) => {}; //? <+>
(...of) => {}; //? <+>
async (of) => {}; //? <+>
async ([of]) => {}; //? <+>
async ({of}) => {}; //? <+>
async ([...of]) => {}; //? <+>
async ({...of}) => {}; //? <+>
async (...of) => {}; //? <+>
of: ; //? <+>
var of; //? <+>
var [of] = []; //? <+>
var {of} = {}; //? <+>
var [...of] = []; //? <+>
var {...of} = {}; //? <+>
let of; //? <+>
let [of] = []; //? <+>
let {of} = {}; //? <+>
let [...of] = []; //? <+>
let {...of} = {}; //? <+>
const of = 0; //? <+>
const [of] = 0; //? <+>
const {of} = 0; //? <+>
const [...of] = 0; //? <+>
const {...of} = 0; //? <+>
function of(){} //? <+>
function a(of){} //? <+>
function a(b = of){} //? <+>
function a([of]){} //? <+>
function a({of}){} //? <+>
function a([...of]){} //? <+>
function a({...of}){} //? <+>
function a(...of){} //? <+>
class of {} //? <+>
class a extends of {} //? <+>
class a { of(){} } //? <+>
class a { [of](){} } //? <+>
class a { b(of){} } //? <+>
class a { b([of]){} } //? <+>
class a { b({of}){} } //? <+>
class a { b([...of]){} } //? <+>
class a { b({...of}){} } //? <+>
class a { b(...of){} } //? <+>

//- default
set; //? <+>
[set]; //? <+>
[...set]; //? <+>
!{set}; //? <+>
!{set: 0}; //? <+>
!{[set]: 0}; //? <+>
!{set = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ set(){} } //? <+>
!{ [set](){} } //? <+>
!{ a(set){} } //? <+>
!{ a([set]){} } //? <+>
!{ a({set}){} } //? <+>
!{ a([...set]){} } //? <+>
!{ a({...set}){} } //? <+>
!{ a(...set){} } //? <+>
!{ set a(set){} } //? <+>
!{ set a([set]){} } //? <+>
!{ set a({set}){} } //? <+>
!{ set a([...set]){} } //? <+>
!{ set a({...set}){} } //? <+>
!{ set a(...set){} } //? <-> @1:10 -default
!function set(){} //? <+>
!function a(set){} //? <+>
!function a(b = set){} //? <+>
!function a([set]){} //? <+>
!function a({set}){} //? <+>
!function a([...set]){} //? <+>
!function a({...set}){} //? <+>
!function a(...set){} //? <+>
!class set {} //? <+>
!class a extends set {} //? <+>
!class a { set(){} } //? <+>
!class a { [set](){} } //? <+>
!class a { b(set){} } //? <+>
!class a { b([set]){} } //? <+>
!class a { b({set}){} } //? <+>
!class a { b([...set]){} } //? <+>
!class a { b({...set}){} } //? <+>
!class a { b(...set){} } //? <+>
`${set}`; //? <+>
a.set; //? <+>
``.set; //? <+>
set++; //? <+>
++set; //? <+>
set = 0; //? <+>
set *= 0; //? <+>
[set] = []; //? <+>
({set} = {}); //? <+>
({set = 0} = {}); //? <+>
[...set] = []; //? <+>
({...set} = {}); //? <+>
set => {}; //? <+>
(set) => {}; //? <+>
([set]) => {}; //? <+>
({set}) => {}; //? <+>
([...set]) => {}; //? <+>
({...set}) => {}; //? <+>
(...set) => {}; //? <+>
async (set) => {}; //? <+>
async ([set]) => {}; //? <+>
async ({set}) => {}; //? <+>
async ([...set]) => {}; //? <+>
async ({...set}) => {}; //? <+>
async (...set) => {}; //? <+>
set: ; //? <+>
var set; //? <+>
var [set] = []; //? <+>
var {set} = {}; //? <+>
var [...set] = []; //? <+>
var {...set} = {}; //? <+>
let set; //? <+>
let [set] = []; //? <+>
let {set} = {}; //? <+>
let [...set] = []; //? <+>
let {...set} = {}; //? <+>
const set = 0; //? <+>
const [set] = 0; //? <+>
const {set} = 0; //? <+>
const [...set] = 0; //? <+>
const {...set} = 0; //? <+>
function set(){} //? <+>
function a(set){} //? <+>
function a(b = set){} //? <+>
function a([set]){} //? <+>
function a({set}){} //? <+>
function a([...set]){} //? <+>
function a({...set}){} //? <+>
function a(...set){} //? <+>
class set {} //? <+>
class a extends set {} //? <+>
class a { set(){} } //? <+>
class a { [set](){} } //? <+>
class a { b(set){} } //? <+>
class a { b([set]){} } //? <+>
class a { b({set}){} } //? <+>
class a { b([...set]){} } //? <+>
class a { b({...set}){} } //? <+>
class a { b(...set){} } //? <+>

//- default
target; //? <+>
[target]; //? <+>
[...target]; //? <+>
!{target}; //? <+>
!{target: 0}; //? <+>
!{[target]: 0}; //? <+>
!{target = 0}; //? <-> @1:3 -invalid_cover_grammar
!{ target(){} } //? <+>
!{ [target](){} } //? <+>
!{ a(target){} } //? <+>
!{ a([target]){} } //? <+>
!{ a({target}){} } //? <+>
!{ a([...target]){} } //? <+>
!{ a({...target}){} } //? <+>
!{ a(...target){} } //? <+>
!{ set a(target){} } //? <+>
!{ set a([target]){} } //? <+>
!{ set a({target}){} } //? <+>
!{ set a([...target]){} } //? <+>
!{ set a({...target}){} } //? <+>
!{ set a(...target){} } //? <-> @1:10 -default
!function target(){} //? <+>
!function a(target){} //? <+>
!function a(b = target){} //? <+>
!function a([target]){} //? <+>
!function a({target}){} //? <+>
!function a([...target]){} //? <+>
!function a({...target}){} //? <+>
!function a(...target){} //? <+>
!class target {} //? <+>
!class a extends target {} //? <+>
!class a { target(){} } //? <+>
!class a { [target](){} } //? <+>
!class a { b(target){} } //? <+>
!class a { b([target]){} } //? <+>
!class a { b({target}){} } //? <+>
!class a { b([...target]){} } //? <+>
!class a { b({...target}){} } //? <+>
!class a { b(...target){} } //? <+>
`${target}`; //? <+>
a.target; //? <+>
``.target; //? <+>
target++; //? <+>
++target; //? <+>
target = 0; //? <+>
target *= 0; //? <+>
[target] = []; //? <+>
({target} = {}); //? <+>
({target = 0} = {}); //? <+>
[...target] = []; //? <+>
({...target} = {}); //? <+>
target => {}; //? <+>
(target) => {}; //? <+>
([target]) => {}; //? <+>
({target}) => {}; //? <+>
([...target]) => {}; //? <+>
({...target}) => {}; //? <+>
(...target) => {}; //? <+>
async (target) => {}; //? <+>
async ([target]) => {}; //? <+>
async ({target}) => {}; //? <+>
async ([...target]) => {}; //? <+>
async ({...target}) => {}; //? <+>
async (...target) => {}; //? <+>
target: ; //? <+>
var target; //? <+>
var [target] = []; //? <+>
var {target} = {}; //? <+>
var [...target] = []; //? <+>
var {...target} = {}; //? <+>
let target; //? <+>
let [target] = []; //? <+>
let {target} = {}; //? <+>
let [...target] = []; //? <+>
let {...target} = {}; //? <+>
const target = 0; //? <+>
const [target] = 0; //? <+>
const {target} = 0; //? <+>
const [...target] = 0; //? <+>
const {...target} = 0; //? <+>
function target(){} //? <+>
function a(target){} //? <+>
function a(b = target){} //? <+>
function a([target]){} //? <+>
function a({target}){} //? <+>
function a([...target]){} //? <+>
function a({...target}){} //? <+>
function a(...target){} //? <+>
class target {} //? <+>
class a extends target {} //? <+>
class a { target(){} } //? <+>
class a { [target](){} } //? <+>
class a { b(target){} } //? <+>
class a { b([target]){} } //? <+>
class a { b({target}){} } //? <+>
class a { b([...target]){} } //? <+>
class a { b({...target}){} } //? <+>
class a { b(...target){} } //? <+>

