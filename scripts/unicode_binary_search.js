const fs = require('fs');
const file_name = process.argv[2];
const content = fs.readFileSync(file_name).toString();
const property = file_name.replace(/^(?:.+\/)?([^/]+)\.[^.]+$/, '$1');

let range_first, range_last, ranges = [];
const pad = (s, n1, n2, c) => (
   (Array(s.length > n1 ? n2 : n1).fill(c).join('') + s).substring(s.length)
);
const hex_literal = n => '0x' + pad(n.toString(16).toUpperCase(), 4, 6, '0');
for(const line of content.split(/\r\n?|\n/g))
{
   if(line.length == 0 || line.startsWith('#')) continue;
   let [first, last = first] = line.split(';')[0].trim().split('..');
   [first, last] = [first, last].map(x => Number(`0x${x}`));
   // join consequent ranges
   if(range_last + 1 == first){
      range_last = last;
   } else {
      if(range_first !== undefined) {
         //if(!((range_first & 0xffffff80) == 0 && (range_last & 0xffffff80) == 0)) {
            ranges.push({first: range_first, last: range_last});
            //console.log(hex_literal(range_first), hex_literal(range_last));
         //}
      }
      range_first = first;
      range_last = last;
   }
}
ranges.push({first: range_first, last: range_last});
function generate_binary_lookup_tree_code(ranges, indent) {
   indent += '   ';
   if(ranges.length == 1) {
      console.log(`${indent}return (c >= ${hex_literal(ranges[0].first)} && c <= ${hex_literal(ranges[0].last)});`);
   } else {
      const center = Math.ceil(ranges.length / 2);
      const ranges_left = ranges.slice(0, center);
      const ranges_right = ranges.slice(center, ranges.length);
      console.log(`${indent}if(c < ${hex_literal(ranges[center].first)}){`)
      generate_binary_lookup_tree_code(ranges_left, indent);
      console.log(`${indent}} else {`);
      generate_binary_lookup_tree_code(ranges_right, indent);
      console.log(`${indent}}`);
   }
}

//console.log(hex_literal(range_first), hex_literal(range_last));
console.log(`int is_unicode_${property}(uint32_t c){`);
generate_binary_lookup_tree_code(ranges, '');
console.log('}');
