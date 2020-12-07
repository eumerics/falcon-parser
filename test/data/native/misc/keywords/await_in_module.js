//- await_in_module
await; //? <-#> @1:1
await = 0; //? <-#> @1:1
await *= 0; //? <-#> @1:1
await++; //? <-#> @1:1
++await; //? <-#> @1:3
!{await}; //? <-#> @1:3
!{await = 0}; //? <-#> @1:3
[await] = []; //? <-#> @1:2
({await} = {}); //? <-#> @1:3
({await = 0} = {}); //? <-#> @1:3
[...await] = []; //? <-#> @1:5
({...await} = {}); //? <-#> @1:6
await: ; //? <-#> @1:1
var await; //? <-#> @1:5
var [await] = []; //? <-#> @1:6
var {await} = {}; //? <-#> @1:6
var [...await] = []; //? <-#> @1:9
var {...await} = {}; //? <-#> @1:9
let await; //? <-#> @1:5
let [await] = []; //? <-#> @1:6
let {await} = {}; //? <-#> @1:6
let [...await] = []; //? <-#> @1:9
let {...await} = {}; //? <-#> @1:9
const await = 0; //? <-#> @1:7
const [await] = []; //? <-#> @1:8
const {await} = {}; //? <-#> @1:8
const [...await] = []; //? <-#> @1:11
const {...await} = {}; //? <-#> @1:11
function await(){} //? <-#> @1:10
function a(await){} //? <-#> @1:12
function a([await]){} //? <-#> @1:13
function a({await}){} //? <-#> @1:13
function a(...await){} //? <-#> @1:15
!function await(){} //? <-#> @1:11
!function a(await){} //? <-#> @1:13
!function a([await]){} //? <-#> @1:14
!function a({await}){} //? <-#> @1:14
!function a(...await){} //? <-#> @1:16
class await {} //? <-#> @1:7
class a { await(){} } //? <+#>
class a { b(await){} } //? <-#> @1:13
class a { b([await]){} } //? <-#> @1:14
class a { b({await}){} } //? <-#> @1:14
class a { b(...await){} } //? <-#> @1:16
!class await {} //? <-#> @1:8
!class a { await(){} } //? <+#>
!class a { b(await){} } //? <-#> @1:14
!class a { b([await]){} } //? <-#> @1:15
!class a { b({await}){} } //? <-#> @1:15
!class a { b(...await){} } //? <-#> @1:17
!{ await(){} } //? <+#>
!{ a(await){} } //? <-#> @1:6
!{ a([await]){} } //? <-#> @1:7
!{ a({await}){} } //? <-#> @1:7
!{ a(...await){} } //? <-#> @1:9
await => {}; //? <-#> @1:1
(await) => {}; //? <-#> @1:2
([await]) => {}; //? <-#> @1:3
({await}) => {}; //? <-#> @1:3
(...await) => {}; //? <-#> @1:5
async(await) => {}; //? <-#> @1:7
async([await]) => {}; //? <-#> @1:8
async({await}) => {}; //? <-#> @1:8
async(...await) => {}; //? <-#> @1:10
