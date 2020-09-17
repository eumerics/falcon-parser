/* globals module window */
export function object_diff(actual, expected) {
   var default_diff = {left: actual, right: expected};
   if(typeof actual != typeof expected) return default_diff;
   switch(typeof actual) {
      case 'undefined': return null;
      case 'object': break;
      case 'symbol': case 'function': return default_diff; // unsupported
      default: return actual === expected ? null : default_diff;
   }
   if(actual === null || expected === null) {
      return (actual !== expected ? default_diff : null);
   }
   var proto_of = Object.getPrototypeOf;
   if(proto_of(actual) !== proto_of(expected)) return default_diff;
   if(typeof ArrayBuffer != 'undefined' && proto_of(actual) == ArrayBuffer.prototype){
      actual = new Uint8Array(actual);
      expected = new Uint8Array(expected);
   }
   switch(proto_of(actual)) {
      case Number.prototype:
         return actual === expected ? null : default_diff;
      case Date.prototype:
         return actual.valueOf() == expected.valueOf() ? null : default_diff;
      case RegExp.prototype:
         return actual.source === expected.source &&
                actual.flags === expected.flags ? null: default_diff;
      case Object.prototype: {
         var left_keys = Object.keys(actual).sort().reverse();
         var right_keys = Object.keys(expected).sort().reverse();
         var left = {}, right = {}, has_diff = false;
         for(var li = 0, ri = 0; li < left_keys.length || ri < right_keys.length;) {
            var lkey = (li < left_keys.length ? left_keys[li] : '');
            var rkey = (ri < right_keys.length ? right_keys[ri] : '');
            if(lkey == rkey) {
               ++li, ++ri;
               var d = object_diff(actual[lkey], expected[rkey]);
               if(d === null) continue;
               left[lkey] = d.left, right[rkey] = d.right;
               has_diff = true;
            } else if(lkey > rkey) {
               ++li, left[lkey] = actual[lkey];
               has_diff = true;
            } else {
               ++ri, right[rkey] = expected[rkey];
               has_diff = true;
            }
         }
         // reverse the property assignment (increasing sort order)
         var diff = [['left', left], ['right', right]].reduce(function(diff, arr){
            diff[arr[0]] = Object.keys(arr[1]).sort().reduce(function(side, key){
               side[key] = arr[1][key];
               return side;
            }, {});
            return diff;
         }, {});
         return !has_diff ? null : diff;
      }
      default:
         if(typeof ArrayBuffer == 'undefined' || !ArrayBuffer.isView(actual)){
            return default_diff;
         }
      // fallthrough
      case Array.prototype: {
         if(actual.length != expected.length) return default_diff;
         var left = [], right = [];
         actual.forEach(function(value, index){
            var d = object_diff(actual[index], expected[index]);
            if(d === null) return;
            //console.log(require('util').inspect(d.left, {depth: 3}));
            //console.log(require('util').inspect(d.right, {depth: 3}));
            left.push(d.left), right.push(d.right);
         });
         return left.length == 0 ? null : {left: left, right: right};
      }
   }
}
