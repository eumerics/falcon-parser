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
///   var-var
export var a, a; //? <-#>
export var [a, a] = []; //? <-#>
export var a; export var a; //? <-#>
export var a; var a; //? <+#>
export var [a] = []; var a; //? <+#>
export var {a} = {}; var a; //? <+#>
var a; export var a; //? <+#>
var a; export var [a] = []; //? <+#>
var a; export var {a} = {}; //? <+#>
///   let-let
export let a, a; //? <-#>
export let [a, a] = []; //? <-#>
export let a; export let a; //? <-#>
export let a; let a; //? <-#>
export let [a] = []; let a; //? <-#>
export let {a} = {}; let a; //? <-#>
export let a; { let a; } //? <+#>
export let [a] = []; { let a; } //? <+#>
export let {a} = {}; { let a; } //? <+#>
let a; export let a; //? <-#>
let a; export let [a] = []; //? <-#>
let a; export let {a} = {}; //? <-#>
{ let a; } export let a; //? <+#>
{ let a; } export let [a] = []; //? <+#>
{ let a; } export let {a} = {}; //? <+#>
///   var-let
export var a; export let a; //? <-#>
export let a; export var a; //? <-#>
export var a; let a; //? <-#>
export var [a] = []; let a; //? <-#>
export var {a} = {}; let a; //? <-#>
export var a; { let a; } //? <+#>
export var [a] = []; { let a; } //? <+#>
export var {a} = {}; { let a; } //? <+#>
var a; export let a; //? <-#>
var a; export let [a] = []; //? <-#>
var a; export let {a} = {}; //? <-#>
///   let-var
export let a; export var a; //? <-#>
export let a; var a; //? <-#>
export let [a] = []; var a; //? <-#>
export let {a} = {}; var a; //? <-#>
let a; export var a; //? <-#>
let a; export var [a] = []; //? <-#>
let a; export var {a} = {}; //? <-#>
{ let a; } export var a; //? <+#>
{ let a; } export var [a] = []; //? <+#>
{ let a; } export var {a} = {}; //? <+#>
/// named-var, named-let
export {a}; export var a; //? <-#>
export {a}; export let a; //? <-#>
export var a; export {a}; //? <-#>
export let a; export {a}; //? <-#>
export {a as b}; export var a; //? <+#>
export {a as b}; export let a; //? <+#>
export var a; export {a as b}; //? <+#>
export let a; export {a as b}; //? <+#>
var a; export {a as b}; var b; //? <+#>
var a; export {a as b}; let b; //? <+#>
var a; var b; export {a as b}; //? <+#>
var a; let b; export {a as b}; //? <+#>
var a; export {a as b}; export var b; //? <-#>
var a; export {a as b}; export let b; //? <-#>
var a; export var b; export {a as b}; //? <-#>
var a; export let b; export {a as b}; //? <-#>
/// default-var default-let
export var a; export default a; //? <+#>
export let a; export default a; //? <+#>
export default a; export var a; //? <+#>
export default a; export let a; //? <+#>
export var a; export default function a(){}; //? <-#>
export let a; export default function a(){}; //? <-#>
export default a; export default b; //? <-#>

/// missing exported reference
export {a}; //? <-#>
export {a as b}; //? <-#>
var a; export {b as a}; //? <-#>
///
export {a}; var a; //? <+#>
export {a}; let a; //? <+#>
export {a}; for(var a;;); //? <+#>
export {a}; for(let a;;); //? <-#>
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
export {a}; { let a; } //? <-#>
export {a}; { for(var a;;); } //? <+#>
export {a}; { for(let a;;); } //? <-#>
export {a}; { function a(){} } //? <-#>
export {a}; { class a {} } //? <-#>
{ var a; } export {a}; //? <+#>
{ let a; } export {a}; //? <-#>
