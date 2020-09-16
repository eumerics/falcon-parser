define([], async function(){

/*
const is_node = (new Function(
   "try {return this === global;} catch(e) {return false;}"
))();
*/
let use_utf16;
const is_node = (typeof process !== 'undefined' && process.versions && !process.versions.electron);
const is_electron = (typeof process !== 'undefined' && process.versions && process.versions.electron);
let read_file;
if(is_node || is_electron) {
   let fs = require('fs');
   read_file = name => fs.readFileSync(name);
} else {
   read_file = async name => {
      const response = await fetch(name);
      const bytes = await response.arrayBuffer();
      return bytes;
   }
}
if(is_node) {
   const color_escape_code = {
      red: 31, green: 32, magenta: 35, cyan: 36, black: 90
   };
   function colored_log(color, message) {
      console.log(`\x1b[1;${color_escape_code[color]}m${message}\x1b[0m`);
   }
} else if(is_electron) {
   function colored_log(color, message) {
      console.log(`%c${message}`, `color: ${color}`);
   }
}
function utf8_to_utf16(utf8_view) {
   const utf16_buffer = new ArrayBuffer(2 * utf8_view.byteLength);
   const utf16_view = new Uint16Array(utf16_buffer);
   const check_prefix = (byte, mask, filter) => (((byte & mask) ^ filter) == 0);
   const ensure_prefix = (byte, mask, filter) => {
      if(!check_prefix(byte, mask, filter)) throw 'UTF-8 encoding error';
      return true;
   };
   let j = 0;
   for(let i = 0; i < utf8_view.length;) {
      let code_length, first_bits;
      const rest_bits = 6;
      const byte = utf8_view[i];
      if(check_prefix(byte, 0x80, 0x00)) [code_length, first_bits] = [1, 7];
      else if(check_prefix(byte, 0xe0, 0xc0)) [code_length, first_bits] = [2, 5];
      else if(check_prefix(byte, 0xf0, 0xe0)) [code_length, first_bits] = [3, 4];
      else if(ensure_prefix(byte, 0xf8, 0xf0)) [code_length, first_bits] = [4, 3];
      //if(code_length == 1) { utf16_view[j++] = byte; ++i; continue; }
      const rest = new Uint8Array(utf8_view.buffer, utf8_view.byteOffset + i + 1, code_length - 1);
      for(const byte of rest) ensure_prefix(byte, 0xc0, 0x80);
      let code = byte & ((0x01 << first_bits) - 1), bits = first_bits;
      for(const byte of rest){ code = (code << rest_bits) | (byte & 0x3f); bits += rest_bits; }
      if(code & 0xffff0000) {
         code -= 0x10000;
         utf16_view[j + 1] = (0b110111 << 10) | (code & 0x3ff); code >>= 10;
         utf16_view[j + 0] = (0b110110 << 10) | (code & 0x3ff); code >>= 10;
         j += 2;
      } else {
         utf16_view[j++] = code;
      }
      i += code_length;
   }
   return new Uint16Array(utf16_buffer, 0, j);
}
async function load_file(file_name) {
   let code_utf8_view = await read_file(file_name);
   let code_view;
   if(use_utf16) {
      // convert from UTF-8 to UTF-16
      const code_string = (new TextDecoder('utf-8')).decode(code_utf8_view);
      //let a = []; for(let i = 0; i < code_string.length; ++i) a.push(code_string.charCodeAt(i)); console.log(a);
      const code_utf16_view = utf8_to_utf16(code_utf8_view);
      //console.log(code_utf16_view);
      code_view = code_utf16_view;
   } else {
      code_view = code_utf8_view;
   }
   const index = instance.exports.malloc(code_view.byteLength);
   const shared_memory = new Uint8Array(memory.buffer);
   const code_uint8_view = new Uint8Array(code_view.buffer, code_view.byteOffset, code_view.byteLength);
   shared_memory.set(code_uint8_view, index);
   return {pointer: index, view: code_view, utf8_view: code_utf8_view};
}
function parse_code(code) {
   let result_size = 4096; //[BUG] large enough for now to now worry about actual size
   let result_pointer = instance.exports.malloc(result_size);
   instance.exports.parse(result_pointer, code.pointer, code.pointer + code.view.byteLength);
   let result = new Uint32Array(memory.buffer, result_pointer, result_size/4);
   return {value: result, pointer: result_pointer};
}
function bind_parse_tree(code, result) {
   let buffer = memory.buffer;
   let buffer_view = {
      buffer: buffer,
      u08: new Uint8Array(buffer),
      u16: new Uint16Array(buffer),
      u32: new Uint32Array(buffer),
      code: code.view
   };
   let TypedArray = (use_utf16 ? Uint16Array : Uint8Array);
   let code_view = new TypedArray(buffer, result.value[1], code.view.length);
   let program = new Program(buffer_view, result.value[0]);
   return {result: result, program: program};
}
function free(result) {
   //instance.exports.wasm_free(result.value[0]);
   instance.exports.parser_free(result.pointer + 4);
   instance.exports.wasm_free(result.pointer);
}
const parse_file = async (file_name) => {
   let code = await load_file(file_name);
   let result = parse_code(code);
   return bind_parse_tree(code, result);
}

const env = {
   show_token_type: function(index){
      let index_begin = index;
      //while(index < shared_memory.length && shared_memory[index++] != 0);
      let string_buffer = memory.buffer.slice(index_begin, index);
      let string = new TextDecoder('utf-8').decode(string_buffer);
      console.log(string);
   },
   show_token: function(format_index, length, index) {
      let string_buffer = memory.buffer.slice(index, index + length);
      let string = new TextDecoder('utf-8').decode(string_buffer);
      console.log(string);
   },
   /*
   log_token: function(format_index, length, index, id, group, begin, end) {
      console.log(index, id, group, begin, end);
      let string_buffer = memory.buffer.slice(index, index + length);
      let string = new TextDecoder('utf-8').decode(string_buffer);
      //console.log(string);
   },
   */
   log_string: function(pointer, length) {
      if(length < 32) {
         console.log(
            utf8_decoder.decode(new Uint8Array(memory.buffer, pointer, length))
         );
      } else {
         console.log('string is too long');
      }
   },
   begin_group_impl: function(pointer, length) {
      if(length < 32) {
         console.groupCollapsed(
            utf8_decoder.decode(new Uint8Array(memory.buffer, pointer, length))
         );
      } else {
         console.groupCollapsed('string is too long');
      }
   },
   end_group: function() { console.groupEnd(); },
   log_pointer: function(pointer) { console.log('pointer', pointer); },
   log_node: function(){ console.log(...arguments); },
   //print: function() { console.log(...arguments); }
   log_parse_descent: function(type_pointer, type_length, depth, params) {
      const type_view = new Uint8Array(memory.buffer, type_pointer, type_length);
      let title = Array(depth < 0 ? 0 : depth % 60).fill(' ').join('') + '=> ';
      title += utf8_decoder.decode(type_view);
      const flags = [
         ['param_flag_await', 'await'],
         ['param_flag_default', 'default'],
         ['param_flag_in', 'in'],
         ['param_flag_return', 'return'],
         ['param_flag_yield', 'yield'],
         ['cover_flag_initializer', 'cover-init'],
         ['cover_flag_parameters', 'cover-params'],
         ['param_flag_for_binding', 'for-binding']
      ];
      title += ' (';
      for(const [flag, label] of flags) {
         if(params & constants[flag]) title += ` ${label}`;
      }
      title += ` ) [${depth}]`;
      console.log(title);
      //console.groupCollapsed(title);
   },
   log_parse_ascent: function(depth, node) {
      let space = Array(depth < 0 ? 0 : depth % 60).fill(' ').join('');
      console.log(`${space}<= [${depth}] ${node == 0 ? 'nullptr' : ''}`);
      //console.groupEnd();
   },
   log_token: function(token_pointer, length) {
      const TypedArray = (use_utf16 ? Uint16Array : Uint8Array);
      const token_view = (new TypedArray(memory.buffer, token_pointer)).subarray(0, length);
      const token = (length < 512 ? decoder.decode(token_view) : '[too long]');
      console.log(token);
   },
   log_token_consumption: function(code_pointer, begin, end, depth) {
      let space = Array(depth < 0 ? 0 : depth % 60).fill(' ').join('');
      const TypedArray = (use_utf16 ? Uint16Array : Uint8Array);
      const token_view = (new TypedArray(memory.buffer, code_pointer)).subarray(begin, end);
      const token = (end - begin < 32 ? decoder.decode(token_view) : '[too long]');
      colored_log('cyan', `${space}consumed token ${token}`);
   },
   log_make_node: function(type_pointer, type_length, depth) {
      let space = Array(depth < 0 ? 0 : depth % 60).fill(' ').join('');
      const type_view = new Uint8Array(memory.buffer, type_pointer, type_length);
      let type = utf8_decoder.decode(type_view);
      colored_log('magenta', `${space}making node ${type}`);
   },
   log_assertion: function(file_name_pointer, length, line_number) {
      const file_name_view = (new Uint8Array(memory.buffer, file_name_pointer)).subarray(0, length);
      const file_name = utf8_decoder.decode(file_name_view);
      console.error(`assertion failed at ${file_name}:${line_number}`);
   }
}
const bytes = await read_file('../../dist/parser.wasm')
const wasm = await WebAssembly.instantiate(bytes, {env: env});
const instance = wasm.instance;
const memory = instance.exports.memory;

//const encoder = new TextEncoder();
const sizeof = {u08: 1, u16: 2, u32: 4};
const program_kind_to_string = new Map();
const program_kind_from_string = new Map();
const property_kind_to_string = new Map();
const property_kind_from_string = new Map();
const declarator_kind_to_string = new Map();
const declarator_kind_from_string = new Map();
const constructors = [];
const constants = map_constants(instance);
use_utf16 = !!constants.has_flag_utf16;
const utf8_decoder = new TextDecoder('utf-8');
const decoder = new TextDecoder(use_utf16 ? 'utf-16' : 'utf-8');

let debug_log, group_begin, group_end, debug = is_electron;
if(debug) {
   debug_log = console.log;
   group_begin = console.groupCollapsed;
   group_end = console.groupEnd;
} else {
   debug_log = () => {};
   group_begin = () => {};
   group_end = () => {};
}

function define_interface(Class, type_info, type_name)
{
   group_begin(Class.name);
   let enumerables = Array.from(Node.prototype.enumerables);
   if(type_name) Object.defineProperty(Class.prototype, 'type', {value: type_name});
   if(type_info.flags) _bind_flags(Class, type_info.flags);
   if(type_info.nodes) _bind_nodes(Class, type_info.nodes);
   //if(type_info.properties) _bind_properties(Class, type_info.properties);
   if(type_info.lists) _bind_lists(Class, type_info.lists);
   if(type_info.strings) _bind_strings(Class, type_info.strings);
   if(type_info.tokens) _bind_tokens(Class, type_info.tokens);
   if(type_info.bind_value) {
      enumerables.push(type_info.bind_value);
      Object.defineProperty(Class.prototype, type_info.bind_value, {
         get: function(){ return this.get_value(); },
      });
   }
   //Object.defineProperty(Class.prototype, 'enumerables', {value: enumerables});
   Class.prototype.enumerables = enumerables;
   group_end();

   function _make_node(parent, node_pointer) {
      if(node_pointer == 0) return null;
      let type_id = parent.buffer_view.u08[node_pointer + 8];
      let constructor = constructors[type_id];
      if(!constructor){
         console.log(parent.pointer, new Uint32Array(parent.buffer_view.buffer, parent.pointer, 6));
         console.log(node_pointer, new Uint32Array(parent.buffer_view.buffer, node_pointer, 6));
         throw(`no constructor for id ${type_id}`);
      }
      return new constructor(parent.buffer_view, node_pointer);
   }
   function _list_to_array(parent, list_node_pointer)
   {
      let array = [];
      const type = 'u32';
      while(list_node_pointer != 0) {
         const prop_offset = list_node_pointer / sizeof[type];
         const node_pointer = parent.buffer_view[type][prop_offset];
         if(node_pointer == 0) {
            array.push(null);
         } else {
            array.push(_make_node(parent, node_pointer));
         }
         const next_pointer = parent.buffer_view[type][prop_offset + 1];
         list_node_pointer = next_pointer;
      }
      return array;
   }
   function _bind_nodes(Class, nodes) {
      group_begin('nodes');
      for(const [name, offset] of Object.entries(nodes)) {
         debug_log(name);
         const type = 'u32';
         enumerables.push(name);
         Object.defineProperty(Class.prototype, name, {
            enumerable: true,
            get: function(){
               if(this.pointer === 0) return null;
               if(this._cached_pointer === this.pointer) return this._cached_node;
               const prop_offset = (this.pointer + offset) / sizeof[type];
               const node_pointer = this.buffer_view[type][prop_offset];
               this._cached_node = _make_node(this, node_pointer);
               this._cached_pointer = node_pointer;
               return this._cached_node;
            },
            set: function(node){
               if(!(node instanceof Node) || node.pointer == undefined) {
                  throw(`invalid node to assing to ${name}`);
               }
               const prop_offset = (this.pointer + offset) / sizeof[type];
               this.buffer_view[type][prop_offset] = node.pointer;
               this._cached_pointer = node.pointer;
               this._cached_node = node;
            }
         });
      }
      group_end();
   }
   /*
   function _bind_properties(Class, properties) {
      group_begin('properties');
      for(const [name, {type, offset}] of Object.entries(properties)) {
         enumerables.push(name);
         Object.defineProperty(Class.prototype, name, {
            enumerable: true,
            get: function(){
               return this.buffer_view[type][prop_offset];
            },
            set: function(value){
               const prop_offset = (this.pointer + offset) / sizeof[type];
               this.buffer_view[type][prop_offset] = value;
            }
         });
      }
      group_end();
   }
   */
   function _bind_strings(Class, strings) {
      group_begin('strings');
      for(const [name, {type, offset, to_string, from_string}] of Object.entries(strings)) {
         debug_log(name);
         enumerables.push(name);
         Object.defineProperty(Class.prototype, name, {
            enumerable: true,
            get: function(){
               const prop_offset = (this.pointer + offset) / sizeof[type];
               return to_string.get(this.buffer_view[type][prop_offset]);
            },
            set: function(value){
               const prop_offset = (this.pointer + offset) / sizeof[type];
               this.buffer_view[type][prop_offset] = from_string.get(value);
            }
         });
      }
      group_end();
   }
   function _bind_flags(Class, flags_detail) {
      group_begin('flags');
      for(const [aggregate_name, {type, offset, flags}] of Object.entries(flags_detail)) {
         debug_log(aggregate_name);
         for(const [name, flag] of Object.entries(flags)) {
            enumerables.push(name);
            Object.defineProperty(Class.prototype, name, {
               enumerable: true,
               get: function(){
                  const prop_offset = (this.pointer + offset) / sizeof[type];
                  return !!(this.buffer_view[type][prop_offset] & flag);
               },
               set: function(value){
                  const prop_offset = (this.pointer + offset) / sizeof[type];
                  if(value) this.buffer_view[type][prop_offset] |= flag;
                  else this.buffer_view[type][prop_offset] &= ~flag;
               }
            });
         }
      }
      group_end();
   }
   function _bind_lists(Class, lists) {
      group_begin('lists');
      for(const [name, offset] of Object.entries(lists)) {
         debug_log(name);
         enumerables.push(name);
         const type = 'u32';
         Object.defineProperty(Class.prototype, name, {
            enumerable: true,
            get: function() {
               if(this.pointer === 0) return [];
               if(this.pointer === this._cached_pointer) return this._cached_node;
               const prop_offset = (this.pointer + offset) / sizeof[type];
               const list_node_pointer = this.buffer_view[type][prop_offset];
               this._cached_node = _list_to_array(this, list_node_pointer);
               this._cached_pointer = list_node_pointer;
               return this._cached_node;
            }
         });
      }
      group_end();
   }
   function _bind_tokens(Class, tokens) {
      group_begin('tokens');
      for(const [name, offset] of Object.entries(tokens)) {
         debug_log(name);
         enumerables.push(name);
         const type = 'u32';
         Object.defineProperty(Class.prototype, name, {
            enumerable: true,
            get: function(){
               const prop_offset = (this.pointer + offset) / sizeof[type];
               const token_pointer = this.buffer_view[type][prop_offset];
               const token_offset = token_pointer / sizeof[type];
               const begin = this.buffer_view[type][token_offset];
               const end = this.buffer_view[type][token_offset + 1];
               const token_string = this.decode(begin, end);
               return token_string;
            }
         });
      }
      group_end();
   }
}

group_begin('interface');
class Node {
   constructor(buffer_view, pointer) {
      Object.defineProperties(this, {
         buffer_view: {value: buffer_view, configurable: true},
         pointer: {value: pointer},
      });
   }

   get_value() { return decoder.decode(this.buffer_view.code.subarray(this.begin, this.end)); }
   decode(begin, end) { return decoder.decode(this.buffer_view.code.subarray(begin, end)); }

   get type() { return this.constructor.name; }
   get type_id() { return this.buffer_view.u08[this.pointer + 8]; }
   get start() { return this.buffer_view.u32[this.pointer/4]; } // for compatibility with acorn
   set start(value) { this.buffer_view.u32[this.pointer/4] = value; } // for compatibility with acorn
   get begin() { return this.buffer_view.u32[this.pointer/4]; }
   set begin(value) { this.buffer_view.u32[this.pointer/4] = value; }
   get end() { return this.buffer_view.u32[this.pointer/4 + 1]; }
   set end(value) { this.buffer_view.u32[this.pointer/4 + 1] = value; }

   toJSON() {
      let enumerable_object = {};
      for(const property of this.enumerables || []) {
         enumerable_object[property] = this[property];
      }
      return enumerable_object;
   }
}
Node.prototype.enumerables = ['type', 'start', 'end'];

class Statement extends Node {}
class Declaration extends Node {}
class Expression extends Node {}
class Pattern extends Node {}

class SpreadElement extends Node {}
class RestElement extends Node {}
define_interface(SpreadElement, {nodes: {argument: 12}});
define_interface(RestElement, {nodes: {argument: 12}});

class Identifier extends Expression {}
define_interface(Identifier, {bind_value: 'name'});

class Literal extends Expression {
   token_to_value(token_id){
      switch(token_id) {
         case constants.rw_null: return null;
         case constants.rw_true: return true;
         case constants.rw_false: return false;
         case constants.tkn_numeric_literal: return Number(this.get_value());
         //[BUG] temporary fix to get parsed values
         case constants.tkn_string_literal: return eval(this.get_value());
      }
      return undefined;
   }
   /*
   value_to_token(value){
      switch(value) {
         case null: return constants.rw_null;
         case true: return constants.rw_true;
         case false: return constants.rw_false;
         default: {
            if(typeof value == 'string') return
         }
      }
   }
   */
   get value() {
      const prop_offset = this.pointer + 10;
      const token_id = this.buffer_view.u08[prop_offset];
      return this.token_to_value(this.buffer_view.u08[prop_offset]);
   }
   get raw() { return this.get_value(); }
}
Literal.prototype.enumerables = Array.from(Node.prototype.enumerables).concat(['value', 'raw']);
class RegExpLiteral extends Literal {
   get regex() {
      const flags_length = this.buffer_view.u08[this.pointer + 10] >> 3;
      const middle = this.end - flags_length;
      return {
         pattern: this.decode(this.begin + 1, middle - 1),
         flags: this.decode(middle, this.end)
      };
   }
   get value() {
      const regexp = this.regex;
      return new RegExp(regexp.pattern, regexp.flags);
   }
}
Object.defineProperty(RegExpLiteral.prototype, 'type', {value: 'Literal'});
RegExpLiteral.prototype.enumerables = Array.from(Node.prototype.enumerables).concat(['regex', 'value', 'raw']);

class ThisExpression extends Expression {}
class ArrayExpression extends Expression {}
class ObjectExpression extends Expression {}
class TemplateLiteral extends Expression {}
define_interface(ArrayExpression, {lists: {elements: 12}});
define_interface(ObjectExpression, {lists: {properties: 16}});
define_interface(TemplateLiteral, {lists: {quasis: 12, expressions: 16}});

class TemplateElement extends Node {
   get value() {
      const type = 'u32';
      const offset = 12;
      const prop_offset = (this.pointer + offset) / sizeof[type];
      const token_pointer = this.buffer_view[type][prop_offset];
      if(token_pointer == 0) return {raw: '', cooked: ''};
      const token_offset = token_pointer / sizeof[type];
      const begin = this.buffer_view[type][token_offset];
      const end = this.buffer_view[type][token_offset + 1];
      const token_string = this.decode(begin, end);
      return {raw: token_string, cooked: token_string};
   }
}
define_interface(TemplateElement, {
   flags: {flags: {type: 'u08', offset: 10, flags: {
      tail: constants.template_flag_tail
   }}}
});
TemplateElement.prototype.enumerables.push('value');

class ParenthesizedExpression extends Expression {
   constructor() {
      super(...arguments);
      return this.expression;
   }
}
define_interface(ParenthesizedExpression, {nodes: {expression: 16}});

const property_type_info = {
   nodes: {key: 12, value: 16},
   strings: {kind: {
      type: 'u08', offset: 10,
      to_string: property_kind_to_string,
      from_string: property_kind_from_string
   }},
   flags: {flags: {type: 'u08', offset: 11, flags: {
      method: constants.property_flag_method,
      shorthand: constants.property_flag_shorthand,
      computed: constants.property_flag_computed
   }}}
};
// clone property_type_info
const method_type_info = Object.assign({}, property_type_info);
method_type_info.flags = {flags: {type: 'u08', offset: 11, flags: {
   computed: constants.property_flag_computed,
   static: constants.method_flag_static
}}};

class Property extends Node {}
class AssignmentProperty extends Property {}
class MethodDefinition extends Property {}
define_interface(Property, property_type_info);
define_interface(AssignmentProperty, property_type_info, 'Property');
define_interface(MethodDefinition, method_type_info);

class Function extends Node {}
class FunctionExpression extends Function {}
class FunctionDeclaration extends Function {}
class ArrowFunctionExpression extends Function {}
define_interface(Function, {
   nodes: {id: 12, body: 20},
   lists: {params: 16},
   flags: {flags: {type: 'u08', offset: 10, flags: {
      expression: constants.function_flag_expression,
      generator: constants.function_flag_generator,
      async: constants.function_flag_async
   }}}
});

class Class extends Statement {}
class ClassExpression extends Class {}
class ClassDeclaration extends Class {}
define_interface(Class, {
   nodes: {id: 12, superClass: 16, body: 20}
});

class MemberExpression extends Expression {}
define_interface(MemberExpression, {
   nodes: {object: 12, property: 16},
   flags: {flags: {type: 'u08', offset: 10, flags: {
      computed: constants.member_flag_computed,
      optional: constants.optional_flag_optional
   }}}
});
class TaggedTemplateExpression extends Expression {}
define_interface(TaggedTemplateExpression, {
   nodes: {tag: 12, quasi: 16}
});
class NewExpression extends Expression {}
define_interface(NewExpression, {
   nodes: {callee: 12},
   lists: {arguments: 16}
});
class CallExpression extends Expression {}
define_interface(CallExpression, {
   nodes: {callee: 12},
   lists: {arguments: 16},
   flags: {flags: {type: 'u08', offset: 10, flags: {
      optional: constants.optional_flag_optional
   }}}
});
class ChainExpression extends Expression {}
define_interface(ChainExpression, {
   nodes: {expression: 12}
});
class ImportExpression extends Expression {}
define_interface(ImportExpression, {
   nodes: {source: 12}
});
class UpdateExpression extends Expression {}
define_interface(UpdateExpression, {
   //nodes: {argument: 12},
   //tokens: {operator: 11}
   nodes: {argument: 16},
   tokens: {operator: 12},
   flags: {flags: {type: 'u08', offset: 10, flags: {
      prefix: constants.operator_flag_prefix
   }}}
});
class UnaryExpression extends Expression {}
define_interface(UnaryExpression, {
   //nodes: {argument: 12},
   //tokens: {operator: 10}
   nodes: {argument: 16},
   tokens: {operator: 12},
   flags: {flags: {type: 'u08', offset: 10, flags: {
      prefix: constants.operator_flag_prefix
   }}}
});
class YieldExpression extends Expression {}
define_interface(YieldExpression, {
   nodes: {argument: 12},
   flags: {flags: {type: 'u08', offset: 10, flags: {
      delegate: constants.yield_flag_delegate
   }}}
});
class AwaitExpression extends Expression {}
define_interface(AwaitExpression, {
   nodes: {argument: 12}
});
class BinaryExpression extends Expression {}
define_interface(BinaryExpression, {
   //nodes: {left: 12, right: 16},
   //tokens: {operator: 10}
   nodes: {left: 16, right: 20},
   tokens: {operator: 12}
});
class LogicalExpression extends Expression {}
define_interface(LogicalExpression, {
   //nodes: {left: 12, right: 16},
   //tokens: {operator: 10}
   nodes: {left: 16, right: 20},
   tokens: {operator: 12}
});
class ConditionalExpression extends Expression {}
define_interface(ConditionalExpression, {
   nodes: {test: 12, consequent: 16, alternate: 20}
});
class AssignmentExpression extends Expression {}
define_interface(AssignmentExpression, {
   //nodes: {left: 12, right: 16},
   //tokens: {operator: 10}
   nodes: {left: 12, right: 16},
   tokens: {operator: 20}
});
class SequenceExpression extends Expression {}
define_interface(SequenceExpression, {
   lists: {expressions: 12}
});
class AssignmentPattern extends Pattern {}
define_interface(AssignmentPattern, {
   nodes: {left: 12, right: 16}
});
//[COMPATIBILITY] for estree compatibility type is set to AssignmentPattern
class InitializedName extends Pattern {}
define_interface(InitializedName, {
   nodes: {left: 12, right: 16}
}, 'AssignmentPattern');
//[COMPATIBILITY] for estree compatibility type is set to AssignmentPattern
class BindingAssignment extends Pattern {}
define_interface(BindingAssignment, {
   nodes: {left: 12, right: 16}
}, 'AssignmentPattern');
class ArrayPattern extends Pattern {}
define_interface(ArrayPattern, {
   lists: {elements: 12}
});
class ObjectPattern extends Pattern {}
define_interface(ObjectPattern, {
   lists: {properties: 16}
});
//[COMPATIBILITY] estree does not distinguish between assignment patterns and
// binding patterns
class ArrayAssignmentPattern extends Pattern {}
define_interface(ArrayAssignmentPattern, {
   lists: {elements: 12}
}, 'ArrayPattern');
class ObjectAssignmentPattern extends Pattern {}
define_interface(ObjectAssignmentPattern, {
   lists: {properties: 16}
}, 'ObjectPattern');
class VariableDeclarator extends Node {}
define_interface(VariableDeclarator, {
   nodes: {id: 12, init: 16}
});
class VariableDeclaration extends Declaration {}
define_interface(VariableDeclaration, {
   lists: {declarations: 12},
   strings: {kind: {
      type: 'u08', offset: 10,
      to_string: declarator_kind_to_string,
      from_string: declarator_kind_from_string
   }},
});
class Super extends Node {}
class MetaProperty extends Expression {}
define_interface(MetaProperty, {
   nodes: {meta: 12, property: 16}
});
class BlockStatement extends Statement {}
define_interface(BlockStatement, {
   lists: {body: 12}
});
class FunctionBody extends BlockStatement {}
class EmptyStatement extends Statement {}
class ExpressionStatement extends Statement {}
define_interface(ExpressionStatement, {
   nodes: {expression: 12}
});
class Directive extends Node {
   get directive() {
      return this.decode(this.expression.begin + 1, this.expression.end - 1);
   }
}
define_interface(Directive, {nodes: {expression: 12}}, 'ExpressionStatement');
Directive.prototype.enumerables.push('directive');
class IfStatement extends Statement {}
define_interface(IfStatement, {
   nodes: {test: 12, consequent: 16, alternate: 20}
});
class DoStatement extends Statement {}
define_interface(DoStatement, {
   nodes: {body: 12, test: 16}
}, 'DoWhileStatement');
class WhileStatement extends Statement {}
define_interface(WhileStatement, {
   nodes: {test: 12, body: 16}
});
class ForStatement extends Statement {}
define_interface(ForStatement, {
   nodes: {init: 12, test: 16, update: 20, body: 24}
});
class ForInStatement extends Statement {}
define_interface(ForInStatement, {
   nodes: {left: 12, right: 16, body: 20}
});
class ForOfStatement extends Statement {}
define_interface(ForOfStatement, {
   nodes: {left: 12, right: 16, body: 20},
   flags: {flags: {type: 'u08', offset: 10, flags: {
      await: constants.for_flag_await
   }}}
});
class CaseStatement extends Statement {}
define_interface(CaseStatement, {
   nodes: {test: 12, consequent: 16}
});
class SwitchStatement extends Statement {}
define_interface(SwitchStatement, {
   nodes: {discriminant: 12},
   lists: {cases: 16}
});
class SwitchCase extends Node {}
define_interface(SwitchCase, {
   nodes: {test: 12},
   lists: {consequent: 16}
});
class ContinueStatement extends Statement {}
define_interface(ContinueStatement, {
   nodes: {label: 12}
});
class BreakStatement extends Statement {}
define_interface(BreakStatement, {
   nodes: {label: 12}
});
class ReturnStatement extends Statement {}
define_interface(ReturnStatement, {
   nodes: {argument: 12}
});
class LabeledStatement extends Statement {}
define_interface(LabeledStatement, {
   nodes: {label: 12, body: 16}
});
class WithStatement extends Statement {}
define_interface(WithStatement, {
   nodes: {object: 12, body: 16}
});
class ThrowStatement extends Statement {}
define_interface(ThrowStatement, {
   nodes: {argument: 12}
});
class TryStatement extends Statement {}
define_interface(TryStatement, {
   nodes: {block: 12, handler: 16, finalizer: 20}
});
class CatchClause extends Node {}
define_interface(CatchClause, {
   nodes: {param: 12, body: 16}
});
class DebuggerStatement extends Statement {}
class ClassBody extends Node {}
define_interface(ClassBody, {
   lists: {body: 12}
});
class Program extends Node {}
define_interface(Program, {
   strings: {sourceType: {
      type: 'u08', offset: 10,
      to_string: program_kind_to_string,
      from_string: program_kind_from_string
   }},
   lists: {body: 12}
});
group_end();

function map_constants(instance) {
   let constants = [];
   const array = new Uint8Array(instance.exports.memory.buffer);
   for(let key in instance.exports) {
      if(key.startsWith('pnt_') ||
         key.startsWith('rw_') ||
         key.startsWith('tkn_') ||
         key.match('_kind_') ||
         key.match('_flag_')
      ){
         constants[key] = array[instance.exports[key].value];
      }
   }

   program_kind_to_string.set(constants.program_kind_script, 'script');
   program_kind_to_string.set(constants.program_kind_module, 'module');
   program_kind_from_string.set('script', constants.program_kind_script);
   program_kind_from_string.set('module', constants.program_kind_module);

   property_kind_to_string.set(constants.property_kind_init, 'init');
   property_kind_to_string.set(constants.property_kind_get, 'get');
   property_kind_to_string.set(constants.property_kind_set, 'set');
   property_kind_to_string.set(constants.property_kind_method, 'method');
   property_kind_to_string.set(constants.property_kind_constructor, 'constructor');
   property_kind_from_string.set('init', constants.property_kind_init);
   property_kind_from_string.set('get', constants.property_kind_get);
   property_kind_from_string.set('set', constants.property_kind_set);
   property_kind_from_string.set('method', constants.property_kind_method);
   property_kind_from_string.set('constructor', constants.property_kind_constructor);

   declarator_kind_to_string.set(constants.rw_var, 'var');
   declarator_kind_to_string.set(constants.rw_let, 'let');
   declarator_kind_to_string.set(constants.rw_const, 'const');
   declarator_kind_from_string.set('var', constants.rw_var);
   declarator_kind_from_string.set('let', constants.rw_let);
   declarator_kind_from_string.set('const', constants.rw_const);

   return constants;
}

function map_constructors(){
   constructors[constants.pnt_program] = Program;
   constructors[constants.pnt_identifier] = Identifier;
   constructors[constants.pnt_literal] = Literal;
   constructors[constants.pnt_regexp_literal] = RegExpLiteral;

   constructors[constants.pnt_this_expression] = ThisExpression;
   constructors[constants.pnt_array_expression] = ArrayExpression;
   constructors[constants.pnt_object_expression] = ObjectExpression;
   constructors[constants.pnt_template_literal] = TemplateLiteral;
   constructors[constants.pnt_template_element] = TemplateElement;
   constructors[constants.pnt_property] = Property;
   constructors[constants.pnt_spread_element] = SpreadElement;
   constructors[constants.pnt_function_expression] = FunctionExpression;
   constructors[constants.pnt_member_expression] = MemberExpression;
   constructors[constants.pnt_tagged_template_expression] = TaggedTemplateExpression;
   constructors[constants.pnt_new_expression] = NewExpression;
   constructors[constants.pnt_call_expression] = CallExpression;
   constructors[constants.pnt_chain_expression] = ChainExpression;
   constructors[constants.pnt_update_expression] = UpdateExpression;
   constructors[constants.pnt_unary_expression] = UnaryExpression;
   constructors[constants.pnt_binary_expression] = BinaryExpression;
   constructors[constants.pnt_logical_expression] = LogicalExpression;
   constructors[constants.pnt_conditional_expression] = ConditionalExpression;
   constructors[constants.pnt_arrow_function_expression] = ArrowFunctionExpression;
   constructors[constants.pnt_array_assignment_pattern] = ArrayAssignmentPattern;
   constructors[constants.pnt_object_assignment_pattern] = ObjectAssignmentPattern;
   constructors[constants.pnt_assignment_expression] = AssignmentExpression;
   constructors[constants.pnt_expression] = SequenceExpression;
   constructors[constants.pnt_assignment_property] = AssignmentProperty;
   constructors[constants.pnt_rest_element] = RestElement;
   constructors[constants.pnt_yield_expression] = YieldExpression;
   constructors[constants.pnt_class_expression] = ClassExpression;
   constructors[constants.pnt_await_expression] = AwaitExpression;
   constructors[constants.pnt_import_expression] = ImportExpression;
   constructors[constants.pnt_parenthesized_expression] = ParenthesizedExpression;
   constructors[constants.pnt_binding_assignment] = BindingAssignment;
   constructors[constants.pnt_initialized_name] = InitializedName;

   constructors[constants.pnt_catch_clause] = CatchClause;
   constructors[constants.pnt_case_clause] = SwitchCase;
   constructors[constants.pnt_function_body] = FunctionBody;
   constructors[constants.pnt_class_body] = ClassBody;
   constructors[constants.pnt_method_definition] = MethodDefinition;
   constructors[constants.pnt_super] = Super;
   constructors[constants.pnt_meta_property] = MetaProperty;

   constructors[constants.pnt_block_statement] = BlockStatement;
   constructors[constants.pnt_empty_statement] = EmptyStatement;
   constructors[constants.pnt_expression_statement] = ExpressionStatement;
   constructors[constants.pnt_directive] = Directive;
   constructors[constants.pnt_if_statement] = IfStatement;
   constructors[constants.pnt_do_statement] = DoStatement;
   constructors[constants.pnt_while_statement] = WhileStatement;
   constructors[constants.pnt_for_statement] = ForStatement;
   constructors[constants.pnt_for_in_statement] = ForInStatement;
   constructors[constants.pnt_for_of_statement] = ForOfStatement;
   constructors[constants.pnt_switch_statement] = SwitchStatement;
   constructors[constants.pnt_continue_statement] = ContinueStatement;
   constructors[constants.pnt_break_statement] = BreakStatement;
   constructors[constants.pnt_return_statement] = ReturnStatement;
   constructors[constants.pnt_with_statement] = WithStatement;
   constructors[constants.pnt_labeled_statement] = LabeledStatement;
   constructors[constants.pnt_throw_statement] = ThrowStatement;
   constructors[constants.pnt_try_statement] = TryStatement;
   constructors[constants.pnt_debugger_statement] = DebuggerStatement;

   constructors[constants.pnt_assignment_pattern] = AssignmentPattern;
   constructors[constants.pnt_array_pattern] = ArrayPattern;
   constructors[constants.pnt_object_pattern] = ObjectPattern;
   constructors[constants.pnt_variable_declaration] = VariableDeclaration;
   constructors[constants.pnt_variable_declarator] = VariableDeclarator;
   constructors[constants.pnt_function_declaration] = FunctionDeclaration;
   constructors[constants.pnt_class_declaration] = ClassDeclaration;
}
map_constructors();

return {
   instance: instance,
   memory: memory,
   constants: constants,
   load_file: load_file,
   parse_code: parse_code,
   bind_parse_tree: bind_parse_tree,
   parse_file: parse_file,
   free: free,
   Program: Program
};

});
