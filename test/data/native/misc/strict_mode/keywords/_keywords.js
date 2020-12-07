import fs from 'fs';
import url from 'url';
import path from 'path';

const file_path = url.fileURLToPath(import.meta.url);
const template_path = file_path.replace(/\.js$/, '.tmpl.js');
if(template_path == file_path) {
   throw 'template and file paths are identical';
}
const parsed = path.parse(file_path);
const output_path = path.join(parsed.dir, parsed.base.replace(/^_/, ''));
if(output_path == file_path) {
   throw 'template and file paths are identical';
}
const test_dir_re = new RegExp(`${path.sep}test${path.sep}.+`);
const test_dir = file_path.replace(test_dir_re, `${path.sep}test`);

(async () => {
   const Expander = (await import(path.join(test_dir, 'expander.js'))).default;
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
   let template = fs.readFileSync(template_path).toString();
   let expander = new Expander(output_path, config);
   expander.group_expand(template);
   expander.write();
})();
