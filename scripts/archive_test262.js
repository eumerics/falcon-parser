const path = require('path');
const child_process = require('child_process');
for(const suite of ['pass', 'pass-explicit', 'fail', 'early']) {
   child_process.spawn(
      path.normalize(`${__dirname}/../test/node_modules/.bin/asar`), [
         'p',
         path.normalize(`${__dirname}/../test/node_modules/test262-parser-tests/${suite}`),
         path.normalize(`${__dirname}/../test/data/test262/${suite}.asar`)
      ], {shell: true}
   );
}
