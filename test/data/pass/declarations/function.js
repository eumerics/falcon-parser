function empty() {}
function identity(a) { return a; }
function rest_only(...b) { return b; }
function rest_mixed(c, ...d) { return d; }
function default_arguments(e, f = 2, g) { return f; }

function* generator_empty() {}
function* generator_identity(a) { yield a; }
function* generator_rest_only(...b) { yield b; }
function* generator_rest_mixed(c, ...d) { yield d; }

async function async_empty() {}
async function async_identity(a) { await a; }
async function async_rest_only(...b) { await b; }
async function async_rest_mixed(c, ...d) { await d; }

async function* async_generator_empty() {}
async function* async_generator_identity(a) { await a; yield a; }
async function* async_generator_rest_only(...b) { await b; yield b; }
async function* async_generator_rest_mixed(c, ...d) { await d; yield d; }

function top_level(a)
{
   let b = 2;
   function nested(c) { return {a: a, b: b, c: c}; }
   function* nested_geneartor(d = 4) { yield {a: a, b: b, d: d}; }
   async function nested_async(e) { await {a: a, b: b, e: e}; }
   async function* nested_async_generator(f) {
      yield {a: a, b: b, f: f};
      await {a: a, b: b, f: f};
   }
}
