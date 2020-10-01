import {Parser} from '../src/interface.js';
import disk from 'asar/lib/disk.js';
import * as acorn from 'acorn';
import {object_diff} from './object_diff.js';
import fs from 'fs';
import readline from 'readline';

function test_file(utf8_view, script, is_module)
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

   const diff = (program && acorn_result ? object_diff(program, acorn_result) : undefined);
   return diff;
}

function test_test262_suite()
{
   for(const suite of ['pass', 'pass-explicit']) {
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
         const diff = test_file(utf8_view, script, is_module);
         if(diff !== null) {
            console.log(`\x1b[1;31mtest262/${suite}/${adjusted_path}\x1b[0;m`);
            console.log(script);
         }
      }
      console.groupEnd();
   }
}

function test_falcon_suite_dir(suite_path)
{
   console.group(`\x1b[1;35mfalcon/${suite_path}\x1b[0;m`);
   for(const file of fs.readdirSync(suite_path))
   {
      const file_path = `${suite_path}/${file}`;
      if(fs.statSync(file_path).isDirectory()) {
         test_falcon_suite_dir(file_path);
         continue;
      }
      if(/tsserver/.test(file_path)) continue;
      if(!/\.js$/.test(file_path)) continue;
      //console.log(file_path);
      process.stdout.write(file_path);
      const is_module = /\.module\.js$|\.mjs$/.test(file_path);
      const utf8_view = fs.readFileSync(file_path);
      const script = utf8_view.toString();
      const diff = test_file(utf8_view, script, is_module);
      readline.clearLine(process.stdout);
      readline.cursorTo(process.stdout, 0);
      if(diff !== null) {
         console.log(`\x1b[1;31mtest262/${suite}/${adjusted_path}\x1b[0;m`);
      }
   }
   console.groupEnd();
}

function test_falcon_suite()
{
   for(const suite of ['pass']) {
      test_falcon_suite_dir(`data/${suite}`);
   }
}

(async () => {
   await Parser.load_wasm('../dist/parser.wasm');
   test_test262_suite();
   test_falcon_suite();
})();
