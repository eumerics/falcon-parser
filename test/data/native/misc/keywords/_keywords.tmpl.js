keyword; //? <+>
[keyword]; //? <+>
[...keyword]; //? <+>
!{keyword}; //? <+>
!{keyword: 0}; //? <+>
!{[keyword]: 0}; //? <+>
!{keyword = 0}; //? <-> @1:3 -invalid_cover_grammar $override
/*{ "skip-error-override": true }*/
!{ keyword(){} } //? <+>
!{ [keyword](){} } //? <+>
!{ a(keyword){} } //? <+>
!{ a([keyword]){} } //? <+>
!{ a({keyword}){} } //? <+>
!{ a([...keyword]){} } //? <+>
!{ a({...keyword}){} } //? <+>
!{ a(...keyword){} } //? <+>
!{ set a(keyword){} } //? <+>
!{ set a([keyword]){} } //? <+>
!{ set a({keyword}){} } //? <+>
!{ set a([...keyword]){} } //? <+>
!{ set a({...keyword}){} } //? <+>
!{ set a(...keyword){} } //? <-> @1:10 -default $override
/*{ "skip-error-override": true }*/
!function keyword(){} //? <+>
!function a(keyword){} //? <+>
!function a(b = keyword){} //? <+>
!function a([keyword]){} //? <+>
!function a({keyword}){} //? <+>
!function a([...keyword]){} //? <+>
!function a({...keyword}){} //? <+>
!function a(...keyword){} //? <+>
!class keyword {} //? <-> @1:8
!class a extends keyword {} //? <-> @1:18 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
!class a { keyword(){} } //? <+>
!class a { [keyword](){} } //? <-> @1:13 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
!class a { b(keyword){} } //? <-> @1:14
!class a { b([keyword]){} } //? <-> @1:15
!class a { b({keyword}){} } //? <-> @1:15
!class a { b([...keyword]){} } //? <-> @1:18
!class a { b({...keyword}){} } //? <-> @1:18
!class a { b(...keyword){} } //? <-> @1:17
`${keyword}`; //? <+>
a.keyword; //? <+>
``.keyword; //? <+>
keyword++; //? <+>
++keyword; //? <+>
keyword = 0; //? <+>
keyword *= 0; //? <+>
[keyword] = []; //? <+>
({keyword} = {}); //? <+>
({keyword = 0} = {}); //? <+>
[...keyword] = []; //? <+>
({...keyword} = {}); //? <+>
keyword => {}; //? <+>
(keyword) => {}; //? <+>
([keyword]) => {}; //? <+>
({keyword}) => {}; //? <+>
([...keyword]) => {}; //? <+>
({...keyword}) => {}; //? <+>
(...keyword) => {}; //? <+>
async (keyword) => {}; //? <+> $override
/*{ "await": "<-> @1:8 -yield_await_in_arrow_params" }*/
async ([keyword]) => {}; //? <+> $override
/*{ "await": "<-> @1:9 -yield_await_in_arrow_params" }*/
async ({keyword}) => {}; //? <+> $override
/*{ "await": "<-> @1:9 -yield_await_in_arrow_params" }*/
async ([...keyword]) => {}; //? <+> $override
/*{ "await": "<-> @1:12 -yield_await_in_arrow_params" }*/
async ({...keyword}) => {}; //? <+> $override
/*{ "await": "<-> @1:12 -yield_await_in_arrow_params" }*/
async (...keyword) => {}; //? <+> $override
/*{ "await": "<-> @1:11 -yield_await_in_arrow_params" }*/
keyword: ; //? <+>
var keyword; //? <+>
var [keyword] = []; //? <+>
var {keyword} = {}; //? <+>
var [...keyword] = []; //? <+>
var {...keyword} = {}; //? <+>
let keyword; //? <+> $override
/*{ "let": "<-> @1:5 -let_in_lexical" }*/
let [keyword] = []; //? <+> $override
/*{ "let": "<-> @1:6 -let_in_lexical" }*/
let {keyword} = {}; //? <+> $override
/*{ "let": "<-> @1:6 -let_in_lexical" }*/
let [...keyword] = []; //? <+> $override
/*{ "let": "<-> @1:9 -let_in_lexical" }*/
let {...keyword} = {}; //? <+> $override
/*{ "let": "<-> @1:9 -let_in_lexical" }*/
const keyword = 0; //? <+> $override
/*{ "let": "<-> @1:7 -let_in_lexical" }*/
const [keyword] = 0; //? <+> $override
/*{ "let": "<-> @1:8 -let_in_lexical" }*/
const {keyword} = 0; //? <+> $override
/*{ "let": "<-> @1:8 -let_in_lexical" }*/
const [...keyword] = 0; //? <+> $override
/*{ "let": "<-> @1:11 -let_in_lexical" }*/
const {...keyword} = 0; //? <+> $override
/*{ "let": "<-> @1:11 -let_in_lexical" }*/
function keyword(){} //? <+>
function a(keyword){} //? <+>
function a(b = keyword){} //? <+>
function a([keyword]){} //? <+>
function a({keyword}){} //? <+>
function a([...keyword]){} //? <+>
function a({...keyword}){} //? <+>
function a(...keyword){} //? <+>
class keyword {} //? <-> @1:7
class a extends keyword {} //? <-> @1:17 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
class a { keyword(){} } //? <+>
class a { [keyword](){} } //? <-> @1:12 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
class a { b(keyword){} } //? <-> @1:13
class a { b([keyword]){} } //? <-> @1:14
class a { b({keyword}){} } //? <-> @1:14
class a { b([...keyword]){} } //? <-> @1:17
class a { b({...keyword}){} } //? <-> @1:17
class a { b(...keyword){} } //? <-> @1:16
