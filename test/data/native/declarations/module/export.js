export * from 'a'; //? <+#>
export * as a from 'a'; //? <+#>

export {} from 'a'; //? <+#>
export {a} from 'a'; //? <+#>
export {a as b} from 'a'; //? <+#>
export {a, b as c, d,} from 'a'; //? <+#>

export {}; //? <+#>
let a; export {a}; //? <+#>
let a; export {a as b}; //? <+#>
let a; export {a as default}; //? <+#>
let a, b, d; export {a, b as c, d,}; //? <+#>

export var a; //? <+#>
export let a; //? <+#>
export const a = 0; //? <+#>
export var [a] = []; //? <+#>
export let [a] = []; //? <+#>
export const [a] = []; //? <+#>
export var {a} = {}; //? <+#>
export let {a} = {}; //? <+#>
export const {a} = {}; //? <+#>

export function a(){} //? <+#>
export function* a(){} //? <+#>
export async function a(){} //? <+#>
export async function* a(){} //? <+#>
export class a {} //? <+#>

export default function a(){} //? <+#>
export default function* a(){} //? <+#>
export default async function a(){} //? <+#>
export default async function* a(){} //? <+#>
export default class a {} //? <+#>

export default function(){} //? <+#>
export default function*(){} //? <+#>
export default async function(){} //? <+#>
export default async function*(){} //? <+#>
export default class {} //? <+#>

export default 0; //? <+#>
export default async; //? <+#>
export default [a] = []; //? <+#>
export default {a} = {}; //? <+#>

export var a; export default b; //? <+#>

/// lexical uniqueness of export declarations
//- duplicate_export
///   var-var
export var a, a; //? <-#> @1:15
export var [a, a] = []; //? <-#> @1:16
export var a; export var a; //? <-#> @1:26
export var a; var a; //? <+#>
export var [a] = []; var a; //? <+#>
export var {a} = {}; var a; //? <+#>
var a; export var a; //? <+#>
var a; export var [a] = []; //? <+#>
var a; export var {a} = {}; //? <+#>
//- duplicate_symbol
///   let-let
export let a, a; //? <-#> @1:15
export let [a, a] = []; //? <-#> @1:16
export let a; export let a; //? <-#> @1:26
export let a; let a; //? <-#> @1:19
export let [a] = []; let a; //? <-#> @1:26
export let {a} = {}; let a; //? <-#> @1:26
export let a; { let a; } //? <+#>
export let [a] = []; { let a; } //? <+#>
export let {a} = {}; { let a; } //? <+#>
let a; export let a; //? <-#> @1:19
let a; export let [a] = []; //? <-#> @1:20
let a; export let {a} = {}; //? <-#> @1:20
{ let a; } export let a; //? <+#>
{ let a; } export let [a] = []; //? <+#>
{ let a; } export let {a} = {}; //? <+#>
///   var-let
export var a; export let a; //? <-#> @1:26
export let a; export var a; //? <-#> @1:26
export var a; let a; //? <-#> @1:19
export var [a] = []; let a; //? <-#> @1:26
export var {a} = {}; let a; //? <-#> @1:26
export var a; { let a; } //? <+#>
export var [a] = []; { let a; } //? <+#>
export var {a} = {}; { let a; } //? <+#>
var a; export let a; //? <-#> @1:19
var a; export let [a] = []; //? <-#> @1:20
var a; export let {a} = {}; //? <-#> @1:20
///   let-var
export let a; export var a; //? <-#> @1:26
export let a; var a; //? <-#> @1:19
export let [a] = []; var a; //? <-#> @1:26
export let {a} = {}; var a; //? <-#> @1:26
let a; export var a; //? <-#> @1:19
let a; export var [a] = []; //? <-#> @1:20
let a; export var {a} = {}; //? <-#> @1:20
{ let a; } export var a; //? <+#>
{ let a; } export var [a] = []; //? <+#>
{ let a; } export var {a} = {}; //? <+#>
/// named-var, named-let
//- duplicate_export
export {a}; export var a; //? <-#> @1:24
export {a}; export let a; //? <-#> @1:24
export var a; export {a}; //? <-#> @1:23
export let a; export {a}; //? <-#> @1:23
export {a as b}; export var a; //? <+#>
export {a as b}; export let a; //? <+#>
export var a; export {a as b}; //? <+#>
export let a; export {a as b}; //? <+#>
var a; export {a as b}; var b; //? <+#>
var a; export {a as b}; let b; //? <+#>
var a; var b; export {a as b}; //? <+#>
var a; let b; export {a as b}; //? <+#>
var a; export {a as b}; export var b; //? <-#> @1:36
var a; export {a as b}; export let b; //? <-#> @1:36
var a; export var b; export {a as b}; //? <-#> @1:35
var a; export let b; export {a as b}; //? <-#> @1:35
/// default-var default-let
export var a; export default a; //? <+#>
export let a; export default a; //? <+#>
export default a; export var a; //? <+#>
export default a; export let a; //? <+#>
//- duplicate_symbol
export var a; export default function a(){}; //? <-#> @1:39
export let a; export default function a(){}; //? <-#> @1:39
//- duplicate_default_export
export default a; export default b; //? <-#> @1:34
export default a; var b; export {b as default}; //? <-#> @1:39
var a; export {a as default}; export default b; //? <-#> @1:46

/// missing exported reference
//- missing_export_reference
export {a}; //? <-#> @1:9
export {a as b}; //? <-#> @1:9
var a; export {b as a}; //? <-#> @1:16
///
export {a}; var a; //? <+#>
export {a}; let a; //? <+#>
export {a}; for(var a;;); //? <+#>
export {a}; for(let a;;); //? <-#> @1:9
export {a}; function a(){} //? <+#>
export {a}; class a {} //? <+#>
var a; export {a}; //? <+#>
let a; export {a}; //? <+#>
export {a as b}; var a; //? <+#>
export {a as b}; let a; //? <+#>
var a; export {a as b}; //? <+#>
let a; export {a as b}; //? <+#>
///
export {a}; { var a; } //? <+#>
export {a}; { let a; } //? <-#> @1:9
export {a}; { for(var a;;); } //? <+#>
export {a}; { for(let a;;); } //? <-#> @1:9
export {a}; { function a(){} } //? <-#> @1:9
export {a}; { class a {} } //? <-#> @1:9
{ var a; } export {a}; //? <+#>
{ let a; } export {a}; //? <-#> @1:20
