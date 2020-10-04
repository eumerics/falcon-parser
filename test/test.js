import {Parser} from '../src/interface.js';
import disk from 'asar/lib/disk.js';
import * as acorn from 'acorn';
import {object_diff} from './object_diff.js';
import fs from 'fs';
import readline from 'readline';

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
   }
   let acorn_result;
   try {
      const options = {ecmaVersion: 2020, sourceType: is_module ? 'module' : 'script'};
      acorn_result = acorn.parse(script, options);
      acorn_result = JSON.parse(JSON.stringify(acorn_result));
   } catch(e) {
   }
   if(is_negative) {
      return (!program && !acorn_result ? null : undefined);
   } else {
      return (program && acorn_result ? object_diff(program, acorn_result) : undefined);
   }
}

function test_test262_suite()
{
   for(const suite of ['fail', 'pass', 'pass-explicit']) {
      const is_negative = (suite == 'fail');
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
   let begin = 0, index = 0, test_failed = false;
   function test_script(segment_view) {
      const script = segment_view.toString();
      //console.log(script); console.log('---')
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
   while(index < length) {
      let code_end;
      if(index != 0) {
         let c = utf8_view[index++];
         if(c != cr && c != lf) continue;
         code_end = index - 1;
         if(c == cr && index < length && utf8_view[index] == lf) ++index;
      } else {
         code_end = 0;
      }
      let marker_begin = index, marker_length = 0;
      while(
         index < length && marker_length < 4 &&
         utf8_view[index] != cr && utf8_view[index] != lf
      ) ++index, ++marker_length;
      //console.log(marker_length, utf8_view[marker_begin]);
      if(
         marker_length != 4 ||
         utf8_view[marker_begin++] != slash ||
         utf8_view[marker_begin++] != slash ||
         utf8_view[marker_begin++] != lesser ||
         utf8_view[marker_begin++] != greater
      ) continue;
      let c = utf8_view[index++];
      if(c == cr && index < length && utf8_view[index] == lf) ++index;
      test_script(utf8_view.subarray(begin, code_end));
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
   test_test262_suite();
   test_falcon_suite();
})();
