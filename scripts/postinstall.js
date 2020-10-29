//require('./archive_test262');

const fs = require('fs');
const url = require('url');
const https = require('https');
const download = function(link, file_path) {
   return new Promise((resolve, reject) => {
      const options = url.parse(link);
      const file = fs.createWriteStream(file_path);
      https.get(options, function(res) {
         res.on('data', function(data) {
            file.write(data);
         }).on('end', function() {
            file.end();
            resolve();
         });
      }).on('error', function(err) {
         file.end();
         reject(err);
      });
   });
};
const tsparser_url = 'https://raw.githubusercontent.com/tree-sitter/tree-sitter.github.io/master/tree-sitter-javascript.wasm';
const tsparser_path = `${__dirname}/../test/node_modules/web-tree-sitter/tree-sitter-javascript.wasm`;
download(tsparser_url, tsparser_path);
