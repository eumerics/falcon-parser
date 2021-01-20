import fs from 'fs';
import {performance} from 'perf_hooks';
import {Worker, isMainThread, parentPort, workerData} from 'worker_threads';
import Benchmark from 'benchmark';

import {fileURLToPath} from 'url';
const __filename = fileURLToPath(import.meta.url);

process.on('unhandledRejection', (reason, p) => {
  console.log('Unhandled Rejection at: Promise', p, 'reason:', reason);
});

const parsers = {
   falcon: {
      name: 'falcon', version: () => '0.x.0',
      make_options: function(_options) {
         let options = {is_module: _options.is_module};
         return options;
      },
      import: async function() {
         this.Parser = (await import('../src/interface.js')).Parser;
         await this.Parser.load_wasm('../dist/parser.wasm');
      },
      init: async function() {
         this.parser = new this.Parser;
      },
      load: function(utf8_vew, script) {
         if(!this.parser.code.view) this.parser.load_script(script);
      },
      parse: function(script, options) {
         const result = this.parser.parse_code(options.is_module, 0);
         const length = result.program.body.length;
         return length;
      },
      free: function() { this.parser.free(); }
   },
   acorn: {
      name: 'acorn', version: function(){ return this.parser.version; },
      make_options: function(_options){
         let options = {locations: _options.locations, ranges: _options.ranges};
         if(_options.ecma_version) options.ecmaVersion = _options.ecma_version;
         if(_options.is_module) options.sourceType = 'module';
         return options;
      },
      import: async function() {
         this.parser = await import('acorn');
      },
      init: function(){},
      load: function(utf8_vew, script){},
      parse: function(script, options){
         const ast = this.parser.parse(script, options);
         return ast.body.length;
      },
      free: function(){}
   },
   meriyah: {
      name: 'meriyah', version: function(){ return this.parser.version; },
      require_directive: () => 'const meriyah = require("meriyah")',
      make_options: function(_options){
         let options = {loc: _options.locations, ranges: _options.ranges};
         if(_options.is_module) options.module = true;
         return options;
      },
      import: async function() {
         this.parser = (await import('meriyah')).default;
      },
      init: function(){},
      load: function(utf8_vew, script){},
      parse: function(script, options){
         const ast = this.parser.parseScript(script, options);
         return ast.body.length;
      },
      free: function(){}
   },
   'tree-sitter': {
      name: 'tree-sitter', version: () => '0.17.1',
      make_options: function(_options){
         let options = {loc: _options.locations, ranges: _options.ranges};
         return options;
      },
      import: async function() {
         this.Parser = (await import('web-tree-sitter')).default;
         await this.Parser.init();
         this.JavaScript = await this.Parser.Language.load(
            'node_modules/web-tree-sitter/tree-sitter-javascript.wasm'
         );
      },
      init: async function(){
         this.parser = new this.Parser;
         this.parser.setLanguage(this.JavaScript);
      },
      load: function(script){},
      parse: function(script, options){
         const ast = this.parser.parse(script);
         const length = ast.rootNode.childCount;
         //tsparser.reset();
         //tsparser.delete();
         return length;
      },
      free: function(){}
   }
};

let invoke_parser = () => {};
const flushed_write = string => new Promise(
   resolve => { process.stdout.write(string, resolve); }
);
const _options = {ecma_version: 2020, locations: true};
const parser_field_length = 18 /*24*/, test_filed_length = 18;
const benchmark_parse = (name, parse, independent) => {
   return new Promise(resolve => {
      const benchmark = new Benchmark(name, parse, {
         defer: independent,
         onComplete: async function(event) {
            const ms = (1000 * this.times.period).toFixed(1).padStart(5);
            const delta = `${Math.round(this.stats.rme)}%`.padStart(3);
            let stats = `${ms} ms ±${delta}`;
            if(this.__memory__) {
               stats = `\`${Math.round(this.__memory__)} MB / ${stats}\``;
            } else {
               stats = `\`${stats}\``;
            }
            await flushed_write('  ' + stats.padStart(parser_field_length) + '|');
            resolve();
         },
         onCycle: (event) => {
            //if(global && global.gc) global.gc();
            //const stats = event.target.stats;
            //console.log(event.target.name, event.target.count, event.target.cycles, stats.sample.length, event.target.times.cycle);
         }
      });
      benchmark.run();
   });
};

(async () => {
   if(isMainThread) {
      const parseArgs = (await import('minimist')).default;

      const libraries = [
         {name: 'jQuery', file: 'jquery-3.5.1.js'},
         {name: 'Angular', file: 'angular-1.8.0.js'},
         {name: 'React', file: 'react-17.0.1.js'},
         //{name: 'TypeScript', file: 'typescript-3.9.7.js'}
      ];

      const args = parseArgs(process.argv.slice(2));
      const independent = !!args.independent;
      await flushed_write('| ' + ''.padStart(test_filed_length) + ' |');
      for await(const parser of Object.values(parsers)) {
         await parser.import(); // just to get version
         const name = `${parser.name}-${parser.version()}`;
         await flushed_write(' ' + name.padStart(parser_field_length) + ' |');
      }
      await flushed_write('\n');
      await flushed_write('|-' + ''.padStart(test_filed_length, '-') + ':|');
      for await(const parser of Object.values(parsers)) {
         await flushed_write('-' + ''.padStart(parser_field_length, '-') + ':|');
      }
      await flushed_write('\n');
      for await(const library of libraries) {
         const file_path = `data/pass/libraries/${library.file}`;
         const utf8_view = fs.readFileSync(file_path);
         const script = utf8_view.toString();
         const worker_data = {utf8_view: utf8_view, script: script};
         await flushed_write('| ' + library.file.padStart(test_filed_length) + ' |');
         for await(const parser of Object.values(parsers)) {
            //if(parser.name != 'falcon') continue;
            //if(use_worker && parser.name != 'falcon') continue;
            const name = `${library.name}-${parser.name}`;
            let parse_event = {library_name: library.name, parser_name: parser.name};
            await new Promise(async resolve => {
               if(independent) {
                  parse_event.action = 'parse';
                  const parse = deferred => {
                     const worker = new Worker(__filename, {workerData: worker_data});
                     worker.on('message', async event => {
                        if(event.message == 'ready') {
                           worker.postMessage(parse_event);
                        } else if(event.message == 'done') {
                           const stats = deferred.benchmark.stats;
                           deferred.resolve();
                           // hack to force the actual elapsed time for parsing excluding
                           // the overhead introduced by the setup and teardown of worker
                           deferred.benchmark.minTime = 0;
                           deferred.elapsed = event.elapsed;
                           //deferred.benchmark._original.__memory__ = event.memory;
                           worker.terminate();
                        }
                     });
                  };
                  await benchmark_parse(name, parse, independent);
                  resolve();
               } else {
                  const worker = new Worker(__filename, {workerData: worker_data});
                  worker.on('message', async event => {
                     if(event.message == 'ready') {
                        parse_event.action = 'benchmark';
                        worker.postMessage(parse_event);
                     } else if(event.message == 'done') {
                        worker.terminate();
                        resolve();
                     }
                  });
               }
            });
         }
         await flushed_write('\n');
      }
   } else {
      parentPort.once('message', async event => {
         const parser = parsers[event.parser_name];
         const name = `${event.library_name}-${event.parser_name}`;
         const options = parser.make_options(_options);
         await parser.import();
         await parser.init();
         await parser.load(workerData.utf8_view, workerData.script);
         if(event.action == 'parse') {
            // perform a single parse
            const begin = performance.now();
            const memory_begin = 0; //process.memoryUsage().heapUsed;
            const result = parser.parse(workerData.script, options);
            const elapsed = (performance.now() - begin) / 1000;
            const memory = (process.memoryUsage().heapUsed - memory_begin) / (1024**2);
            parser.free();
            parentPort.postMessage({message: 'done', result: result, elapsed: elapsed, memory: memory});
         } else {
            // perform multiple parses and extract benchmark details
            const parse = () => {
               const result = parser.parse(workerData.script, options);
               parser.free();
               return result;
            };
            await benchmark_parse(name, parse, false);
            parentPort.postMessage({message: 'done'});
         }
      });
      parentPort.postMessage({message: 'ready'});
   }
})();
