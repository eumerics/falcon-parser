import fs from 'fs';
import url from 'url';
import path from 'path';

const file_path = url.fileURLToPath(import.meta.url);
const parsed = path.parse(file_path);
const test_dir_re = new RegExp(`${path.sep}test${path.sep}.+`);
const test_dir = file_path.replace(test_dir_re, `${path.sep}test`);

(async () => {
   const Expander = (await import(path.join(test_dir, 'expander.js'))).default;
   {
      const config = {
         keywords: [
            'break', 'case', 'catch', 'class', 'const', 'continue', 'debugger',
            'default', 'delete', 'do', 'else', 'enum', 'export', 'extends',
            'false', 'finally', 'for', 'function', 'if', 'import', 'in',
            'instanceof', 'new', 'null', 'return', 'super', 'switch', 'this',
            'throw', 'true', 'try', 'typeof', 'var', 'void', 'while', 'with'
         ]
      }
      //const template_path = path.join(parsed.dir, '_contextual.tmpl.js');
      const output_path = path.join(parsed.dir, 'reserved_words.js');
      let expander = new Expander(output_path, config);
      expander.expand('!{keyword: 0}; //? <+>');
      expander.expand('a.keyword; //? <+>');
      expander.expand('var keyword; //? <-> @1:5', 'reserved_word_as_variable');
      expander.expand('let keyword; //? <-> @1:5', 'expect ;', {
         in: '//? <-> @1:7 -default', instanceof: '//? <-> @1:15 -default'
      });
      expander.expand('const keyword = 0; //? <-> @1:7', 'reserved_word_as_variable');
      expander.expand(`'use strict'; let keyword; //? <-> @1:19`, 'reserved_word_as_variable');
      expander.write();
   }
   {
      const config = {
         keywords: [
            'eval', 'arguments', 'yield', 'await',
            'let', 'static', 'implements', 'interface',
            'package', 'private', 'protected', 'public'
         ],
         errors: {
            eval: 'eval_args_in_strict_mode',
            arguments: 'eval_args_in_strict_mode',
            yield: 'yield_in_strict_mode',
            await: 'await_in_module',
            __default__: 'invalid_strict_mode_identifier'
         },
         error_overrides: new Set(['await'])
      }
      const template_path = path.join(parsed.dir, '_keywords.tmpl.js');
      const output_path = path.join(parsed.dir, 'strict_mode.js');
      let template = fs.readFileSync(template_path).toString();
      let expander = new Expander(output_path, config);
      expander.group_expand(template);
      expander.write();
   }
   {
      const keywords = ['as', 'async', 'from', 'get', 'of', 'set', 'target'];
      const config = {
         keywords: keywords, errors: {},
         error_overrides: new Set(keywords)
      }
      const template_path = path.join(parsed.dir, '_keywords.tmpl.js');
      const output_path = path.join(parsed.dir, 'contextual.js');
      let template = fs.readFileSync(template_path).toString();
      let expander = new Expander(output_path, config);
      expander.group_expand(template);
      expander.write();
   }
})();
