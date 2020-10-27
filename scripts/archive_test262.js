const fs = require('fs');
const path = require('path');
const child_process = require('child_process');
const base = `${__dirname}/../test/node_modules/test262-parser-tests`;
const incorrect_fail_tests = [
   '0d5e450f1da8a92a.js', // ('\9')
   '748656edbfb2d0bb.js', // ('\8')
   '79f882da06f88c9f.js', // "\8";
   '92b6af54adef3624.js', // "\9";
   '647e21f8f157c338.js', // '<LS>'
   '8af69d8f15295ed2.js', // '<PS>'
   'e3fbcf63d7e43ead.js'  // for-in var initializer
];
const incorrect_early_tests = [
   '0f5f47108da5c34e.js',
   '12a74c60f52a60de.js',
   '1aff49273f3e3a98.js',
   'be7329119eaa3d47.js',
   'ec31fa5e521c5df4.js'
];
for(const test_name of incorrect_fail_tests) {
   const file_path = path.normalize(`${base}/fail/${test_name}`);
   if(fs.existsSync(file_path)) fs.renameSync(file_path, `${base}/pass/${test_name}`);
}
for(const test_name of incorrect_early_tests) {
   const file_path = path.normalize(`${base}/early/${test_name}`);
   if(fs.existsSync(file_path)) fs.renameSync(file_path, `${base}/pass/${test_name}`);
}
for(const suite of ['pass', 'pass-explicit', 'fail', 'early']) {
   child_process.spawn(
      path.normalize(`${__dirname}/../test/node_modules/.bin/asar`), [
         'p',
         path.normalize(`${base}/${suite}`),
         path.normalize(`${__dirname}/../test/data/test262/${suite}.asar`)
      ], {shell: true}
   );
}
