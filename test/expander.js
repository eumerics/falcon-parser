import fs from 'fs';
import path from 'path';

export default class Expander {
   constructor(output_path, config) {
      this.test = '';
      this.config = config;
      this.output_path = output_path;
   }
   expand(template, error, overrides, config) {
      template = template.trim();
      overrides = overrides || {};
      config = config || this.config;
      let expanded = (error ? `//- ${error}\r\n` : '///\r\n');
      for(const keyword of config.keywords) {
         let _test = template.replace(/keyword/g, keyword);
         const override = overrides[keyword];
         if(override) _test = _test.replace(/\/\/\? .+$/, override);
         expanded += _test + '\r\n';
      }
      expanded += '\r\n';
      this.test += expanded;
   }
   group_expand(template, errors, config) {
      template = template.trim();
      config = config || this.config;
      errors = errors || this.config.errors;
      for(const keyword of config.keywords) {
         const error = errors[keyword] || errors.__default__ || 'default';
         this.test += `//- ${error}\r\n`;
         let replaced = template.replace(/keyword/g, keyword);
         let override_error = config.error_overrides.has(keyword);
         if(override_error) {
            // convert non-overrided tests to positive tests
            replaced = replaced.replace(/\/\/\? <+->[^\r\n$]*(?=[\r\n]|$)/g, '//? <+>');
         }
         replaced = replaced.replace(
            /(<[+-]>.*) \$override[\r\n]+\/\*([^*]+)\*\//g,
            (pattern, match1, match2) => {
               const overrides = JSON.parse(match2);
               const override = overrides[keyword];
               const skip = overrides['skip-error-override'];
               return override || (override_error && !skip ? '<+>' : match1);
            }
         )
         this.test += replaced + '\r\n\r\n';
      }
   }
   write() {
      fs.writeFileSync(this.output_path, this.test);
   }
}
