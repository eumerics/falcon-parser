let a, b, c, d, e, f, g, h, i, j, k, l, m, n, o;

export * from 'module';
export * as a from 'module';

export {} from 'module';
export {b} from 'module';
export {c as d} from 'module';
export {e, f as g, h,} from 'module';

export {};
export {i};
export {j as k};
export {l, m as n, o,};

export var p;
export let q;
export const r = 0;

export function s(){}
export function* t(){}
export async function u(){}
export async function* v(){}
export class w {}

export default function x(){}
//export default function* y(){}
//export default async function z(){}
//export default async function* aa(){}
//export default class ab {}

//export default 1;
//export default async;
//export default [ac, ad] = [];
//export default {ae, af} = {};
