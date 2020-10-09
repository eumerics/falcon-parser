import {Parser} from '../src/interface.js';
import disk from 'asar/lib/disk.js';
import * as acorn from 'acorn';
import Tenko from 'tenko';
import {object_diff} from './object_diff.js';
import fs from 'fs';
import readline from 'readline';
import parse_args from 'minimist';

const arg = parse_args(process.argv.slice(2));

function test_file(utf8_view, script, is_module, is_negative)
{
   const parser = new Parser();
   const params = 0;
   parser.load_utf8_view(utf8_view);
   let program;
   try {
      const parse_result = parser.parse_code(is_module, params);
      program = parse_result.program;
      program = JSON.parse(JSON.stringify(program));
   } catch(e) {
      //console.log(e);
   }
   let reference_result;
   try {
      const source_type = (is_module ? 'module' : 'script');
      const options = {ecmaVersion: 2020, sourceType: source_type};
      reference_result = acorn.parse(script, options);
      //reference_result = Tenko(script, {goalMode: source_type, ranges: true}).ast;
      reference_result = JSON.parse(JSON.stringify(reference_result));
   } catch(e) {
      //console.log(e);
   }
   let result;
   if(is_negative) {
      result = (program ? undefined : null);
      //result = (!program && !reference_result ? null : undefined);
      //if(!program && reference_result) console.log('refernce implementation failed the test');
   } else {
      result = (program && reference_result ? object_diff(program, reference_result) : undefined);
   }
   //if(result !== null) { console.log(program, reference_result); }
   //parser.free();
   return result;
}

function test_test262_suite()
{
   for(const suite of ['fail', 'early', 'pass', 'pass-explicit']) {
   //for(const suite of ['fail', 'pass', 'pass-explicit']) {
      const is_negative = (suite == 'fail' || suite == 'early');
      console.group(`\x1b[1;35mtest262/${suite}\x1b[0;m`);
      const suite_path = `data/test262/${suite}.asar`;
      const asarfs = disk.readFilesystemSync(suite_path);
      for(const path of asarfs.listFiles())
      {
         const adjusted_path = path.substring(1);
         const is_module = /\.module\.js$|\.mjs$/.test(adjusted_path);
         const info = asarfs.getFile(adjusted_path);
         const utf8_view = disk.readFileSync(asarfs, adjusted_path, info);
         const script = utf8_view.toString();
         const diff = test_file(utf8_view, script, is_module, is_negative);
         if(diff !== null) {
            console.log(`\x1b[1;31mtest262/${suite}/${adjusted_path}\x1b[0;m`);
            console.log(script);
         }
      }
      console.groupEnd();
   }
}

function test_segmented_file(file_path, is_module, is_negative)
{
   const utf8_view = fs.readFileSync(file_path);
   const length = utf8_view.byteLength;
   const script = utf8_view.toString();
   function test_script(segment_view) {
      const script = segment_view.toString();
      //console.log(script); console.log('---');
      const diff = test_file(segment_view, script, is_module, is_negative);
      if(diff !== null) {
         if(!test_failed) {
            console.log(`\x1b[1;31mtest262/${file_path}\x1b[0;m`);
         } else {
            console.log('---');
         }
         console.log(script);
         test_failed = true;
      }
   }
   const cr = '\r'.charCodeAt(0);
   const lf = '\n'.charCodeAt(0);
   const slash = '/'.charCodeAt(0);
   const lesser = '<'.charCodeAt(0);
   const greater = '>'.charCodeAt(0);
   let begin = 0, index = 0, test_failed = false;
   while(index < length) {
      let end = index;
      if(utf8_view[index] != slash || index + 4 > length) { ++index; continue; }
      if(utf8_view[++index] != slash ||
         utf8_view[++index] != lesser ||
         utf8_view[++index] != greater
      ) continue;
      if(++index != length) {
         let c = utf8_view[index];
         if(c != cr && c != lf) continue;
         if(c == cr && ++index < length && utf8_view[index] == lf) ++index;
      }
      test_script(utf8_view.subarray(begin, end));
      begin = index;
   }
   if(begin < length) {
      test_script(utf8_view.subarray(begin, length));
   }
}

function test_falcon_suite_dir(suite_path, is_negative)
{
   console.group(`\x1b[1;35mfalcon/${suite_path}\x1b[0;m`);
   for(const file of fs.readdirSync(suite_path))
   {
      const file_path = `${suite_path}/${file}`;
      if(fs.statSync(file_path).isDirectory()) {
         test_falcon_suite_dir(file_path, is_negative);
         continue;
      }
      if(arg.native && /libraries/.test(file_path)) continue;
      if(/tsserver/.test(file_path)) continue;
      if(!/\.js$/.test(file_path)) continue;
      //console.log(file_path);
      const is_module = /\.module\.js$|\.mjs$/.test(file_path);
      if(is_negative) {
         test_segmented_file(file_path, is_module, is_negative);
      } else {
         process.stdout.write(file_path);
         const utf8_view = fs.readFileSync(file_path);
         const script = utf8_view.toString();
         const diff = test_file(utf8_view, script, is_module, is_negative);
         readline.clearLine(process.stdout);
         readline.cursorTo(process.stdout, 0);
         if(diff !== null) {
            console.log(`\x1b[1;31mtest262/${file_path}\x1b[0;m`);
         }
      }
   }
   console.groupEnd();
}

function test_falcon_suite()
{
   for(const suite of ['pass', 'fail']) {
   //for(const suite of ['fail']) {
      test_falcon_suite_dir(`data/${suite}`, suite == 'fail');
   }
}

(async () => {
   await Parser.load_wasm('../dist/parser.wasm');
   if(arg.f) {
      const is_module = !!arg.m, is_negative = !!arg.n;
      if(is_negative) {
         test_segmented_file(arg.f, is_module, is_negative);
      } else {
         const utf8_view = fs.readFileSync(arg.f);
         const script = utf8_view.toString();
         const diff = test_file(utf8_view, script, is_module, is_negative);
         if(diff !== null) {
            console.log(`\x1b[1;31m${arg.f}\x1b[0;m`);
         }
      }
   } else if(arg.s) {
      test_falcon_suite_dir(arg.s, !!arg.n);
   } else {
      if(!arg.native) test_test262_suite();
      test_falcon_suite();
   }
})();
