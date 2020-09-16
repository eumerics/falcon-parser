#ifndef _SCANNER_BASE_H_
#define _SCANNER_BASE_H_

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"
#include "constants.h"
#include "interface.h"
#include "nodes.h"

#if defined(timing) || defined(profile)
   #define start_clock(x) \
      clock_t cbegin = clock(); \
      uint64_t clock_begin = __rdtsc();
   #define print_elapsed_time(name) { \
      uint64_t end = __rdtsc(); \
      clock_t cend = clock(); \
      printf("%s took %.3fms\n", name, 1000 * ((double)(cend - cbegin)) / CLOCKS_PER_SEC); \
   }
#else
   #define start_clock(x)
   #define print_elapsed_time(name)
#endif
#if defined(profile)
   #define note_elapsed_time(name, counts, timings, characters) \
      ++counts.name; \
      timings.name += __rdtsc() - clock_begin; \
      characters.name += (result - string);
#else
   #define note_elapsed_time(name, counts, timings, characters)
#endif

inline_spec int is_binary(char_t d)
{
   return (d >= '0' & d <= '1');
}
inline_spec int is_octal(char_t d)
{
   return (d >= '0' & d <= '7');
}
inline_spec int is_decimal(char_t d)
{
   return (d >= '0' & d <= '9');
}
inline_spec int is_hex(char_t h)
{
   char_t hl = h | 0x20; // lower case h
   return ((h >= '0' & h <= '9') | (hl >= 'a' & hl <= 'f'));
}
inline_spec int is_identifier_start(char_t c)
{
   char_t l = c | 0x20; // lower
   return (l >= 'a' && l <= 'z') || c == '$' || c == '_';
}

inline_spec char_t const* scan_string_literal(char_t const* string, char_t const* end)
{
   char_t const* begin = string;
   char_t const quote = *string; ++string;
   while(string < end) {
      if(*string == quote) return ++string;
      if(*string == '\\') {
         ++string;
         if(string == end) return begin;
         char_t const c = *string;
         int hex_chars = 0;
         int code_point = 0;
         if(c == 'x') {
            hex_chars = 2;
            ++string;
         } else if(c == 'u') {
            if(*(string + 1) == '{') {
               code_point = 1;
               ++string;
            } else {
               hex_chars = 4;
            }
            ++string;
         } else if(c == '\n') { // \u2028 <LS> \u2029 <PS>
            ++string;
         } else if(c == '\r') {
            if(++string == end) return begin;
            if(c == '\n') ++string;
         } else {
            ++string;
         }
         if(code_point) {
            // buffer should be two additional characters long
            while(*string != '}') {
               if(string >= end) return begin;
               if(!is_hex(*string)) return begin;
               ++string; ++hex_chars;
            }
            ++string;
         } else if(hex_chars != 0) {
            if(string + hex_chars >= end) return begin;
            for(int hi = 0; hi < hex_chars; ++hi, ++string) {
               if(!is_hex(*string)) return begin;
            }
         }
      } else {
         ++string;
      }
   }
   return begin;
}

inline_spec char_t const* scan_numeric_literal(char_t const* string, char_t const* end)
{
   //[TODO] spacing character _
   if(string == end) return string;
   char_t const* begin = string;
   if(*string == '0') {
      if(++string == end) return string;
      char_t lower = *string | 0x20;
      char_t const* digit_begin = string + 1;
      if(lower == 'x') { // hexadecimal number
         while(++string < end && is_hex(*string));
      } else if(lower == 'b') {
         while(++string < end && is_binary(*string));
      } else if(lower == 'o') {
         while(++string < end && is_octal(*string));
      } else {
         goto decimal;
      }
      if(string == digit_begin) return begin;
      if(string == end) return string;
      // https://tc39.es/ecma262/#sec-literals-numeric-literals
      // The SourceCharacter immediately following a NumericLiteral
      // must not be an IdentifierStart or DecimalDigit
      return ((is_identifier_start(*string) || is_decimal(*string)) ? begin : string);
   }
decimal:
   // parse the integer part
   if(*string != '.') {
      do {
         if(!is_decimal(*string)) break;
      } while(++string < end);
      if(string == end) return string;
   }
   // parse the decimal part
   if(*string == '.') {
      while(++string < end) {
         if(!is_decimal(*string)) break;
      }
      if(string - begin == 1) return begin; // . must follow atleast a digit
      if(string == end) return string;
   }
   // parse the exponent
   if(((*string | 0x20) == 'e') && (string - begin > 0)) {
      char_t c = *(++string);
      if(c == '+' || c == '-') ++string;
      int decimal_digits = 0;
      do {
         if(!is_decimal(*string)) break;
         ++decimal_digits;
      } while(++string < end);
      return (decimal_digits == 0 ? begin : string);
   }
   return string;
}

// low 8-bits: length of flags
// high 24-bits: length of the literal
//[LIMITATION]: regular expression literal length is less than 1<<24 and the
// number of flags are less than 1<<8.
inline_spec uint32_t scan_regexp_literal(char_t const* string, char_t const* end)
{
   char_t const* begin = string;
   while(1) {
      if(++string == end) return 0;
      char_t current = *string;
      if(current == '/') { ++string; break; }
      if(current == '\n' || current == '\r') return 0;
      // take care of scenarios where '/' fails to serve as a closing tag
      if(current == '\\') {
         // for scanning it is enough to eat next character
         // as long as it is not a line terminator
         char_t next = *(++string);
         if(next == '\n' || next == '\r') return 0;
      } else if(current == '[') {
         while(1) {
            if(++string >= end) return 0;
            if(*string == ']') break;
            if(*string == '\\') {
               char_t next = *(++string);
               if(next == '\n' || next == '\r') return 0;
            }
         }
      }
   }
   // parse flags
   char_t c = *string;
   char_t const* flag_begin = string;
   while(c == 'g' || c == 'i' || c == 'm' || c == 's' || c == 'u' || c == 'y'){
      if(++string == end) return ((end - begin) << 24) | (string - flag_begin);
      c = *string;
   }
   return ((string - begin) << 24) | (string - flag_begin);
}

inline_spec char_t const* scan_comment(char_t const* string, char_t const* const end)
{
   char_t const* begin = string;
   char_t type = *(string + 1);
   string += 2;
   if(type == '/') {
      do {
         char_t current = *string;
         if(current == '\n' || current == '\r') return string;
      } while(++string != end);
      return string;
   } else {
      do {
         char_t current = *string;
         if(current == '*') {
            if(string + 1 == end) return begin;
            if(*(string + 1) == '/') return string + 2;
            continue;
         }
      } while(++string != end);
      return begin;
   }
}

/*
inline_spec char_t scan_punctuator(char_t const* string, char_t const* end)
{
   char_t c = *string;
   if(c == '{' || c == '}' || c == '(' || c == ')' || c == '[' || c == ']' ||
      c == '?' || c == ':' || c == '.' || c == ';' || c == ',' || c == '~'
   ){
      return 1;
   }
   char_t c1 = *(string + 0);
   char_t c2 = *(string + 1);
   if((c1 == '+' && c2 == '+') || (c1 == '-' && c2 == '-') ||
      (c1 == '&' && c2 == '&') || (c1 == '|' && c2 == '|') ||
      (c1 == '+' && c2 == '=') || (c1 == '-' && c2 == '=') ||
      (c1 == '*' && c2 == '=') || (c1 == '/' && c2 == '=') ||
      (c1 == '%' && c2 == '=') || (c1 == '&' && c2 == '=') ||
      (c1 == '|' && c2 == '=') || (c1 == '^' && c2 == '=') ||
      (c1 == '<' && c2 == '=') || (c1 == '>' && c2 == '=')
   ){
      return 2;
   }
   char_t c3 = *(string + 2);
   char_t c4 = *(string + 3);
   if(c1 == '>' && c2 == '>' && c3 == '>' && c4 == '=') {
      return 4;
   }
   if((c1 == '=' && c2 == '=' && c3 == '=') ||
      (c1 == '!' && c2 == '=' && c3 == '=') ||
      (c1 == '<' && c2 == '<' && c3 == '=') ||
      (c1 == '>' && c2 == '>' && c3 == '=') ||
      (c1 == '>' && c2 == '>' && c3 == '>') ||
      (c1 == '>' && c2 == '>' && c3 == '=')
   ){
      return 3;
   }
   if((c1 == '=' && c2 == '=') || (c1 == '!' && c2 == '=') ||
      (c1 == '<' && c2 == '<') || (c1 == '>' && c2 == '>')
   ){
      return 2;
   }
   if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '&' ||
      c == '|' || c == '^' || c == '<' || c == '>' || c == '=' || c == '!'
   ){
      return 1;
   }
   return 0;
}
//*/

///*
//  [9] { } ( ) [ ] ; , :
//  [5] ? . ... => ?.
//  [2] ++ --
//  [8] < > <= >= == != === !==
// [13] + - * / % **  ------  = += -= *= /= %= **=
//  [8]    & | ^ ! ~  ------    &= |= ^=
//  [6]     && || ??  ------    &&= ||= ??=
//  [6]    << >> >>>  ------    <<= >>= >>>=
// [57]
#define combine(id, group, precedence, token_flags) \
   ((uint32_t)(token_flags)) | (((uint32_t)(precedence)) << 3) | (((uint32_t)(id)) << 8) | (((uint32_t)(group)) << 16)
inline_spec uint32_t scan_punctuator(char_t const* string, char_t const* end)
{
   char_t c1 = *string;
   char_t c2 = *(string + 1);
   //[14] { } ( ) [ ] ; , : . === == => =
   if(c1 == '(' || c1 == ')') return combine(c1, mask_parentheses, precedence_none, 1);
   if(c1 != c2) { // . => =
      if(c1 == '.') return combine(c1, mask_none, precedence_none, 1);
      if(c1 == '=') {
         if(c2 == '>') return combine(pnct_arrow, mask_none, precedence_none, 2);
         return combine(c1, mask_assign_ops, precedence_none, 1);
      }
   } else { // === ==
      if(c1 == '=') {
         char_t c3 = *(string + 2);
         if(c3 == '=') return combine(pnct_strict_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 3);
         return combine(pnct_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 2);
      }
   }
   if(c1 == ';' || c1 == ',') return combine(c1, mask_none, precedence_none, 1);
   if(c1 == '{' || c1 == '['){
      return combine(c1, mask_parentheses | mask_let_inclusions, precedence_none, 1);
   }
   if(c1 == '}' || c1 == ']'){
      return combine(c1, mask_parentheses, precedence_none, 1);
   }
   if(c1 == ':') return combine(c1, mask_none, precedence_none, 1);
   //[17] >>>= >>> ... <<= >>= &&= ||= **= ??= ++ -- << >> && || ** ??
   if(c1 == c2) {
      char_t c3 = *(string + 2);
      if(c3 == '=') { // <<= >>= &&= ||= **= ??=
         switch(c1) {
            case '?': return combine(pnct_inplace_logical_coalesce, mask_assign_ops, precedence_none, 3);
            case '&': return combine(pnct_inplace_logical_and, mask_assign_ops, precedence_none, 3);
            case '|': return combine(pnct_inplace_logical_or, mask_assign_ops, precedence_none, 3);
            case '<': return combine(pnct_inplace_shift_left, mask_assign_ops, precedence_none, 3);
            case '>': return combine(pnct_inplace_shift_right, mask_assign_ops, precedence_none, 3);
            case '*': return combine(pnct_inplace_exponentiation, mask_assign_ops, precedence_none, 3);
         }
      } else {
         switch(c1) {
            // && || ??
            case '&': return combine(pnct_logical_and, mask_logical_ops, precedence_logical_and, 2);
            case '|': return combine(pnct_logical_or, mask_logical_ops, precedence_logical_or, 2);
            case '?': return combine(pnct_logical_coalesce, mask_none, precedence_logical_coalesce, 2);
            // ++ --
            case '+': return combine(pnct_increment, mask_update_ops, precedence_none, 2);
            case '-': return combine(pnct_decrement, mask_update_ops, precedence_none, 2);
            // <<
            case '<': return combine(pnct_shift_left, mask_shift_ops | mask_binary_ops, precedence_shift, 2);
            // >>>= >>> >>
            case '>': {
               if(c3 == '>') { // >>>= >>>
                  char_t c4 = *(string + 3);
                  if(c4 == '=') {
                     return combine(pnct_inplace_unsigned_shift_right, mask_assign_ops, precedence_none, 4);
                  } else {
                     return combine(pnct_unsigned_shift_right, mask_shift_ops | mask_binary_ops, precedence_shift, 3);
                  }
               } else { // >>
                  return combine(pnct_shift_right, mask_shift_ops | mask_binary_ops, precedence_shift, 2);
               }
            }
            // **
            case '*': return combine(pnct_exponentitation, mask_arithmetic_ops, precedence_none, 2);
            // ...
            case '.': if(c3 == '.') return combine(pnct_spread, mask_none, precedence_none, 3);
            // fallthrough
         }
      }
   }
   if(c2 == '=') {
      //[2] !== !=
      if(c1 == '!') {
         char_t c3 = *(string + 2);
         if(c3 == '=') return combine(pnct_strict_not_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 3);
         else return combine(pnct_not_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 2);
      }
      //[10] += -= *= /= %= &= |= ^= <= >=
      switch(c1) {
         case '+': return combine(pnct_inplace_add, mask_assign_ops, precedence_none, 2);
         case '-': return combine(pnct_inplace_substract, mask_assign_ops, precedence_none, 2);
         case '*': return combine(pnct_inplace_mulitply, mask_assign_ops, precedence_none, 2);
         case '/': return combine(pnct_inplace_divide, mask_assign_ops, precedence_none, 2);
         case '%': return combine(pnct_inplace_remainder, mask_assign_ops, precedence_none, 2);
         case '&': return combine(pnct_inplace_binary_and, mask_assign_ops, precedence_none, 2);
         case '|': return combine(pnct_inplace_binary_or, mask_assign_ops, precedence_none, 2);
         case '^': return combine(pnct_inplace_binary_xor, mask_assign_ops, precedence_none, 2);
         case '<': return combine(pnct_lesser_or_equals, mask_comparison_ops | mask_binary_ops, precedence_relational, 2);
         case '>': return combine(pnct_greater_or_equals, mask_comparison_ops | mask_binary_ops, precedence_relational, 2);
      }
   }
   {
      //[3] ? ?.
      if(c1 == '?') {
         if(c2 == '.') return combine(pnct_optional, mask_none, precedence_none, 2);
         else return combine(c1, mask_none, precedence_none, 1);
      }
      //[11] + - * / % & | ^ ! < >
      if(c1 == '+' || c1 == '-') {
         return combine(c1, mask_arithmetic_ops | mask_unary_ops | mask_binary_ops, precedence_additive, 1);
      } else if(c1 == '*' || c1 == '/' || c1 == '%') {
         return combine(c1, mask_arithmetic_ops | mask_binary_ops, precedence_multiplicative, 1);
      } else if(c1 == '&') {
         return combine(c1, mask_arithmetic_ops | mask_binary_ops, precedence_bitwise_and, 1);
      } else if(c1 == '|') {
         return combine(c1, mask_arithmetic_ops | mask_binary_ops, precedence_bitwise_or, 1);
      } else if(c1 == '^') {
         return combine(c1, mask_arithmetic_ops | mask_binary_ops, precedence_bitwise_xor, 1);
      } else if(c1 == '<' || c1 == '>') {
         return combine(c1, mask_comparison_ops | mask_binary_ops, precedence_relational, 1);
      } else if(c1 == '!') {
         return combine(c1, mask_logical_ops | mask_unary_ops, precedence_none, 1);
      }
   }
   //[1] ~
   if(c1 == '~') return combine(c1, mask_unary_ops, precedence_none, 1);
   return 0;
}
//*/

inline_spec char_t const* scan_identifier(char_t const* string, char_t const* const end)
{
   char_t const* const begin = string;
   while(++string < end) {
      char_t c = *string;
      char_t cl = c | 0x20;
      int is_valid =
         (cl >= 'a' && cl <= 'z') ||
         (c >= '0' && c <= '9') ||
         c == '$' || c == '_'
      ;
      if(!is_valid) return string;
   }
   return string;
}

inline_spec uint32_t scan_template_characters(char_t const* string, char_t const* const end)
{
   uint32_t const error_result = 0x80000000;
   char_t const* const begin = string;
   while(string < end) {
      char_t c = *string;
      if(c == '`' || (c == '$' && (*(string + 1) == '{'))) return string - begin;
      if(c == '\\') {
         if(string + 1 == end) return error_result;
         else ++string;
      }
      ++string;
   }
   return error_result;
}

/*
inline_spec int is_reserved(char_t const* string, char_t first_char, int length)
{
   if(length == 0) return 0;
   #define _strncmp(kw) strncmp_impl(string, stringize(kw), strlen_impl(stringize(kw)))
   return
      !_strncmp(await) || !_strncmp(break) || !_strncmp(case) ||
      !_strncmp(catch) || !_strncmp(class) || !_strncmp(const) ||
      !_strncmp(continue) || !_strncmp(debugger) || !_strncmp(default) ||
      !_strncmp(delete) || !_strncmp(do) || !_strncmp(else) ||
      !_strncmp(enum) || !_strncmp(export) || !_strncmp(extends) ||
      !_strncmp(false) || !_strncmp(finally) || !_strncmp(for) ||
      !_strncmp(function) || !_strncmp(if) || !_strncmp(import) ||
      !_strncmp(in) || !_strncmp(instanceof) || !_strncmp(new) ||
      !_strncmp(null) || !_strncmp(return) || !_strncmp(super) ||
      !_strncmp(switch) || !_strncmp(this) || !_strncmp(throw) ||
      !_strncmp(true) || !_strncmp(try) || !_strncmp(typeof) ||
      !_strncmp(var) || !_strncmp(void) || !_strncmp(while) ||
      !_strncmp(with) || !_strncmp(yield) ||
      !_strncmp(implements) || !_strncmp(interface) || !_strncmp(package) ||
      !_strncmp(private) || !_strncmp(protected) || !_strncmp(public)
   ;
   #undef _strncmp
}
*/

inline_spec uint32_t is_reserved(char_t const* string, char_t const first_char, int const length)
{
   if(length == 0) return 0;
   #if defined(profile)
      #define _strncmp(kw) ( \
         ++characters1.string_compares, \
         strncmp_impl(string, stringize(kw), strlen_impl(stringize(kw))) \
      )
   #else
      #define _strncmp(kw) strncmp_impl(string, stringize(kw), strlen_impl(stringize(kw)))
   #endif
   #define _rwid(word) combine(rw_##word, rwg_##word, rwp_##word, token_flag_none)
   #define return_comparison_with(string) return (_strncmp(string) == 0 ? _rwid(string) : 0);
   #define return_comparison_with_vec2(string1, string2) { \
      if(!_strncmp(string1)) return _rwid(string1); \
      if(!_strncmp(string2)) return _rwid(string2); \
      return 0; \
   }
   #define return_comparison_with_vec3(string1, string2, string3) { \
      if(!_strncmp(string1)) return _rwid(string1); \
      if(!_strncmp(string2)) return _rwid(string2); \
      if(!_strncmp(string3)) return _rwid(string3); \
      return 0; \
   }
   switch(first_char) {
      case 'a': {
         switch(length) {
            //case 5: return_comparison_with(await);
            case 2: return_comparison_with(as);
            case 5: return_comparison_with_vec2(async, await);
            default: return 0;
         }
      }
      case 'b': {
         switch(length) {
            case 5: return_comparison_with(break);
            default: return 0;
         }
      }
      case 'c': {
         switch(length) {
            case 4: return_comparison_with(case);
            case 5: return_comparison_with_vec3(catch, class, const);
            case 8: return_comparison_with(continue);
            default: return 0;
         }
      }
      case 'd': {
         switch(length) {
            case 8: return_comparison_with(debugger);
            case 7: return_comparison_with(default);
            case 6: return_comparison_with(delete);
            case 2: return_comparison_with(do);
            default: return 0;
         }
      }
      case 'e': {
         switch(length) {
            case 4: return_comparison_with_vec2(else, enum);
            case 6: return_comparison_with(export);
            case 7: return_comparison_with(extends);
            default: return 0;
         }
      }
      case 'f': {
         switch(length) {
            case 4: return_comparison_with(from);
            case 5: return_comparison_with(false);
            case 7: return_comparison_with(finally);
            case 3: return_comparison_with(for);
            case 8: return_comparison_with(function);
            default: return 0;
         }
      }
      case 'g': {
         switch(length) {
            case 3: return_comparison_with(get);
         }
      }
      case 'i': {
         switch(length) {
            case 2: return_comparison_with_vec2(if, in);
            case 6: return_comparison_with(import);
            case 9: return_comparison_with(interface);
            case 10: return_comparison_with_vec2(implements, instanceof);
            default: return 0;
         }
      }
      case 'l': {
         switch(length) {
            case 3: return_comparison_with(let);
            default: return 0;
         }
      }
      case 'n': {
         switch(length) {
            case 3: return_comparison_with(new);
            case 4: return_comparison_with(null);
            default: return 0;
         }
      }
      case 'o': {
         switch(length) {
            case 2: return_comparison_with(of);
         }
      }
      case 'p': {
         switch(length) {
            case 6: return_comparison_with(public);
            case 7: return_comparison_with_vec2(package, private);
            case 9: return_comparison_with(protected);
         }
      }
      case 'r': {
         switch(length) {
            case 6: return_comparison_with(return);
            default: return 0;
         }
      }
      case 's': {
         switch(length) {
            case 3: return_comparison_with(set);
            case 5: return_comparison_with(super);
            case 6: return_comparison_with_vec2(static, switch);
            default: return 0;
         }
      }
      case 't': {
         switch(length) {
            case 4: return_comparison_with_vec2(this, true);
            case 5: return_comparison_with(throw);
            case 3: return_comparison_with(try);
            case 6: return_comparison_with_vec2(typeof, target);
            default: return 0;
         }
      }
      case 'v': {
         switch(length) {
            case 3: return_comparison_with(var);
            case 4: return_comparison_with(void);
            default: return 0;
         }
      }
      case 'w': {
         switch(length) {
            case 5: return_comparison_with(while);
            case 4: return_comparison_with(with);
            default: return 0;
         }
      }
      case 'y': {
         switch(length) {
            case 5: return_comparison_with(yield);
            default: return 0;
         }
      }
      default: return 0;
   }
   #undef _rwid
   #undef _strncmp
   #undef return_comparison_with
   #undef return_comparison_with_vec2
   #undef return_comparison_with_vec3
}

#define finalize_token(_begin, _end) \
   current_token->begin = _begin; \
   current_token->end = _end; \
   ++current_token;
#define assign_token(_id, _group, _precedence) \
   *current_token = (token_t){ \
      .begin = string - begin, .end = result - begin, \
      .id = _id, .group = _group, \
      .flags = (_precedence << 3) | token_flags \
   }; \
   ++current_token;
#define assign_char_token(_id) { \
   size_t offset = string - begin; \
   *current_token = (token_t){ \
      .begin = offset, .end = offset + 1, \
      .id = _id, .group = mask_none, .flags = token_flag_none \
   }; \
   ++current_token; \
   result = string + 1; \
}

wasm_export scan_result_t tokenize(char_t const* string, char_t const* end)
{
   if_verbose( begin_group("tokenization"); )
   start_clock();
   // additional eot token and 2 more dummy tokens for algorithmic convenience
   size_t predicted_tokens = ((end - string) / 1) + 3;
   token_t* tokens = (token_t*) malloc(predicted_tokens * sizeof(token_t));
   token_t* current_token = tokens;
   token_t* end_token = current_token + predicted_tokens;

   char_t const* begin = string;
   char_t const* result;
   int regexp_context = 1;
   uint8_t token_flags = token_flag_none;
   uint32_t template_level = 0;
   int in_template_expression = 0;
   while(string < end) {
      uint8_t current_token_flags = token_flag_none;
      char_t current = *string;
      char_t next = *(string + 1);
      char_t lower = current | 0x20;
      if(current == '`' || (template_level != 0 && current == '}')) {
         // the only purpose of saved_string is for debugging
         char_t const* saved_string = string;
         if(current == '`'){
            if(template_level == 0 || in_template_expression){
               ++template_level;
            } else {
               --template_level;
            }
            assign_char_token('`');
         } else {
            assign_char_token('}');
         }
         if(template_level == 0) string = saved_string;
         while(template_level > 0) {
            string = result; token_flags = current_token_flags;
            uint32_t error_result = 0x80000000;
            uint32_t length = scan_template_characters(string, end);
            if(length == error_result) {
               break;
            } else {
               if(length != 0) {
                  result = string + length;
                  assign_token(tkn_template_string, mask_none, precedence_none);
                  string = result;
               }
               if(*string == '`') {
                  assign_char_token('`');
                  --template_level;
                  in_template_expression = (template_level > 0);
               } else { // ${
                  assign_char_token('$'); string = result;
                  assign_char_token('{');
                  in_template_expression = 1;
               }
               if(in_template_expression) {
                  string = saved_string;
                  break;
               }
            }
         }
         if_verbose(print_string("template: "));
      } else if((lower >= 'a' && lower <= 'z') || current == '$' || current == '_') {
         regexp_context = 0;
         start_clock();
         result = scan_identifier(string, end);
         note_elapsed_time(identifier, counts1, timings1, characters1);
         if(result != string){
            start_clock();
            size_t length = result - string;
            uint32_t reserved_word_id = is_reserved(string, current, length);
            note_elapsed_time(reserved_word, counts1, timings1, characters1);
            if(reserved_word_id == 0) {
               assign_token(tkn_identifier, mask_identifier, precedence_none);
               if_verbose(print_string("identifier: "));
            } else {
               //current_token->aggregated_id = combine(reserved_word_id, mask_reserved_word, tkn_keyword);
               current_token->aggregated_id = reserved_word_id | token_flags;
               finalize_token(string - begin, result - begin);
               if_verbose(print_string("reserved_word: "));
               regexp_context = 1;
            }
         }
      } else if(current == ' ' || current == '\t') {
         result = string;
         start_clock();
         while(++result < end && (*result == ' ' || *result == '\t'));
         //assign_token(tkn_whitespace, mask_none, precedence_none);
         current_token_flags = token_flags;
         note_elapsed_time(whitespace, counts1, timings1, characters1);
         if_verbose(print_string("space: "));
      } else if(current == '\r' || current == '\n') {
         result = string;
         start_clock();
         while(++result < end && (*result == '\r' || *result == '\n'));
         //assign_token(tkn_terminator, mask_none, precedence_none);
         current_token_flags |= token_flag_newline;
         note_elapsed_time(terminator, counts1, timings1, characters1);
         if_verbose(print_string("newline: "));
      } else if((current >= '0' && current <= '9') ||
         (current == '.' && (*(string + 1) >= '0' && *(string + 1) <= '9'))
      ){
         regexp_context = 0;
         start_clock();
         result = scan_numeric_literal(string, end);
         assign_token(tkn_numeric_literal, mask_literal, precedence_none);
         note_elapsed_time(numeric_literal, counts1, timings1, characters1);
         if_verbose(print_string("number: "));
      } else if(current == '\'' || current == '"') {
         regexp_context = 0;
         start_clock();
         result = scan_string_literal(string, end);
         assign_token(tkn_string_literal, mask_literal, precedence_none);
         note_elapsed_time(string_literal, counts1, timings1, characters1);
         if_verbose(print_string("string: "));
      } else if(current == '/') {
         if(next == '/' || next == '*') {
            start_clock();
            result = scan_comment(string, end);
            //assign_token(tkn_comment, mask_none, precedence_none);
            note_elapsed_time(comment, counts1, timings1, characters1);
            if_verbose(print_string("comment: "));
         } else if(regexp_context) {
            start_clock();
            //result = scan_regexp_literal(string, end);
            uint32_t lengths = scan_regexp_literal(string, end);
            uint8_t flags_length = lengths & 0xff;
            result = string + (lengths >> 24);
            assign_token(tkn_regexp_literal, mask_none, flags_length);
            note_elapsed_time(regexp_literal, counts1, timings1, characters1);
            if_verbose(print_string("regexp: "));
         } else {
            regexp_context = 1;
            start_clock();
            uint32_t aggregated_id = scan_punctuator(string, end);
            uint8_t length = aggregated_id & 0x07;
            result = string + length;
            current_token->aggregated_id = (aggregated_id & 0xfffffff8) | token_flags;
            finalize_token(string - begin, result - begin);
            note_elapsed_time(punctuator, counts1, timings1, characters1);
            if_verbose(print_string("punctuator: "));
         }
      } else {
         regexp_context = (current == ')' || current == ']' ? 0 : 1);
         start_clock();
         uint32_t aggregated_id = scan_punctuator(string, end);
         uint8_t length = aggregated_id & 0x07;
         result = string + length;
         current_token->aggregated_id = (aggregated_id & 0xfffffff8) | token_flags;
         finalize_token(string - begin, result - begin);
         note_elapsed_time(punctuator, counts1, timings1, characters1);
         if_verbose(print_string("punctuator: "));
      }
      if(result == string) {
         //printf("\nparse failed at %ld\n", string - begin);
         return (scan_result_t){
            .tokens = tokens,
            .token_count = current_token - tokens,
            .return_value = 0
         };
      }
      //if_verbose(printf("%.*s\n", result - string, string));
      //if_verbose(show_token("%.*s\n", result - string, string));
      print_token(string, result - string);
      //printf("%.*s (%d, %d)\n", result - string, string, string - begin, result - string);
      token_flags = current_token_flags;
      string = result;
   }
   *current_token = (token_t){
      .begin = end - begin,
      .end = end - begin,
      .precedence = precedence_none,
      .id = tkn_eot,
      .group = 0
      //.aggregated_id = __token_aggr_id
   };
   ++current_token;
   //printf("%d %d %d\n", predicted_tokens, (current_token - tokens), sizeof(token_t));
   if_verbose( end_group(); )
   print_elapsed_time("tokenization");
   return (scan_result_t){
      .tokens = tokens,
      .token_count = current_token - tokens,
      .return_value = 1
   };
   //if(string == end) printf("parsing succesful\n");
}

#endif //_SCANNER_BASE_H_
