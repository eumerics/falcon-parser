import {Parser} from '../src/interface.js';
import TSParser from 'web-tree-sitter';
import Tenko from 'tenko';

(async () => {
   /*
   {
      let start = new Date;
      for(let it = 0; it < 1000; ++it) {
         tokenize(data_string, 0, data_string.length);
      }
      console.log((new Date - start));
   }
   */
   //console.log(await parse_file('../../data/jquery-3.5.1.js'));
   ///*
   if(!process.versions || !process.versions.electron) {
      let args = (await import('minimist')).default(process.argv.slice(2));
      await Parser.load_wasm('../dist/parser.wasm');
      let parser = new Parser();
      if(args.f) {
         const is_module = /\.module\.js$|\.mjs$/.test(args.f);
         const params = (args.s ? Parser.constants.param_flag_streaming: 0)
         if(args.b) {
            let result;
            await parser.load_file(args.f);
            let start = new Date;
            let iterations = args.i || 1000;
            let parse_result;
            for(let it = 0; it < iterations; ++it) {
               parse_result = parser.parse_code(is_module, params);
               if(it != iterations - 1) parser.free();
            }
            const elapsed = (new Date - start) / iterations;
            const program = parse_result.program;
            if(args.s) {
               console.log(elapsed);
            } else {
               const script = parser.code.utf8_view.toString();
               const source_type = (is_module ? 'module' : 'script');
               const acorn = await import('acorn');
               const options = {ecmaVersion: 2020, sourceType: source_type, locations: true, sourceFile: ''};
               let acorn_result;
               start = new Date();
               for(let it = 0; it < iterations; ++it) {
                  acorn_result = acorn.parse(script, options);
               }
               const acorn_elapsed = (new Date - start) / iterations;
               const meriyah = (await import('meriyah')).default;
               //
               let meriyah_result;
               start = new Date();
               for(let it = 0; it < iterations; ++it) {
                  meriyah_result = meriyah.parseScript(script, {loc: true});
               }
               const meriyah_elapsed = (new Date - start) / iterations;
               //
               let tenko_result;
               start = new Date();
               for(let it = 0; it < iterations; ++it) {
                  tenko_result = Tenko(script, {goalMode: source_type, sourceField: ''});
               }
               const tenko_elapsed = (new Date - start) / iterations;
               //
               await TSParser.init();
               const tsparser = new TSParser;
               const JavaScript = await TSParser.Language.load('node_modules/web-tree-sitter/tree-sitter-javascript.wasm');
               tsparser.setLanguage(JavaScript);
               let tsparser_result;
               start = new Date();
               for(let it = 0; it < iterations; ++it) {
                  tsparser_result = tsparser.parse(script);
               }
               const tsparser_elapsed = (new Date - start) / iterations;
               //
               console.log(
                  'falcon:', elapsed, 'acorn:', acorn_elapsed,
                  'meriyah:', meriyah_elapsed, 'tenko:', tenko_elapsed,
                  'tree-parser:', tsparser_elapsed
               );
            }
         } else {
            const parse_result = await parser.parse_file(args.f, is_module, params);
            const program = parse_result.program;
            if(args.c) {
               const acorn = await import('acorn');
               const source_type = (is_module ? 'module' : 'script');
               const options = {ecmaVersion: 2020, sourceType: source_type, locations: true, sourceFile: ''};
               const fs = await import('fs');
               const script = fs.readFileSync(args.f).toString();
               let reference_result;
               reference_result = acorn.parse(script, options);
               //reference_result = Tenko(script, {goalMode: source_type, sourceField: '', ranges: true}).ast;
               //reference_result = Tenko(script, {goalMode: source_type, sourceField: ''}).ast;
               const {object_diff} = await import('./object_diff.js');
               let sb = new Date; const s = JSON.stringify(program); let se = new Date - sb;
               let tb = new Date; const t = JSON.stringify(reference_result); let te = new Date - tb;
               let spb = new Date; const source = JSON.parse(s); let spe = new Date - spb;
               const target = JSON.parse(t);
               if(!args.nodump) {
                  fs.writeFileSync('../.ignore/log1', JSON.stringify(source, null, '   '));
                  fs.writeFileSync('../.ignore/log2', JSON.stringify(target, null, '   '));
               }
               const diff = object_diff(source, target);
               console.log(JSON.stringify(diff, null, '   '));
               let vt = new Date; program.visit(); let visitation_time = new Date - vt;
               //console.log('visitation', visitation_time, Parser.visitation_count, spe);
               //console.log('stringification times', se, Parser.to_json_time, Parser.list_time, te);
            } else {
               console.log(JSON.stringify(program, null, '   '));
            }
            //console.log(JSON.stringify(result.program, null, ' '));
         }
      }
   }
   //*/
   {
      /*

      /*
      start = new Date();
      let tkn_base = 0x80, base = 0xc0;
      let symbols = new Map();
      symbols.set(tkn_base + 1, Symbol('numeric_literal'));
      symbols.set(tkn_base + 2, Symbol('string_literal'));
      symbols.set(tkn_base + 3, Symbol('regexp_literal'));
      symbols.set(tkn_base + 4, Symbol('identifier'));
      symbols.set(tkn_base + 5, Symbol('punctuator'));
      symbols.set(tkn_base + 6, Symbol('terminator'));
      symbols.set(tkn_base + 7, Symbol('whitespace'));
      symbols.set(tkn_base + 8, Symbol('comment'));
      symbols.set(tkn_base + 9, Symbol('keyword'));
      symbols.set(base + 0, Symbol('await'));
      symbols.set(base + 1, Symbol('break'));
      symbols.set(base + 2, Symbol('case'));
      symbols.set(base + 3, Symbol('catch'));
      symbols.set(base + 4, Symbol('class'));
      symbols.set(base + 5, Symbol('const'));
      symbols.set(base + 6, Symbol('continue'));
      symbols.set(base + 7, Symbol('debugger'));
      symbols.set(base + 8, Symbol('default'));
      symbols.set(base + 9, Symbol('delete'));
      symbols.set(base + 10, Symbol('do'));
      symbols.set(base + 11, Symbol('else'));
      symbols.set(base + 12, Symbol('enum'));
      symbols.set(base + 13, Symbol('export'));
      symbols.set(base + 14, Symbol('extends'));
      symbols.set(base + 15, Symbol('false'));
      symbols.set(base + 16, Symbol('finally'));
      symbols.set(base + 17, Symbol('for'));
      symbols.set(base + 18, Symbol('function'));
      symbols.set(base + 19, Symbol('if'));
      symbols.set(base + 20, Symbol('import'));
      symbols.set(base + 21, Symbol('in'));
      symbols.set(base + 22, Symbol('instanceof'));
      symbols.set(base + 23, Symbol('new'));
      symbols.set(base + 24, Symbol('null'));
      symbols.set(base + 25, Symbol('return'));
      symbols.set(base + 26, Symbol('super'));
      symbols.set(base + 27, Symbol('switch'));
      symbols.set(base + 28, Symbol('this'));
      symbols.set(base + 29, Symbol('throw'));
      symbols.set(base + 30, Symbol('true'));
      symbols.set(base + 31, Symbol('try'));
      symbols.set(base + 32, Symbol('typeof'));
      symbols.set(base + 33, Symbol('var'));
      symbols.set(base + 34, Symbol('void'));
      symbols.set(base + 35, Symbol('while'));
      symbols.set(base + 36, Symbol('with'));
      symbols.set(base + 37, Symbol('yield'));
      symbols.set(base + 38, Symbol('implements'));
      symbols.set(base + 39, Symbol('interface'));
      symbols.set(base + 40, Symbol('package'));
      symbols.set(base + 41, Symbol('private'));
      symbols.set(base + 42, Symbol('protected'));
      symbols.set(base + 43, Symbol('public'));

      let token_size = 12;
      //let pointer = result[0], token_count = result[1];
      let pointer = result[2], token_count = (result[3] - result[2]) / token_size + 1;
      result = new Uint32Array(memory.buffer, pointer, token_size*token_count/4);
      let tokens = new Array(token_count);
      for(let i = 0; i < 3*token_count; i += 3) {
         let begin = result[i], end = result[i + 1];
         let value = result[i + 2];
         let type = value & 0xff;
         let id = (value >> 8) & 0xff;
         let group = (value >> 16) & 0xffff;
         tokens[i/3] = {
            type: symbols.get(type), id: symbols.get(id) || id,
            value: data_string.substring(begin, end),
            group: group, begin: begin, end: end
         }
      }
      console.log('token binding took', (new Date - start));
      //console.log(tokens);
      //*/
   }
})();

//return exports;
//});
