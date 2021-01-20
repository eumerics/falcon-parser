# Falcon Parser

A blazing fast, memory efficient ECMAScript parser written in C and compiled to WebAssembly. It is a standalone library with no dependencies and a lean code. The library can be compiled to WebAssembly without the need for heavy toolchains such as Emscripten. Hence the glue code required to load the WebAssembly code is minimal.


# Performance

On average `falcon` parser is **5x-7x** faster than the best performing cold run library `web-tree-sitter`, while **3x-4x** faster than the best performing hot run library `meriyah`.

Benchmark results of cold parse times computed with [benchmark.js](https://benchmarkjs.com/) library are tabulated below. Each parse is executed in a separate worker thread to prevent JIT compiler optimizations from kicking in.

|                    |       falcon-0.x.0 |        acorn-8.0.1 |      meriyah-2.1.0 | tree-sitter-0.17.1 |
|-------------------:|-------------------:|-------------------:|-------------------:|-------------------:|
|    jquery-3.5.1.js |     `  6.9 ms ± 3%`|     `127.6 ms ± 1%`|     ` 83.1 ms ± 1%`|     ` 45.0 ms ± 2%`|
|   angular-1.8.0.js |     ` 22.0 ms ± 2%`|     `217.3 ms ± 1%`|     `176.0 ms ± 1%`|     `108.8 ms ± 3%`|
|    react-17.0.1.js |     `  2.6 ms ± 3%`|     ` 64.9 ms ± 1%`|     ` 51.4 ms ± 3%`|     ` 18.4 ms ± 4%`|

Tabulated below are the benchmark results of hot parse times which reflect JIT compiler optimizations that kick in after repetitive invocations of parsing possibly within a short span of time.

|                    |       falcon-0.x.0 |        acorn-8.0.1 |      meriyah-2.1.0 | tree-sitter-0.17.1 |
|-------------------:|-------------------:|-------------------:|-------------------:|-------------------:|
|    jquery-3.5.1.js |     `  4.6 ms ± 1%`|     ` 24.4 ms ± 8%`|     ` 16.6 ms ±18%`|     ` 38.8 ms ± 1%`|
|   angular-1.8.0.js |     ` 10.0 ms ± 1%`|     ` 53.5 ms ± 8%`|     ` 45.7 ms ±13%`|     ` 99.1 ms ± 1%`|
|    react-17.0.1.js |     `  1.3 ms ± 1%`|     `  3.9 ms ± 1%`|     `  2.2 ms ± 2%`|     ` 12.0 ms ± 1%`|

##### Caveats
The above benchmarks measure pure parsing performance. Accessing syntax tree built on the WebAssembly side via JavaScript bindings introduces additional overheads. [WebAssembly GC Propsoal](https://github.com/WebAssembly/gc/blob/master/proposals/gc/Overview.md "WebAssembly GC Propsoal") will reduce these overheads.
