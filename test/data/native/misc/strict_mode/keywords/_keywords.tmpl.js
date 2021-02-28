'use strict'; keyword; //? <-> @1:15 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; [keyword]; //? <-> @1:16 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; [...keyword]; //? <-> @1:19 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; !{keyword}; //? <-> @1:17 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; !{keyword: 0}; //? <+>
'use strict'; !{[keyword]: 0}; //? <-> @1:18 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; !{keyword = 0}; //? <-> @1:17 $override
/*{ "await": "<-> @1:17 -invalid_cover_grammar" }*/
'use strict'; !{ keyword(){} } //? <+>
'use strict'; !{ [keyword](){} }; //? <-> @1:19 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; !{ a(keyword){} } //? <-> @1:20
'use strict'; !{ a([keyword]){} } //? <-> @1:21
'use strict'; !{ a({keyword}){} } //? <-> @1:21
'use strict'; !{ a([...keyword]){} } //? <-> @1:24
'use strict'; !{ a({...keyword}){} } //? <-> @1:24
'use strict'; !{ a(...keyword){} } //? <-> @1:23
'use strict'; !{ set a(keyword){} } //? <-> @1:24
'use strict'; !{ set a([keyword]){} } //? <-> @1:25
'use strict'; !{ set a({keyword}){} } //? <-> @1:25
'use strict'; !{ set a([...keyword]){} } //? <-> @1:28
'use strict'; !{ set a({...keyword}){} } //? <-> @1:28
'use strict'; !{ set a(...keyword){} } //? <-> @1:24 -default $override
/*{ "await": "<-> @1:24 -default" }*/
'use strict'; !function keyword(){} //? <-> @1:25
'use strict'; !function a(b = keyword){} //? <-> @1:31 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; !function a(keyword){} //? <-> @1:27
'use strict'; !function a([keyword]){} //? <-> @1:28
'use strict'; !function a({keyword}){} //? <-> @1:28
'use strict'; !function a([...keyword]){} //? <-> @1:31
'use strict'; !function a({...keyword}){} //? <-> @1:31
'use strict'; !function a(...keyword){} //? <-> @1:30
'use strict'; `${keyword}`; //? <-> @1:18 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; a.keyword; //? <+>
'use strict'; ``.keyword; //? <+>
'use strict'; keyword++; //? <-> @1:15
'use strict'; ++keyword; //? <-> @1:17
'use strict'; keyword = 0; //? <-> @1:15
'use strict'; keyword *= 0; //? <-> @1:15
'use strict'; [keyword] = []; //? <-> @1:16
'use strict'; ({keyword} = {}); //? <-> @1:17
'use strict'; ({keyword = 0} = {}); //? <-> @1:17
'use strict'; [...keyword] = []; //? <-> @1:19
'use strict'; ({...keyword} = {}); //? <-> @1:20
'use strict'; keyword => {}; //? <-> @1:15
'use strict'; (keyword) => {}; //? <-> @1:16
'use strict'; ([keyword]) => {}; //? <-> @1:17
'use strict'; ({keyword}) => {}; //? <-> @1:17
'use strict'; ([...keyword]) => {}; //? <-> @1:20
'use strict'; ({...keyword}) => {}; //? <-> @1:20
'use strict'; (...keyword) => {}; //? <-> @1:19
'use strict'; async (keyword) => {}; //? <-> @1:22 $override
/*{ "await": "<-> @1:22 -yield_await_in_arrow_params" }*/
'use strict'; async ([keyword]) => {}; //? <-> @1:23 $override
/*{ "await": "<-> @1:23 -yield_await_in_arrow_params" }*/
'use strict'; async ({keyword}) => {}; //? <-> @1:23 $override
/*{ "await": "<-> @1:23 -yield_await_in_arrow_params" }*/
'use strict'; async ([...keyword]) => {}; //? <-> @1:26 $override
/*{ "await": "<-> @1:26 -yield_await_in_arrow_params" }*/
'use strict'; async ({...keyword}) => {}; //? <-> @1:26 $override
/*{ "await": "<-> @1:26 -yield_await_in_arrow_params" }*/
'use strict'; async (...keyword) => {}; //? <-> @1:25 $override
/*{ "await": "<-> @1:25 -yield_await_in_arrow_params" }*/
'use strict'; keyword: ; //? <-> @1:15 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; var keyword; //? <-> @1:19
'use strict'; var [keyword] = []; //? <-> @1:20
'use strict'; var {keyword} = {}; //? <-> @1:20
'use strict'; var [...keyword] = []; //? <-> @1:23
'use strict'; var {...keyword}= {}; //? <-> @1:23
'use strict'; let keyword; //? <-> @1:19 $override
/*{ "let": "<-> @1:19 -let_in_lexical" }*/
'use strict'; let [keyword] = []; //? <-> @1:20 $override
/*{ "let": "<-> @1:20 -let_in_lexical" }*/
'use strict'; let {keyword} = {}; //? <-> @1:20 $override
/*{ "let": "<-> @1:20 -let_in_lexical" }*/
'use strict'; let [...keyword] = []; //? <-> @1:23 $override
/*{ "let": "<-> @1:23 -let_in_lexical" }*/
'use strict'; let {...keyword} = {}; //? <-> @1:23 $override
/*{ "let": "<-> @1:23 -let_in_lexical" }*/
'use strict'; const keyword = 0; //? <-> @1:21 $override
/*{ "let": "<-> @1:21 -let_in_lexical" }*/
'use strict'; const [keyword] = 0; //? <-> @1:22 $override
/*{ "let": "<-> @1:22 -let_in_lexical" }*/
'use strict'; const {keyword} = 0; //? <-> @1:22 $override
/*{ "let": "<-> @1:22 -let_in_lexical" }*/
'use strict'; const [...keyword] = 0; //? <-> @1:25 $override
/*{ "let": "<-> @1:25 -let_in_lexical" }*/
'use strict'; const {...keyword} = 0; //? <-> @1:25 $override
/*{ "let": "<-> @1:25 -let_in_lexical" }*/
'use strict'; function keyword(){} //? <-> @1:24
'use strict'; function a(keyword){} //? <-> @1:26
'use strict'; function a(b = keyword){} //? <-> @1:30 $override
/*{ "eval": "<+>", "arguments": "<+>" }*/
'use strict'; function a([keyword]){} //? <-> @1:27
'use strict'; function a({keyword}){} //? <-> @1:27
'use strict'; function a([...keyword]){} //? <-> @1:30
'use strict'; function a({...keyword}){} //? <-> @1:30
'use strict'; function a(...keyword){} //? <-> @1:29
///
function keyword(){ 'use strict'; } //? <-> @1:10
function a(keyword){ 'use strict'; } //? <-> @1:12
function a(b, keyword){ 'use strict'; } //? <-> @1:15
!function keyword(){ 'use strict'; } //? <-> @1:11
!function a(keyword){ 'use strict'; } //? <-> @1:13
!{ keyword(){ 'use strict'; } } //? <+>
!{ a(keyword){ 'use strict'; } } //? <-> @1:6
!{ set a(keyword){ 'use strict'; } } //? <-> @1:10
keyword => { 'use strict'; }; //? <-> @1:1
(keyword) => { 'use strict'; }; //? <-> @1:2
async (keyword) => { 'use strict'; }; //? <-> @1:8 $override
/*{ "await": "<-> @1:8 -yield_await_in_arrow_params" }*/
