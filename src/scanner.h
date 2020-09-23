#ifndef _SCANNER_BASE_H_
#define _SCANNER_BASE_H_

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"
#include "constants.h"
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
      timings.name += __rdtsc() - clock_begin;
#else
   #define note_elapsed_time(name, counts, timings, characters)
#endif
//characters.name += (result - string);

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
inline_spec int is_line_terminator(char_t c)
{
   #if defined(UTF16)
      return (c == '\r' || c == '\n' || c == 0x2028 || c == 0x2029);
   #else
      return (c == '\r' || c == '\n');
   #endif
}

inline_spec void make_char_token(scan_state_t* state, uint8_t const id)
{
   size_t offset = state->code - state->code_begin;
   *(state->token) = (token_t){
      .begin = offset, .end = offset + 1,
      .id = id, .group = mask_none, .flags = token_flag_none,
      .detail = nullptr
   };
   ++state->token;
   ++state->code;
}

inline_spec void make_token(
   scan_state_t* const state, char_t const* begin,
   uint8_t const id, uint16_t const group,
   uint8_t const contextual, void* detail
){
   *(state->token) = (token_t){
      .begin = begin - state->code_begin,
      .end = state->code - state->code_begin,
      .id = id, .group = group, .flags = (contextual << 3 | state->token_flags),
      .detail = detail
   };
   ++state->token;
}

inline_spec void make_aggregated_token(
   scan_state_t* const state, char_t const* begin,
   uint32_t const aggregated_id, void* detail
){
   *(state->token) = (token_t){
      .begin = begin - state->code_begin,
      .end = state->code - state->code_begin,
      .aggregated_id = aggregated_id,
      .detail = detail
   };
   ++state->token;
}

// [LIMITATION] string length is 1-bit shorter than what the platform can
// support i.e, 1 << (size(ptrdiff_t) * 8 - 1), for nearly all cases this
// should not be a problem at all
ptrdiff_t escaped_string_flag = (ptrdiff_t)(1) << (sizeof(ptrdiff_t)*8 - 1);
inline_spec ptrdiff_t prescan_string_literal(char_t const* code, char_t const* const end)
{
   char_t const* const begin = code;
   char_t const quote = *code;
   ptrdiff_t string_type = 0;
   while(++code < end) {
      char_t c = *code;
      switch(c) {
         case '\r': case '\n': return 0;
         case '\\': {
            string_type = escaped_string_flag;
            if(*++code == '\r') {
               if(*(code + 1) == '\n') ++code;
            }
            break;
         }
         default: if(c == quote) return (++code - begin) | string_type;
      }
   }
   return 0;
}
compiled_string_t* compile_string(
   scan_state_t* const state, int for_template,
   char_t const* const begin, char_t const* const end
)
{
   char_t const* code = begin - 1;
   char_t* compiled = parser_malloc((end - begin) * sizeof(char_t));
   char_t const* const compiled_begin = compiled;
   while(++code < end) {
      char_t c = *code;
      if(c != '\\') {
         // Very odd behavior for template LineTerminatorSequences
         // https://tc39.es/ecma262/#sec-static-semantics-tv-and-trv
         // NOTE: TV excludes the code units of LineContinuation while TRV
         // includes them. <CR><LF> and <CR> LineTerminatorSequences are
         // normalized to <LF> for both TV and TRV. An explicit EscapeSequence
         // is needed to include a <CR> or <CR><LF> sequence.
         if(!for_template || c != '\r') {
            *compiled++ = c;
         } else {
            *compiled++ = '\n';
            if(*(code + 1) == '\n') ++code;
         }
      } else {
         char_t c = *(++code);
         uint16_t const line_separator = 0x2028;
         uint16_t const paragraph_separator = 0x2029;
         switch(c) {
            case 'r': *compiled++ = '\r'; break;
            case 'n': *compiled++ = '\n'; break;
            case 't': *compiled++ = '\t'; break;
            case 'v': *compiled++ = '\v'; break;
            case 'b': *compiled++ = '\b'; break;
            case 'f': *compiled++ = '\f'; break;
            //case '0': *compiled = '\0'; ++compiled; break;
            case '\r': if(*(code + 1) == '\n') ++code; break;
            case '\n': break;
         #if defined(UTF16)
            case line_separator: break;
            case paragraph_separator: break;
         #else
               //[TODO]
         #endif
            case 'x':
            case 'u': {
               uint32_t min_hex_chars = 0, max_hex_chars = 0, is_code_point = 0;
               if(c == 'x') { min_hex_chars = max_hex_chars = 2; }
               else {
                  if(*(code + 1) == '{') {
                     is_code_point = 1, ++code;
                     min_hex_chars = 1, max_hex_chars = (uint32_t)(-1);
                  } else {
                     min_hex_chars = max_hex_chars = 4;
                  }
               }
               uint32_t hex = 0;
               for(int i = 0; i < max_hex_chars; ++i) {
                  char_t c = *++code, cl = c | 0x20;
                  hex <<= 4;
                  if(c >= '0' && c <= '9'){ hex |= (c - '0'); continue; }
                  if(cl >= 'a' && cl <= 'f'){ hex |= 10 + (cl - 'a'); continue; }
                  if(i < min_hex_chars) return 0;
                  else { --code; hex >>= 4; break; }
               }
               if(is_code_point && (*++code != '}')) return 0;
            #if defined(UTF16)
               if(hex & 0xffff0000) {
                  if(hex > 0x10ffff) return 0;
                  hex -= 0x10000;
                  *(compiled + 1) = (0b110111 << 10) | (hex & 0x3ff); hex >>= 10;
                  *(compiled + 0) = (0b110110 << 10) | (hex & 0x3ff); hex >>= 10;
                  compiled += 2;
               } else {
                  *compiled++ = (char_t)(hex);
               }
            #else
               //[TODO]
            #endif
               break;
            }
            default: {
               if(!for_template && (state->params & param_flag_annex) && c >= '0' && c <= '9') {
                  // legacy octal escape sequence
                  if(c >= '8') { *compiled++ = c; break; }
                  char_t octal = c - '0';
                  char_t o = *(code + 1);
                  if(!(o >= '0' && o <= '7')) { *compiled++ = octal; break; }
                  octal = (octal << 3) | (o - '0');
                  ++code;
                  if(c >= '4') break;
                  o = *(code + 1);
                  if(!(o >= '0' && o <= '7')) { *compiled++ = octal; break; }
                  octal = (octal << 3) | (o - '0');
                  ++code;
               } else if(c == '0' && (*(code + 1) < '0' || *(code + 1) > '9')){
                  *compiled++ = 0;
               } else if(c < '0' || c > '9'){
                  *compiled++ = c;
               } else {
                  return 0;
               }
            }
         }
      }
   }
   compiled_string_t* compiled_string = parser_malloc(sizeof(compiled_string_t));
   compiled_string->begin = compiled_begin;
   compiled_string->end = compiled;
   return compiled_string;
}
inline_spec int compile_string_literal(scan_state_t* const state)
{
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   ptrdiff_t length_and_flag = prescan_string_literal(begin, end);
   if(length_and_flag == 0) return 0;
   void* compiled_string = nullptr;
   size_t length = (length_and_flag & ~escaped_string_flag);
   if(length_and_flag & escaped_string_flag) {
      compiled_string = compile_string(state, 0, begin + 1, begin + length - 1);
      if(compiled_string == nullptr) return 0;
   }
   state->code = begin + length;
   make_token(state, begin, tkn_string_literal, mask_literal, precedence_none, compiled_string);
   return 1;
}
inline_spec int scan_string_literal(scan_state_t* const state)
{
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t const quote = *code; ++code;
   while(code < end) {
      if(*code == quote) { ++code; goto _make_string_token; }
      if(*code == '\\') {
         if(++code == end) return 0;
         char_t const c = *code;
         int hex_chars = 0;
         int code_point = 0;
         if(c == 'x') {
            hex_chars = 2;
            ++code;
         } else if(c == 'u') {
            if(code + 1 == end) return 0;
            if(*(code + 1) == '{') {
               code_point = 1;
               ++code;
            } else {
               hex_chars = 4;
            }
            ++code;
         } else if(c == '\n') { // \u2028 <LS> \u2029 <PS>
            ++code;
         } else if(c == '\r') {
            if(++code == end) return 0;
            if(*code == '\n') ++code;
         } else if((state->params & param_flag_annex) && c >= '0' && c <= '9'){
            if(c >= '8') ++code;
            else if(c >= '4') {
               if(++code != end && *code >= '0' && *code <= '7') ++code;
            } else {
               if(++code != end && *code >= '0' && *code <= '7')
               if(++code != end && *code >= '0' && *code <= '7') ++code;
            }
         } else {
            ++code;
         }
         if(code == end) return 0;
         if(code_point) {
            while(*code != '}') {
               if(!is_hex(*code)) return 0;
               ++code; ++hex_chars;
               if(code == end) return 0;
            }
            ++code;
         } else if(hex_chars != 0) {
            if(code + hex_chars > end) return 0;
            for(int hi = 0; hi < hex_chars; ++hi, ++code) {
               if(!is_hex(*code)) return 0;
            }
         }
      } else {
         ++code;
      }
   }
   return 0;
_make_string_token:
   state->code = code;
   make_token(state, begin, tkn_string_literal, mask_literal, precedence_none, nullptr);
   return 1;
}

inline_spec int scan_numeric_literal(scan_state_t* const state)
{
   //[TODO] spacing character _
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t c = *code;
   // parse the integer part
   if(c == '0') {
      if(++code == end) goto _make_numeric_token;
      char_t c = *code;
      if((state->params & param_flag_annex) && (c >= '0' && c <= '7')) {
         while(++code < end && (*code >= '0' && *code <= '7'));
      } else {
         char_t lower = *code | 0x20;
         char_t const* digit_begin = code + 1;
         if(lower == 'x') { // hexadecimal number
            while(++code < end && is_hex(*code));
         } else if(lower == 'b') {
            while(++code < end && is_binary(*code));
         } else if(lower == 'o') {
            while(++code < end && is_octal(*code));
         }
         if(code == digit_begin) return 0;
      }
   } else if(c >= '1' && c <= '9') {
      while(++code < end && is_decimal(*code));
   }
   if(code == end) goto _make_numeric_token;
   // parse the decimal part
   if(*code == '.') {
      while(++code < end && is_decimal(*code));
      if(code - begin == 1) return 0; // . must follow atleast a digit
      if(code == end) goto _make_numeric_token;
   }
   // parse the exponent
   if(((*code | 0x20) == 'e') && (code - begin > 0)) {
      if(code + 1 == end) return 0;
      char_t c = *(code + 1);
      if(c == '+' || c == '-') ++code;
      char_t const* const exponent_begin = code + 1;
      while(++code < end && is_decimal(*code));
      if(code == exponent_begin) return 0;
      if(code == end) goto _make_numeric_token;
   }
   // https://tc39.es/ecma262/#sec-literals-numeric-literals
   // The SourceCharacter immediately following a NumericLiteral
   // must not be an IdentifierStart or DecimalDigit
   if(is_identifier_start(*code) || is_decimal(*code)) return 0;
_make_numeric_token:
   state->code = code;
   make_token(state, begin, tkn_numeric_literal, mask_literal, precedence_none, nullptr);
   return 1;
}

//[LIMITATION]: maximum number of allowed flags 1<<5 = 32.
inline_spec int scan_regexp_literal(scan_state_t* const state)
{
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   while(1) {
      if(++code == end) return 0;
      char_t current = *code;
      if(current == '/') { ++code; break; }
      if(current == '\n' || current == '\r') return 0;
      // take care of scenarios where '/' fails to serve as a closing tag
      if(current == '\\') {
         // for scanning it is enough to eat next character
         // as long as it is not a line terminator
         if(++code == end) return 0;
         char_t next = *code;
         if(next == '\n' || next == '\r') return 0;
      } else if(current == '[') {
         while(1) {
            if(++code == end) return 0;
            if(*code == ']') break;
            if(*code == '\\') {
               if(++code == end) return 0;
               char_t next = *code;
               if(next == '\n' || next == '\r') return 0;
            }
         }
      }
   }
   // parse flags
   char_t const* flags_begin = code;
   if(code < end) {
      char_t c = *code;
      while(c == 'g' || c == 'i' || c == 'm' || c == 's' || c == 'u' || c == 'y'){
         if(++code == end) break;
         c = *code;
      }
   }
   state->code = code;
   make_token(state, begin, tkn_regexp_literal, mask_none, code - flags_begin, nullptr);
   return 1;
}

inline_spec int scan_comment(scan_state_t* const state)
{
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t type = *(++code);
   if(type == '/') {
      while(++code != end) {
         if(is_line_terminator(*code)) goto _make_comment_token;
      }
   } else {
      while(++code != end) {
         char_t const c = *code;
         if(c == '*') {
            if(code + 1 == end) return 0;
            if(*(code + 1) == '/') {
               code += 2; goto _make_comment_token;
            }
         } else if(is_line_terminator(c)) {
            state->current_token_flags |= token_flag_newline;
         }
      }
      return 0;
   }
_make_comment_token:
   state->code = code;
   //make_token(state, begin, tkn_comment, mask_none, precedence_none, nullptr);
   return 1;
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
inline_spec int scan_punctuator(scan_state_t* const state)
{
   #define return_scan(id, group, precedence, length) { \
      code += length; \
      aggregated_id = combine(id, group, precedence, state->token_flags); \
      goto _make_punctuator_token; \
   }
   uint32_t aggregated_id;
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t c1 = *code;
   char_t c2 = (code + 1 < end ? *(code + 1) : 0);
   //[14] { } ( ) [ ] ; , : . === == => =
   if(c1 == '(' || c1 == ')') return_scan(c1, mask_parentheses, precedence_none, 1);
   if(c1 != c2) { // . => =
      if(c1 == '.') return_scan(c1, mask_none, precedence_none, 1);
      if(c1 == '=') {
         if(c2 == '>') return_scan(pnct_arrow, mask_none, precedence_none, 2);
         return_scan(c1, mask_assign_ops, precedence_none, 1);
      }
   } else { // === ==
      if(c1 == '=') {
         char_t c3 = (code + 2 < end ? *(code + 2) : 0);
         if(c3 == '=') return_scan(pnct_strict_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 3);
         return_scan(pnct_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 2);
      }
   }
   if(c1 == ';' || c1 == ',') return_scan(c1, mask_none, precedence_none, 1);
   if(c1 == '{') {
      ++state->parenthesis_level;
      return_scan(c1, mask_parentheses | mask_let_inclusions, precedence_none, 1);
   }
   if(c1 == '}'){
      --state->parenthesis_level;
      return_scan(c1, mask_parentheses, precedence_none, 1);
   }
   if(c1 == '[') return_scan(c1, mask_parentheses | mask_let_inclusions, precedence_none, 1);
   if(c1 == ']') return_scan(c1, mask_parentheses, precedence_none, 1);
   if(c1 == ':') return_scan(c1, mask_none, precedence_none, 1);
   //[17] >>>= >>> ... <<= >>= &&= ||= **= ??= ++ -- << >> && || ** ??
   if(c1 == c2) {
      char_t c3 = (code + 2 < end ? *(code + 2) : 0);
      if(c3 == '=') { // <<= >>= &&= ||= **= ??=
         switch(c1) {
            case '?': return_scan(pnct_inplace_logical_coalesce, mask_assign_ops, precedence_none, 3);
            case '&': return_scan(pnct_inplace_logical_and, mask_assign_ops, precedence_none, 3);
            case '|': return_scan(pnct_inplace_logical_or, mask_assign_ops, precedence_none, 3);
            case '<': return_scan(pnct_inplace_shift_left, mask_assign_ops, precedence_none, 3);
            case '>': return_scan(pnct_inplace_shift_right, mask_assign_ops, precedence_none, 3);
            case '*': return_scan(pnct_inplace_exponentiation, mask_assign_ops, precedence_none, 3);
         }
      } else {
         switch(c1) {
            // && || ??
            case '&': return_scan(pnct_logical_and, mask_logical_ops, precedence_logical_and, 2);
            case '|': return_scan(pnct_logical_or, mask_logical_ops, precedence_logical_or, 2);
            case '?': return_scan(pnct_logical_coalesce, mask_none, precedence_logical_coalesce, 2);
            // ++ --
            case '+': return_scan(pnct_increment, mask_update_ops, precedence_none, 2);
            case '-': return_scan(pnct_decrement, mask_update_ops, precedence_none, 2);
            // <<
            case '<': return_scan(pnct_shift_left, mask_shift_ops | mask_binary_ops, precedence_shift, 2);
            // >>>= >>> >>
            case '>': {
               if(c3 == '>') { // >>>= >>>
                  char_t c4 = (code + 3 < end ? *(code + 3) : 0);
                  if(c4 == '=') {
                     return_scan(pnct_inplace_unsigned_shift_right, mask_assign_ops, precedence_none, 4);
                  } else {
                     return_scan(pnct_unsigned_shift_right, mask_shift_ops | mask_binary_ops, precedence_shift, 3);
                  }
               } else { // >>
                  return_scan(pnct_shift_right, mask_shift_ops | mask_binary_ops, precedence_shift, 2);
               }
            }
            // **
            case '*': return_scan(pnct_exponentitation, mask_arithmetic_ops, precedence_none, 2);
            // ...
            case '.': if(c3 == '.') return_scan(pnct_spread, mask_none, precedence_none, 3);
            // fallthrough
         }
      }
   }
   if(c2 == '=') {
      //[2] !== !=
      if(c1 == '!') {
         char_t c3 = (code + 2 < end ? *(code + 2) : 0);
         if(c3 == '=') { return_scan(pnct_strict_not_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 3); }
         else { return_scan(pnct_not_equals, mask_comparison_ops | mask_binary_ops, precedence_equality, 2); }
      }
      //[10] += -= *= /= %= &= |= ^= <= >=
      switch(c1) {
         case '+': return_scan(pnct_inplace_add, mask_assign_ops, precedence_none, 2);
         case '-': return_scan(pnct_inplace_substract, mask_assign_ops, precedence_none, 2);
         case '*': return_scan(pnct_inplace_mulitply, mask_assign_ops, precedence_none, 2);
         case '/': return_scan(pnct_inplace_divide, mask_assign_ops, precedence_none, 2);
         case '%': return_scan(pnct_inplace_remainder, mask_assign_ops, precedence_none, 2);
         case '&': return_scan(pnct_inplace_binary_and, mask_assign_ops, precedence_none, 2);
         case '|': return_scan(pnct_inplace_binary_or, mask_assign_ops, precedence_none, 2);
         case '^': return_scan(pnct_inplace_binary_xor, mask_assign_ops, precedence_none, 2);
         case '<': return_scan(pnct_lesser_or_equals, mask_comparison_ops | mask_binary_ops, precedence_relational, 2);
         case '>': return_scan(pnct_greater_or_equals, mask_comparison_ops | mask_binary_ops, precedence_relational, 2);
      }
   }
   {
      //[3] ? ?.
      if(c1 == '?') {
         if(c2 == '.') { return_scan(pnct_optional, mask_none, precedence_none, 2); }
         else { return_scan(c1, mask_none, precedence_none, 1); }
      }
      //[11] + - * / % & | ^ ! < >
      if(c1 == '+' || c1 == '-') {
         return_scan(c1, mask_arithmetic_ops | mask_unary_ops | mask_binary_ops, precedence_additive, 1);
      } else if(c1 == '*' || c1 == '/' || c1 == '%') {
         return_scan(c1, mask_arithmetic_ops | mask_binary_ops, precedence_multiplicative, 1);
      } else if(c1 == '&') {
         return_scan(c1, mask_arithmetic_ops | mask_binary_ops, precedence_bitwise_and, 1);
      } else if(c1 == '|') {
         return_scan(c1, mask_arithmetic_ops | mask_binary_ops, precedence_bitwise_or, 1);
      } else if(c1 == '^') {
         return_scan(c1, mask_arithmetic_ops | mask_binary_ops, precedence_bitwise_xor, 1);
      } else if(c1 == '<' || c1 == '>') {
         return_scan(c1, mask_comparison_ops | mask_binary_ops, precedence_relational, 1);
      } else if(c1 == '!') {
         return_scan(c1, mask_logical_ops | mask_unary_ops, precedence_none, 1);
      }
   }
   //[1] ~
   if(c1 == '~') return_scan(c1, mask_unary_ops, precedence_none, 1);
   return 0;
_make_punctuator_token:
   state->code = code;
   make_aggregated_token(state, begin, aggregated_id, nullptr);
   return 1;
   #undef return_scan
}

inline_spec int scan_template_characters(scan_state_t* const state)
{
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   int needs_compilation = 0;
   while(state->code < end) {
      switch(*state->code) {
         case '\r': needs_compilation = 1; break;
         case '`': {
            void* compiled_string = nullptr;
            if(needs_compilation) {
               compiled_string = compile_string(state, 1, begin, state->code);
               if(compiled_string == nullptr) return 0;
            }
            make_token(state, begin, tkn_template_string, mask_none, precedence_none, compiled_string);
            make_char_token(state, '`');
            --state->template_level;
            state->in_template_expression = (state->template_level > 0);
            if_debug(
               print_string("template-chars: ");
               print_token(begin, state->code-1 - begin);
               print_string("template: `\n");
            );
            return 1;
         }
         case '$': {
            if(state->code + 1 == end) return 0;
            if(*(state->code + 1) == '{') {
               void* compiled_string = nullptr;
               if(needs_compilation) {
                  compiled_string = compile_string(state, 1, begin, state->code);
                  if(compiled_string == nullptr) return 0;
               }
               make_token(state, begin, tkn_template_string, mask_none, precedence_none, compiled_string);
               make_char_token(state, '$');
               make_char_token(state, '{');
               ++state->parenthesis_level;
               state->in_template_expression = 1;
               if_debug(
                  print_string("template-chars: ");
                  print_token(begin, state->code-2 - begin);
                  print_string("template: $\n");
                  print_string("template: {\n");
               );
               return 1;
            }
            break;
         }
         case '\\': {
            needs_compilation = 1;
            if(*++state->code == '\r') {
               if(*(state->code + 1) == '\n') ++state->code;
            }
            break;
         }
      }
      ++state->code;
   }
   return 0;
}

inline_spec int scan_template_literal(scan_state_t* const state)
{
   // the declartion below is purely for debugging
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   if(*state->code == '`'){
      if(state->template_level == 0) {
         state->template_parenthesis_offset = state->parenthesis_level;
         ++state->template_level;
      } else if(state->in_template_expression){
         ++state->template_level;
      } else {
         --state->template_level;
      }
      make_char_token(state, '`');
      if(state->template_level == 0) {
         state->token_flags = token_flag_none;
      }
      if_verbose( print_string("template: `\n"); );
   } else {
      make_char_token(state, '}');
      --state->parenthesis_level;
      if_verbose( print_string("template: }\n"); );
   }
   while(state->template_level > 0 && state->code < end) {
      state->token_flags = state->current_token_flags;
      if(!scan_template_characters(state)) return 0;
      if(state->in_template_expression) break;
   }
   return 1;
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

inline_spec uint32_t is_reserved(scan_state_t const* const state, char_t const* string, char_t const first_char, int const length)
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
   #define _rwid(word) combine(rw_##word, rwg_##word, rwp_##word, state->token_flags)
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

inline_spec int scan_identifier(scan_state_t* const state)
{
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   while(++code < end) {
      char_t c = *code;
      char_t cl = c | 0x20;
      int is_valid =
         (cl >= 'a' && cl <= 'z') ||
         (c >= '0' && c <= '9') ||
         c == '$' || c == '_'
      ;
      if(!is_valid) break;
   }
   state->code = code;
   uint32_t reserved_word_id = is_reserved(state, begin, *begin, code - begin);
   if(reserved_word_id == 0) {
      make_token(state, begin, tkn_identifier, mask_identifier, precedence_none, nullptr);
      if_verbose(print_string("identifier: "));
   } else {
      make_aggregated_token(state, begin, reserved_word_id, nullptr);
      if_verbose(print_string("reserved_word: "));
      state->in_regexp_context = 1;
   }
   return 1;
}

#if defined(verbose)
   #define debug_wrap(_token_name, _token_type, _code) { \
      char_t const* begin = state->code; \
      start_clock(); \
      _code \
      note_elapsed_time(_token_type, counts1, timings1, characters1); \
      print_string(_token_name ": "); \
      print_token(begin, state->code - begin); \
   }
#else
   #define debug_wrap(_token_name, _token_type, _code) _code
#endif

wasm_export scan_result_t tokenize(char_t const* const code_begin, char_t const* const code_end, memory_state_t* const memory_state, uint32_t params)
{
   if_verbose( begin_group("tokenization"); )
   start_clock();
   // additional eot token and 2 more dummy tokens for algorithmic convenience
   size_t predicted_tokens = ((code_end - code_begin) / 1) + 3 + 128;
   token_t* tokens = (token_t*) malloc(predicted_tokens * sizeof(token_t));
   scan_state_t _state = {
      .code_begin = code_begin,
      .code_end = code_end,
      .code = code_begin,
      .token_begin = tokens,
      .token_end = tokens + predicted_tokens,
      .token = tokens,
      .token_flags = token_flag_none,
      .current_token_flags = token_flag_none,
      .in_template_expression = 0,
      .in_regexp_context = 1,
      .template_level = 0,
      .parenthesis_level = 0,
      .template_parenthesis_offset = 0,
      .params = params,
      .memory = memory_state
   };
   int errored = 0, was_comment = 0, is_comment = 0;
   scan_state_t* const state = &_state;
   while(state->code < code_end) {
      is_comment = 0;
      state->current_token_flags = token_flag_none;
      char_t current = *(state->code);
      char_t next = (state->code + 1 < state->code_end ? *(state->code + 1) : 0);
      char_t lower = current | 0x20;
      //printf("%d %d\n", state->template_level, state->parenthesis_level);
      if(current == '`' || (state->template_level != 0 && current == '}' && state->template_level + state->template_parenthesis_offset == state->parenthesis_level)) {
         if(!scan_template_literal(state)) { errored = 1; break; }
      } else if((lower >= 'a' && lower <= 'z') || current == '$' || current == '_') {
         debug_wrap("", identifier,
            state->in_regexp_context = 0;
            if(!scan_identifier(state)) { errored = 1; break; }
         );
      } else if(current == ' ' || current == '\t') {
         // [TODO] 0x09, 0x0C, 0xA0, \uFEFF, Unicode Space_Separator
         debug_wrap("space", whitespace,
            while(++state->code < code_end && (*state->code == ' ' || *state->code == '\t'));
            //make_token(state, tkn_whitespace, mask_none, precedence_none, nullptr);
            state->current_token_flags = state->token_flags;
            is_comment = was_comment;
         );
      } else if(current == '\r' || current == '\n') {
         debug_wrap("newline", terminator,
            while(++state->code < code_end && (*state->code == '\r' || *state->code == '\n'));
            //make_token(state, tkn_terminator, mask_none, precedence_none, nullptr);
            state->current_token_flags |= token_flag_newline;
         );
      } else if((current >= '0' && current <= '9') ||
         (current == '.' && (next >= '0' && next <= '9'))
      ){
         debug_wrap("number", numeric_literal,
            state->in_regexp_context = 0;
            if(!scan_numeric_literal(state)) { errored = 1; break; }
         )
      } else if(current == '\'' || current == '"') {
         debug_wrap("string", string_literal,
            state->in_regexp_context = 0;
            //if(!scan_string_literal(state)) { errored = 1; break; }
            if(!compile_string_literal(state)) { errored = 1; break; }
         );
      } else if(current == '/') {
         if(next == '/' || next == '*') {
            debug_wrap("comment", comment,
               is_comment = 1;
               if(was_comment) {
                  state->current_token_flags |= state->token_flags & token_flag_newline;
               }
               if(!scan_comment(state)) { errored = 1; break; }
            );
         } else if(state->in_regexp_context) {
            debug_wrap("regexp", regexp_literal,
               if(!scan_regexp_literal(state)) { errored = 1; break; }
            );
         } else {
            debug_wrap("punctuator", punctuator,
               state->in_regexp_context = 1;
               if(!scan_punctuator(state)) { errored = 1; break; }
            );
         }
      } else {
         debug_wrap("punctuator", punctuator,
            state->in_regexp_context = (current == ')' || current == ']' ? 0 : 1);
            if(!scan_punctuator(state)) { errored = 1; break; }
         );
      }
      state->token_flags = state->current_token_flags;
      was_comment = is_comment;
   }
   if(errored) {
      //printf("\nparse failed at %ld\n", string - begin);
      return (scan_result_t){
         .tokens = state->token_begin,
         .token_count = state->token - state->token_begin,
         .return_value = 0
      };
   } else {
      make_token(state, state->code, tkn_eot, 0, precedence_none, nullptr);
      if_verbose( end_group(); )
      print_elapsed_time("tokenization");
      return (scan_result_t){
         .tokens = state->token_begin,
         .token_count = state->token - state->token_begin,
         .return_value = 1
      };
   }
}

#endif //_SCANNER_BASE_H_
