const is_node = (typeof process !== 'undefined' && process.versions && !process.versions.electron);
const is_electron = (typeof process !== 'undefined' && process.versions && process.versions.electron);
let read_file;
if(is_node) {
   read_file = async name => {
      const fs = await import('fs');
      return fs.readFileSync(name);
   };
} else {
   read_file = async name => {
      const response = await fetch(name);
      const bytes = await response.arrayBuffer();
      return new Uint8Array(bytes);
   }
}
/*
const color_escape_code = {
   red: 31, green: 32, magenta: 35, cyan: 36, black: 90
};
function colored_log(color, message) {
   console.log(`%c${message}`, `color: ${color}`);
}
*/
const color_escape_code = {
   red: 31, green: 32, magenta: 35, cyan: 36, black: 90
};
let colored_log;
if(is_node) {
   colored_log = function(color, message) {
      console.log(`\x1b[1;${color_escape_code[color]}m${message}\x1b[0m`);
   }
} else if(is_electron) {
   colored_log = function(color, message) {
      console.log(`%c${message}`, `color: ${color}`);
   }
}
const sizeof = {u08: 1, u16: 2, u32: 4};
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

function change_node_type(Class, type_name)
{
   Object.defineProperty(Class.prototype, 'type', {value: type_name});
}
function add_enumerables(Class, new_enumerables)
{
   let enumerables = Class.prototype.hasOwnProperty('enumerables')
      ? Class.prototype.enumerables : Array.from(Class.prototype.enumerables);
   //let t1 = new Set(enumerables);
   enumerables.push(...new_enumerables);
   /*
   let t2 = new Set(enumerables);
   if(t1.size + new_enumerables.length != t2.size) {
      console.error(Class, t1, new_enumerables, t2);
   }
   */
   Class.prototype.enumerables = enumerables;
}
function define_interface(Class, type_info, type_name)
{
   group_begin(Class.name);
   let enumerables = [];
   if(type_name) change_node_type(Class, type_name);
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
   //Class.prototype.enumerables = enumerables;
   add_enumerables(Class, enumerables);
   group_end();

   function _make_node(parent, node_pointer) {
      if(node_pointer == 0) return null;
      let type_id = parent.buffer_view.u08[node_pointer + 8];
      let constructor = Parser.constructors[type_id];
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
               let begin = new Date;
               this._cached_node = _list_to_array(this, list_node_pointer);
               Parser.list_time += new Date - begin;
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

export class Node {
   constructor(buffer_view, pointer) {
      Object.defineProperties(this, {
         buffer_view: {value: buffer_view, configurable: true},
         pointer: {value: pointer},
      });
   }

   get_value() { return Parser.decoder.decode(this.buffer_view.code.subarray(this.begin, this.end)); }
   decode(begin, end) { return Parser.decoder.decode(this.buffer_view.code.subarray(begin, end)); }
   get_compiled_value(strip_length) {
      const type = 'u32';
      const compiled_begin = this.buffer_view[type][(this.pointer + 12) / sizeof[type]];
      const compiled_end = this.buffer_view[type][(this.pointer + 16) / sizeof[type]];
      if(!compiled_begin) {
         return Parser.decoder.decode(
            this.buffer_view.code.subarray(this.begin + strip_length, this.end - strip_length)
         );
      } else {
         return Parser.decoder.decode(
            this.buffer_view.u08.subarray(compiled_begin, compiled_end)
         );
      }
   }

   get type() { return this.constructor.name; }
   get type_id() { return this.buffer_view.u08[this.pointer + 8]; }
   get start() { return this.buffer_view.u32[this.pointer/4]; } // for compatibility with acorn
   set start(value) { this.buffer_view.u32[this.pointer/4] = value; } // for compatibility with acorn
   get begin() { return this.buffer_view.u32[this.pointer/4]; }
   set begin(value) { this.buffer_view.u32[this.pointer/4] = value; }
   get end() { return this.buffer_view.u32[this.pointer/4 + 1]; }
   set end(value) { this.buffer_view.u32[this.pointer/4 + 1] = value; }

   toJSON() {
      let begin = new Date;
      let enumerable_object = {};
      for(const property of this.enumerables || []) {
         enumerable_object[property] = this[property];
      }
      Parser.to_json_time += new Date - begin;
      return enumerable_object;
   }
}
Node.prototype.enumerables = ['type', 'start', 'end'];

export class Statement extends Node {}
export class Declaration extends Node {}
export class Expression extends Node {}
export class Pattern extends Node {}
export class ModuleDeclaration extends Node {}

export class SpreadElement extends Node {}
export class RestElement extends Node {}

export class Identifier extends Expression {
   get name() { return this.get_compiled_value(0); }
}
add_enumerables(Identifier, ['name']);

export class Literal extends Expression {
   token_to_value(token_id){
      switch(token_id) {
         case Parser.constants.rw_null: return null;
         case Parser.constants.rw_true: return true;
         case Parser.constants.rw_false: return false;
         case Parser.constants.tkn_numeric_literal: return Number(this.get_value().replace(/^(0[0-7]+)$/, '0o$1'));
         //[BUG] temporary fix to get parsed values
         case Parser.constants.tkn_string_literal: return eval(this.get_value());
      }
      return undefined;
   }
   /*
   value_to_token(value){
      switch(value) {
         case null: return Parser.constants.rw_null;
         case true: return Parser.constants.rw_true;
         case false: return Parser.constants.rw_false;
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
add_enumerables(Literal, ['value', 'raw']);
export class StringLiteral extends Literal {
   get value() { return this.get_compiled_value(1); }
   get raw() { return this.get_value(); }
}
change_node_type(StringLiteral, 'Literal');
//Literal.prototype.enumerables = Array.from(Node.prototype.enumerables).concat(['value', 'raw']);
export class RegExpLiteral extends Literal {
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
//Object.defineProperty(RegExpLiteral.prototype, 'type', {value: 'Literal'});
//RegExpLiteral.prototype.enumerables = Array.from(Node.prototype.enumerables).concat(['regex', 'value', 'raw']);
add_enumerables(RegExpLiteral, ['regex']);
change_node_type(RegExpLiteral, 'Literal');

export class ThisExpression extends Expression {}
export class ArrayExpression extends Expression {}
export class ObjectExpression extends Expression {}
export class TemplateLiteral extends Expression {}

export class TemplateElement extends Node {
   get value() {
      /*
      const type = 'u32';
      const offset = 12;
      const prop_offset = (this.pointer + offset) / sizeof[type];
      const token_pointer = this.buffer_view[type][prop_offset];
      if(token_pointer == 0) return {raw: '', cooked: ''};
      const token_offset = token_pointer / sizeof[type];
      const begin = this.buffer_view[type][token_offset];
      const end = this.buffer_view[type][token_offset + 1];
      const token_string = this.decode(begin, end);
      */
      return {raw: this.get_value().replace(/\r\n?/g, '\n'), cooked: this.get_compiled_value(0)};
   }
}
//TemplateElement.prototype.enumerables = Array.from(Node.prototype.enumerables).concat(['value']);
add_enumerables(TemplateElement, ['value']);
export class ParenthesizedExpression extends Expression {
   constructor() {
      super(...arguments);
      return this.expression;
   }
}
export class Property extends Node {}
export class AssignmentProperty extends Property {}
export class MethodDefinition extends Node {}

export class Function extends Node {}
export class FunctionExpression extends Function {}
export class FunctionDeclaration extends Function {}
export class ArrowFunctionExpression extends Function {}

export class Class extends Statement {}
export class ClassExpression extends Class {}
export class ClassDeclaration extends Class {}

export class ImportDeclaration extends ModuleDeclaration {}
export class ModuleSpecifier extends Node {}
export class ImportSpecifier extends ModuleSpecifier {}
export class ImportDefaultSpecifier extends ModuleSpecifier {}
export class ImportNamespaceSpecifier extends ModuleSpecifier {}
export class ExportAllDeclaration extends ModuleDeclaration {}
export class ExportNamedDeclaration extends ModuleDeclaration {}
export class ExportDefaultDeclaration extends ModuleDeclaration {}
export class ExportSpecifier extends ModuleSpecifier {}

export class MemberExpression extends Expression {}
export class TaggedTemplateExpression extends Expression {}
export class NewExpression extends Expression {}
export class CallExpression extends Expression {}
export class ChainExpression extends Expression {}
export class ImportExpression extends Expression {}
export class UpdateExpression extends Expression {}
export class UnaryExpression extends Expression {}
export class YieldExpression extends Expression {}
export class AwaitExpression extends Expression {}
export class BinaryExpression extends Expression {}
export class LogicalExpression extends Expression {}
export class ConditionalExpression extends Expression {}
export class AssignmentExpression extends Expression {}
export class SequenceExpression extends Expression {}
export class AssignmentPattern extends Pattern {}
export class InitializedName extends Pattern {}
export class BindingAssignment extends Pattern {}
export class ArrayPattern extends Pattern {}
export class ObjectPattern extends Pattern {}
export class ArrayAssignmentPattern extends Pattern {}
export class ObjectAssignmentPattern extends Pattern {}
export class VariableDeclarator extends Node {}
export class VariableDeclaration extends Declaration {}
export class Super extends Node {}
export class MetaProperty extends Expression {}
export class BlockStatement extends Statement {}
export class FunctionBody extends BlockStatement {}
export class EmptyStatement extends Statement {}
export class ExpressionStatement extends Statement {}
export class Directive extends Node {
   get directive() {
      return this.decode(this.expression.begin + 1, this.expression.end - 1);
   }
}
//Directive.prototype.enumerables = Array.from(Node.prototype.enumerables).concat(['directive']);
add_enumerables(Directive, ['directive']);
export class IfStatement extends Statement {}
export class DoStatement extends Statement {}
export class WhileStatement extends Statement {}
export class ForStatement extends Statement {}
export class ForInStatement extends Statement {}
export class ForOfStatement extends Statement {}
export class CaseStatement extends Statement {}
export class SwitchStatement extends Statement {}
export class SwitchCase extends Node {}
export class ContinueStatement extends Statement {}
export class BreakStatement extends Statement {}
export class ReturnStatement extends Statement {}
export class LabeledStatement extends Statement {}
export class WithStatement extends Statement {}
export class ThrowStatement extends Statement {}
export class TryStatement extends Statement {}
export class CatchClause extends Node {}
export class DebuggerStatement extends Statement {}
export class ClassBody extends Node {}
export class Program extends Node {}

const env = {
   show_token_type: function(index){
      let index_begin = index;
      //while(index < shared_memory.length && shared_memory[index++] != 0);
      let string_buffer = Parser.memory.buffer.slice(index_begin, index);
      let string = new TextDecoder('utf-8').decode(string_buffer);
      console.log(string);
   },
   show_token: function(format_index, length, index) {
      let string_buffer = Parser.memory.buffer.slice(index, index + length);
      let string = new TextDecoder('utf-8').decode(string_buffer);
      console.log(string);
   },
   /*
   log_token: function(format_index, length, index, id, group, begin, end) {
      console.log(index, id, group, begin, end);
      let string_buffer = Parser.memory.buffer.slice(index, index + length);
      let string = new TextDecoder('utf-8').decode(string_buffer);
      //console.log(string);
   },
   */
   log_number: function(number) { console.log(String.fromCharCode(number), number.toString(16)); },
   log_string: function(pointer, length) {
      if(length < 256) {
         console.log(
            Parser.utf8_decoder.decode(new Uint8Array(Parser.memory.buffer, pointer, length))
         );
      } else {
         console.log('string is too long');
      }
   },
   begin_group_impl: function(pointer, length) {
      if(length < 32) {
         console.groupCollapsed(
            Parser.utf8_decoder.decode(new Uint8Array(Parser.memory.buffer, pointer, length))
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
      const type_view = new Uint8Array(Parser.memory.buffer, type_pointer, type_length);
      let title = Array(depth < 0 ? 0 : depth % 60).fill(' ').join('') + '=> ';
      title += Parser.utf8_decoder.decode(type_view);
      const flags = [
         ['param_flag_await', 'await'],
         ['param_flag_default', 'default'],
         ['param_flag_in', 'in'],
         ['param_flag_return', 'return'],
         ['param_flag_yield', 'yield'],
         ['cover_flag_initializer', 'cover-init'],
         ['cover_flag_parameters', 'cover-params'],
         ['param_flag_for_binding', 'for-binding'],
         ['param_flag_annex', 'annex'],
         ['param_flag_strict_mode', 'strict']
      ];
      title += ' (';
      for(const [flag, label] of flags) {
         if(params & Parser.constants[flag]) title += ` ${label}`;
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
      const TypedArray = (Parser.use_utf16 ? Uint16Array : Uint8Array);
      const token_view = (new TypedArray(Parser.memory.buffer, token_pointer)).subarray(0, length);
      const token = (length < 512 ? Parser.decoder.decode(token_view) : '[too long]');
      console.log(token);
   },
   log_token_consumption: function(code_pointer, begin, end, depth) {
      let space = Array(depth < 0 ? 0 : depth % 60).fill(' ').join('');
      const TypedArray = (Parser.use_utf16 ? Uint16Array : Uint8Array);
      const token_view = (new TypedArray(Parser.memory.buffer, code_pointer)).subarray(begin, end);
      const token = (end - begin < 32 ? Parser.decoder.decode(token_view) : '[too long]');
      colored_log('cyan', `${space}consumed token ${token}`);
   },
   log_make_node: function(type_pointer, type_length, depth) {
      let space = Array(depth < 0 ? 0 : depth % 60).fill(' ').join('');
      const type_view = new Uint8Array(Parser.memory.buffer, type_pointer, type_length);
      let type = Parser.utf8_decoder.decode(type_view);
      colored_log('magenta', `${space}making node ${type}`);
   },
   log_assertion: function(file_name_pointer, length, line_number) {
      const file_name_view = (new Uint8Array(Parser.memory.buffer, file_name_pointer)).subarray(0, length);
      const file_name = Parser.utf8_decoder.decode(file_name_view);
      console.error(`assertion failed at ${file_name}:${line_number}`);
   }
}

export class Parser {
   constructor() {
      this.code = {};
      this.program = null;
      this.parse_result = {};
   }
   async load_file(file_path) {
      // for now all files are assumed to be UTF-8 encoded
      let code_utf8_view = await read_file(file_path);
      let code_view;
      if(Parser.use_utf16) {
         // convert from UTF-8 to UTF-16
         const code_string = (new TextDecoder('utf-8')).decode(code_utf8_view);
         const code_utf16_view = utf8_to_utf16(code_utf8_view);
         code_view = code_utf16_view;
      } else {
         code_view = code_utf8_view;
      }
      const index = Parser.instance.exports.malloc(code_view.byteLength);
      const shared_memory = new Uint8Array(Parser.memory.buffer);
      const code_uint8_view = new Uint8Array(code_view.buffer, code_view.byteOffset, code_view.byteLength);
      shared_memory.set(code_uint8_view, index);
      this.code = {pointer: index, view: code_view, utf8_view: code_utf8_view};
   }
   parse_code(is_module) {
      let params = Parser.constants.param_flag_annex;
      let result_size = 4096; //[BUG] large enough for now to not worry about actual size
      let result_pointer = Parser.instance.exports.malloc(result_size);
      let begin = this.code.pointer, end = begin + this.code.view.byteLength;
      Parser.instance.exports.parse(result_pointer, begin, end, is_module, params);
      let result = new Uint32Array(Parser.memory.buffer, result_pointer, result_size/4);
      this.parse_result = {value: result, pointer: result_pointer};
   }
   bind_parse_tree() {
      let buffer = Parser.memory.buffer;
      let buffer_view = {
         buffer: buffer,
         u08: new Uint8Array(buffer),
         u16: new Uint16Array(buffer),
         u32: new Uint32Array(buffer),
         code: this.code.view
      };
      let TypedArray = (Parser.use_utf16 ? Uint16Array : Uint8Array);
      let code_view = new TypedArray(buffer, this.parse_result.value[1], this.code.view.length);
      this.program = new Program(buffer_view, this.parse_result.value[0]);
      return this.program;
   }
   async parse_file(file_name, is_module) {
      await this.load_file(file_name);
      is_module = is_module ?? /\.module\.js$|\.mjs$/.test(file_name);
      this.parse_code(is_module);
      return this.bind_parse_tree();
   }
   free() {
      //Parser.instance.exports.wasm_free(result.value[0]);
      Parser.instance.exports.parser_free(this.parse_result.pointer + 4);
      Parser.instance.exports.wasm_free(this.parse_result.pointer);
   }

   static async load_wasm(path) {
      const bytes = await read_file(path);
      const wasm = await WebAssembly.instantiate(bytes, {env: env});
      Parser.instance = wasm.instance;
      Parser.memory = Parser.instance.exports.memory;
      Parser.map_constants();
      Parser.use_utf16 = !!Parser.constants.has_flag_utf16;
      Parser.utf8_decoder = new TextDecoder('utf-8');
      Parser.decoder = new TextDecoder(Parser.use_utf16 ? 'utf-16' : 'utf-8');
      Parser.map_constructors();
      Parser.complete_interface_definitions();
   }
   static map_constants() {
      Parser.constants = {};
      const array08 = new Uint8Array(Parser.instance.exports.memory.buffer);
      const array32 = new Uint32Array(Parser.instance.exports.memory.buffer);
      for(let key in Parser.instance.exports) {
         if(key.startsWith('pnt_') ||
            key.startsWith('rw_') ||
            key.startsWith('tkn_') ||
            key.match('_kind_') ||
            key.match('_flag_')
         ){
            if(key.startsWith('param_flag')) {
               Parser.constants[key] = array32[Parser.instance.exports[key].value/4];
            } else {
               Parser.constants[key] = array08[Parser.instance.exports[key].value];
            }
         }
      }
   }
   static map_constructors(){
      const constants = Parser.constants;
      const constructors = Parser.constructors = {};
      constructors[constants.pnt_program] = Program;
      constructors[constants.pnt_identifier] = Identifier;
      constructors[constants.pnt_literal] = Literal;
      constructors[constants.pnt_string_literal] = StringLiteral;
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
      constructors[constants.pnt_covered_call_expression] = CallExpression;
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

      constructors[constants.pnt_import_declaration] = ImportDeclaration;
      constructors[constants.pnt_import_specifier] = ImportSpecifier;
      constructors[constants.pnt_import_default_specifier] = ImportDefaultSpecifier;
      constructors[constants.pnt_import_namespace_specifier] = ImportNamespaceSpecifier;
      constructors[constants.pnt_export_all_declaration] = ExportAllDeclaration;
      constructors[constants.pnt_export_named_declaration] = ExportNamedDeclaration;
      constructors[constants.pnt_export_default_declaration] = ExportDefaultDeclaration;
      constructors[constants.pnt_export_specifier] = ExportSpecifier;
   }
   static complete_interface_definitions() {
      group_begin('interface');
      const constants = Parser.constants;
      const program_kind_to_string = new Map();
      const program_kind_from_string = new Map();
      program_kind_to_string.set(constants.program_kind_script, 'script');
      program_kind_to_string.set(constants.program_kind_module, 'module');
      program_kind_from_string.set('script', constants.program_kind_script);
      program_kind_from_string.set('module', constants.program_kind_module);
      define_interface(Program, {
         strings: {sourceType: {
            type: 'u08', offset: 10,
            to_string: program_kind_to_string,
            from_string: program_kind_from_string
         }},
         lists: {body: 12}
      });

      const property_kind_to_string = new Map();
      const property_kind_from_string = new Map();
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
      //
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
      define_interface(Property, property_type_info);
      change_node_type(AssignmentProperty, 'Property');
      //define_interface(AssignmentProperty, property_type_info, 'Property');
      define_interface(MethodDefinition, method_type_info);

      const declarator_kind_to_string = new Map();
      const declarator_kind_from_string = new Map();
      declarator_kind_to_string.set(constants.rw_var, 'var');
      declarator_kind_to_string.set(constants.rw_let, 'let');
      declarator_kind_to_string.set(constants.rw_const, 'const');
      declarator_kind_from_string.set('var', constants.rw_var);
      declarator_kind_from_string.set('let', constants.rw_let);
      declarator_kind_from_string.set('const', constants.rw_const);
      define_interface(VariableDeclaration, {
         lists: {declarations: 12},
         strings: {kind: {
            type: 'u08', offset: 10,
            to_string: declarator_kind_to_string,
            from_string: declarator_kind_from_string
         }},
      });

      define_interface(ImportDeclaration, {
         lists: {specifiers: 12},
         nodes: {source: 16}
      });
      define_interface(ModuleSpecifier, {nodes: {local: 12}});
      define_interface(ImportSpecifier, {nodes: {imported: 16}});
      define_interface(ExportAllDeclaration, {nodes: {exported: 12, source: 16}});
      define_interface(ExportNamedDeclaration, {
         lists: {specifiers: 12},
         nodes: {source: 16, declaration: 20}
      });
      define_interface(ExportDefaultDeclaration, {nodes: {declaration: 12}});
      define_interface(ExportSpecifier, {nodes: {exported: 16}});

      define_interface(SpreadElement, {nodes: {argument: 12}});
      define_interface(RestElement, {nodes: {argument: 12}});
      //define_interface(Identifier, {bind_value: 'name'});
      define_interface(ArrayExpression, {lists: {elements: 12}});
      define_interface(ObjectExpression, {lists: {properties: 16}});
      define_interface(TemplateLiteral, {lists: {quasis: 12, expressions: 16}});
      define_interface(TemplateElement, {
         flags: {flags: {type: 'u08', offset: 10, flags: {
            tail: Parser.constants.template_flag_tail
         }}}
      });
      define_interface(ParenthesizedExpression, {nodes: {expression: 16}});
      define_interface(Function, {
         nodes: {id: 12, body: 20},
         lists: {params: 16},
         flags: {flags: {type: 'u08', offset: 10, flags: {
            expression: Parser.constants.function_flag_expression,
            generator: Parser.constants.function_flag_generator,
            async: Parser.constants.function_flag_async
         }}}
      });
      define_interface(Class, {
         nodes: {id: 12, superClass: 16, body: 20}
      });
      define_interface(MemberExpression, {
         nodes: {object: 12, property: 16},
         flags: {flags: {type: 'u08', offset: 10, flags: {
            computed: Parser.constants.member_flag_computed,
            optional: Parser.constants.optional_flag_optional
         }}}
      });
      define_interface(TaggedTemplateExpression, {
         nodes: {tag: 12, quasi: 16}
      });
      define_interface(NewExpression, {
         nodes: {callee: 12},
         lists: {arguments: 16}
      });
      define_interface(CallExpression, {
         nodes: {callee: 12},
         lists: {arguments: 16},
         flags: {flags: {type: 'u08', offset: 10, flags: {
            optional: Parser.constants.optional_flag_optional
         }}}
      });
      define_interface(ChainExpression, {
         nodes: {expression: 12}
      });
      define_interface(ImportExpression, {
         nodes: {source: 12}
      });
      define_interface(UpdateExpression, {
         //nodes: {argument: 12},
         //tokens: {operator: 11}
         nodes: {argument: 16},
         tokens: {operator: 12},
         flags: {flags: {type: 'u08', offset: 10, flags: {
            prefix: Parser.constants.operator_flag_prefix
         }}}
      });
      define_interface(UnaryExpression, {
         //nodes: {argument: 12},
         //tokens: {operator: 10}
         nodes: {argument: 16},
         tokens: {operator: 12},
         flags: {flags: {type: 'u08', offset: 10, flags: {
            prefix: Parser.constants.operator_flag_prefix
         }}}
      });
      define_interface(YieldExpression, {
         nodes: {argument: 12},
         flags: {flags: {type: 'u08', offset: 10, flags: {
            delegate: Parser.constants.yield_flag_delegate
         }}}
      });
      define_interface(AwaitExpression, {
         nodes: {argument: 12}
      });
      define_interface(BinaryExpression, {
         //nodes: {left: 12, right: 16},
         //tokens: {operator: 10}
         nodes: {left: 16, right: 20},
         tokens: {operator: 12}
      });
      define_interface(LogicalExpression, {
         //nodes: {left: 12, right: 16},
         //tokens: {operator: 10}
         nodes: {left: 16, right: 20},
         tokens: {operator: 12}
      });
      define_interface(ConditionalExpression, {
         nodes: {test: 12, consequent: 16, alternate: 20}
      });
      define_interface(AssignmentExpression, {
         //nodes: {left: 12, right: 16},
         //tokens: {operator: 10}
         nodes: {left: 12, right: 16},
         tokens: {operator: 20}
      });
      define_interface(SequenceExpression, {
         lists: {expressions: 12}
      });
      define_interface(AssignmentPattern, {
         nodes: {left: 12, right: 16}
      });
      //[COMPATIBILITY] for estree compatibility type is set to AssignmentPattern
      define_interface(InitializedName, {
         nodes: {left: 12, right: 16}
      }, 'AssignmentPattern');
      //[COMPATIBILITY] for estree compatibility type is set to AssignmentPattern
      define_interface(BindingAssignment, {
         nodes: {left: 12, right: 16}
      }, 'AssignmentPattern');
      define_interface(ArrayPattern, {
         lists: {elements: 12}
      });
      define_interface(ObjectPattern, {
         lists: {properties: 16}
      });
      //[COMPATIBILITY] estree does not distinguish between assignment patterns and
      // binding patterns
      define_interface(ArrayAssignmentPattern, {
         lists: {elements: 12}
      }, 'ArrayPattern');
      define_interface(ObjectAssignmentPattern, {
         lists: {properties: 16}
      }, 'ObjectPattern');
      define_interface(VariableDeclarator, {
         nodes: {id: 12, init: 16}
      });
      define_interface(MetaProperty, {
         nodes: {meta: 12, property: 16}
      });
      define_interface(BlockStatement, {
         lists: {body: 12}
      });
      define_interface(ExpressionStatement, {
         nodes: {expression: 12}
      });
      define_interface(Directive, {nodes: {expression: 12}}, 'ExpressionStatement');
      define_interface(IfStatement, {
         nodes: {test: 12, consequent: 16, alternate: 20}
      });
      define_interface(DoStatement, {
         nodes: {body: 12, test: 16}
      }, 'DoWhileStatement');
      define_interface(WhileStatement, {
         nodes: {test: 12, body: 16}
      });
      define_interface(ForStatement, {
         nodes: {init: 12, test: 16, update: 20, body: 24}
      });
      define_interface(ForInStatement, {
         nodes: {left: 12, right: 16, body: 20}
      });
      define_interface(ForOfStatement, {
         nodes: {left: 12, right: 16, body: 20},
         flags: {flags: {type: 'u08', offset: 10, flags: {
            await: Parser.constants.for_flag_await
         }}}
      });
      define_interface(CaseStatement, {
         nodes: {test: 12, consequent: 16}
      });
      define_interface(SwitchStatement, {
         nodes: {discriminant: 12},
         lists: {cases: 16}
      });
      define_interface(SwitchCase, {
         nodes: {test: 12},
         lists: {consequent: 16}
      });
      define_interface(ContinueStatement, {
         nodes: {label: 12}
      });
      define_interface(BreakStatement, {
         nodes: {label: 12}
      });
      define_interface(ReturnStatement, {
         nodes: {argument: 12}
      });
      define_interface(LabeledStatement, {
         nodes: {label: 12, body: 16}
      });
      define_interface(WithStatement, {
         nodes: {object: 12, body: 16}
      });
      define_interface(ThrowStatement, {
         nodes: {argument: 12}
      });
      define_interface(TryStatement, {
         nodes: {block: 12, handler: 16, finalizer: 20}
      });
      define_interface(CatchClause, {
         nodes: {param: 12, body: 16}
      });
      define_interface(ClassBody, {
         lists: {body: 12}
      });
      group_end();
   }
}
Parser.to_json_time = 0;
Parser.list_time = 0;