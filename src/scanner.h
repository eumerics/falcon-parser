#ifndef _SCANNER_BASE_H_
#define _SCANNER_BASE_H_

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"
#include "constants.h"
#include "nodes.h"
#include "messages.h"
#include "unicode/id_start.h"
#include "unicode/id_continue.h"

#ifdef bool
   #pragma push_macro("bool")
   #pragma push_macro("true")
   #pragma push_macro("false")
   #define __POP_BOOL__
   #undef bool
   #undef true
   #undef false
#endif

#define in_strict_mode() (params & param_flag_strict_mode)
#define to_loose_mode() (params = (params & ~param_flag_strict_mode) | param_flag_loose_mode)
#define to_strict_mode() (params = (params & ~param_flag_loose_mode) | param_flag_strict_mode)
#define allow_annex() ((params & param_flag_annex) && !in_strict_mode())

#if defined(MEMOPT)
   #define token_diff(token1, token2) (((token1) - (token2) + token_capacity) % token_capacity)
   #define _offset_from_current_scan_token(offset) (state->token_begin + ((state->token_count + offset) % token_capacity))
   #define previous_scan_token() _offset_from_current_scan_token(-1)
   // discard const qualifier for the following two definitions in favor of efficiency
   #define increment_current_scan_token(token) (state->scan_token = (token_t*) _offset_from_current_scan_token(1), ++state->token_count)
   #define decrement_current_scan_token(token) (state->scan_token = (token_t*) _offset_from_current_scan_token(-1), --state->token_count)
   #define unwind_for_use_strict(token) ( \
      state->tokenization_status = status_flag_incomplete, \
      state->code = token->begin, \
      state->token_count -= (state->scan_token - token + token_capacity) % token_capacity, \
      state->scan_token = (token_t*) token, \
      state->line_number = token->location.begin.line, \
      state->line_begin = token->begin - token->location.begin.column, \
      scan_next_token(state, params) \
   )
#else
   #define token_diff(token1, token2) ((token1) - (token2))
   #define previous_scan_token() (state->scan_token - 1)
   #define increment_current_scan_token() (++state->scan_token, ++state->token_count)
   #define decrement_current_scan_token() (--state->scan_token, --state->token_count)
   #define unwind_for_use_strict(token)
#endif

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
uint32_t compile_unicode_escape_sequence(parse_state_t* state, int for_identifier)
{
   char_t const* const begin = state->code;
   int is_code_point = 0, min_hex_chars = 0, max_hex_chars = 0;
   if(*++state->code != 'u') return_scan_error(expecting_unicode_sequence, begin, 0);
   if(*(state->code + 1) == '{') {
      is_code_point = 1, ++state->code;
      min_hex_chars = 1, max_hex_chars = (uint32_t)(-1);
   } else {
      min_hex_chars = max_hex_chars = 4;
   }
   uint32_t value = 0;
   for(uint32_t i = 0; i < max_hex_chars; ++i) {
      char_t c = *++state->code, cl = c | 0x20;
      //print_number(c);
      value <<= 4;
      if(c >= '0' && c <= '9'){ value |= (c - '0'); continue; }
      if(cl >= 'a' && cl <= 'f'){ value |= 10 + (cl - 'a'); continue; }
      if(i < min_hex_chars) { return_scan_error(not_enough_hexdigits, state->code, 0); }
      else { --state->code; value >>= 4; break; }
   }
   if(is_code_point && *++state->code != '}') {
      return_scan_error(missing_unicode_closing, state->code, 0);
   }
   if(for_identifier && ((value & 0xf800) == 0xd800)) {
      //state->code = begin;
      return_scan_error(surrogate_in_identifier, begin, 0);
   }
   ++state->code;
   return value;
}
uint32_t compile_unicode_code_point(parse_state_t* state, int for_identifier)
{
   char_t const* const begin = state->code;
   uint32_t value;
   if(*state->code == '\\') {
      value = compile_unicode_escape_sequence(state, for_identifier);
      if(state->parse_error) return 0;
   } else {
      value = *state->code++;
   }
   //print_number(value);
   /*
   if(for_identifier && ((value & 0xf800) == 0xd800)) {
      state->code = begin;
      return_error(surrogate_in_identifier, 0);
   }
   */
   if((value & 0xfc00) == 0xdc00) {
      state->code = begin;
      return_scan_error(missing_leading_surrogate, begin, 0);
   }
   if((value & 0xfc00) == 0xd800) {
      char_t const* const begin = state->code;
      uint32_t trailing_value;
      if(*state->code == '\\') {
         trailing_value = compile_unicode_escape_sequence(state, for_identifier);
         if(state->parse_error) return 0;
      } else if(state->code < state->code_end){
         trailing_value = *state->code++;
      } else {
         return_scan_error(missing_trailing_surrogate, begin, 0);
      }
      if((trailing_value & 0xdc00) != 0xdc00) {
         state->code = begin;
         return_scan_error(missing_trailing_surrogate, begin, 0);
      }
      value = (value & 0x3ff) << 10 | (trailing_value & 0x3ff);
      value += 0x10000;
   }
   return value;
}
inline_spec int is_ascii_identifier_start(char_t c)
{
   //print_string("id-start"); print_number(c);
   char_t l = c | 0x20; // lower
   return (l >= 'a' && l <= 'z') || c == '$' || c == '_';
}
inline_spec int scan_ascii_identifier_start(parse_state_t* state, char_t c)
{
   if(is_ascii_identifier_start(c)) { ++state->code; return 1; }
   return 0;
}
inline_spec int scan_unicode_identifier_start_helper(parse_state_t* state, char_t c)
{
   //print_string("id-start-helper"); print_number(c);
   char_t const* const begin = state->code;
   if(!(c == '\\' || (c & 0xffffff80))) return 0;
   uint32_t value = compile_unicode_code_point(state, 1);
   //print_number(value);
   if(state->parse_error) return 0;
   if(!is_unicode_id_start(value)) {
      state->code = begin; return 0;
   }
   return 1;
}
inline_spec int is_unicode_identifier_start_helper(parse_state_t* state, char_t c)
{
   char_t const* const begin = state->code;
   int return_value = scan_unicode_identifier_start_helper(state, c);
   state->code = begin;
   return return_value;
}
inline_spec int is_ascii_identifier_continue(char_t c)
{
   //print_string("id-continue"); print_number(c);
   char_t l = c | 0x20; // lower
   return (l >= 'a' && l <= 'z') || c == '$' || c == '_' || (c >= '0' && c <= '9');
}
inline_spec int scan_ascii_identifier_continue(parse_state_t* state, char_t c)
{
   if(is_ascii_identifier_continue(c)) { ++state->code; return 1; }
   return 0;
}
inline_spec int scan_unicode_identifier_continue_helper(parse_state_t* state, char_t c)
{
   //print_string("id-continue-helper"); print_number(c);
   char_t const* const begin = state->code;
   if(!(c == '\\' || (c & 0xffffff80))) return 0;
   uint32_t value = compile_unicode_code_point(state, 1);
   if(state->parse_error) return 0;
   //print_number(value);
   // ZWNJ: 0x200c, ZWJ: 0x200d
   if(value == 0x200c || value == 0x200d || is_unicode_id_continue(value)) {
      return 1;
   } else {
      state->code = begin;
      return 0;
   }
}
inline_spec int is_unicode_identifier_continue_helper(parse_state_t* state, char_t c)
{
   char_t const* const begin = state->code;
   int return_value = scan_unicode_identifier_continue_helper(state, c);
   state->code = begin;
   return return_value;
}
#define scan_identifier_start(c) ( \
   scan_ascii_identifier_start(state, c) || \
   scan_unicode_identifier_start_helper(state, c) \
)
#define scan_identifier_continue(c) ( \
   scan_ascii_identifier_continue(state, c) || \
   scan_unicode_identifier_continue_helper(state, c) \
)
#define is_identifier_start(c) ( \
   is_ascii_identifier_start(c) || \
   is_unicode_identifier_start_helper(state, c) \
)
inline_spec int is_common_line_terminator(char_t c)
{
   return (c == '\r' || c == '\n');
}
inline_spec int is_line_terminator(char_t c)
{
   #if defined(UTF16)
      return (c == '\r' || c == '\n' || c == 0x2028 || c == 0x2029);
   #else
      return (c == '\r' || c == '\n');
   #endif
}
inline_spec int consume_terminator_sequence(parse_state_t* state, char_t const** code, params_t flags)
{
   char_t const c = **code;
   if(c == '\r') { ++*code; if(*code < state->code_end && **code == '\n') ++*code; }
   else if(c == '\n') { ++*code; }
#if defined(UTF16)
   else if(c == 0x2028 || c == 0x2029) {
      ++*code; if(flags & param_flag_inconsistent_lines) return 1;
   }
#endif
   else return 0;
   ++state->line_number;
   state->line_begin = *code;
   return 1;
}

inline_spec void make_char_token(parse_state_t* state, uint8_t const id)
{
   //size_t offset = state->code - state->code_begin;
   position_t const begin_position = make_position(state);
   position_t const end_position = {
      .line = state->line_number, .column = state->code - state->line_begin + 1
   };
   *(state->scan_token) = (token_t){
      .begin = state->code, .end = state->code + 1,
      .id = id, .group = mask_none, .flags = token_flag_none,
      .detail = nullptr,
      .location = {.begin = begin_position, .end = end_position}
   };
   increment_current_scan_token();
   ++state->code;
}

inline_spec void make_token(
   parse_state_t* const state, char_t const* begin,
   position_t const begin_position,
   uint8_t const id, uint16_t const group,
   uint8_t const contextual, void* detail
){
   *(state->scan_token) = (token_t){
      .begin = begin,
      .end = state->code,
      .id = id, .group = group, .flags = (contextual << 4 | state->token_flags),
      .detail = detail,
      .location = {.begin = begin_position, .end = make_position(state)}
   };
   increment_current_scan_token();
}

inline_spec void make_aggregated_token(
   parse_state_t* const state, char_t const* begin,
   position_t const begin_position,
   uint32_t const aggregated_id, void* detail
){
   *(state->scan_token) = (token_t){
      .begin = begin,
      .end = state->code,
      .aggregated_id = aggregated_id,
      .detail = detail,
      .location = {.begin = begin_position, .end = make_position(state)}
   };
   increment_current_scan_token();
}

// [LIMITATION] string length is 1-bit shorter than what the platform can
// support i.e, 1 << (size(ptrdiff_t) * 8 - 1), for nearly all cases this
// should not be a problem at all
ptrdiff_t escaped_string_flag = (ptrdiff_t)(1) << (sizeof(ptrdiff_t)*8 - 1);
inline_spec ptrdiff_t prescan_string_literal(
   parse_state_t* state, char_t const* code, char_t const* const end, params_t params
){
   char_t const* const begin = code;
   char_t const quote = *code;
   ptrdiff_t string_type = 0;
   while(++code < end) {
      char_t c = *code;
      switch(c) {
         case '\r': case '\n': return_scan_error(newline_in_string_literal, code, 0);
#if defined(UTF16)
         case 0x2028: case 0x2029:
            if(!(params & param_flag_inconsistent_lines)) {
               ++state->line_number;
               state->line_begin = code + 1;
            }
            break;
#endif
         case '\\': {
            string_type = escaped_string_flag;
            ++code; if(consume_terminator_sequence(state, &code, params)) --code;
            break;
         }
         default: if(c == quote) return (++code - begin) | string_type;
      }
   }
   return 0;
}
compiled_string_t* compile_string(
   parse_state_t* const state, int for_template,
   char_t const* const begin, char_t const* const end, params_t params
)
{
   #define return_not_escape_string(error_type) { \
      if(for_template) { \
         compiled_string_t* compiled_string = parser_malloc(mm_compiled_strings, sizeof(compiled_string_t)); \
         *compiled_string = (compiled_string_t){ \
            .begin = nullptr, .end = nullptr, \
            .compile_flags = compile_flag_not_escape, \
            .offending_position = make_given_position(state, not_escape_code_begin), \
            .offending_error = &error_##error_type \
         }; \
         return compiled_string; \
      } else { \
         return_scan_error(error_type, not_escape_code_begin, nullptr); \
      } \
   }
   char_t const* code = begin - 1;
   char_t* compiled = parser_malloc(mm_compiled_strings, (end - begin) * sizeof(char_t));
   char_t const* const compiled_begin = compiled;
   position_t offending_position;
   parse_error_t const* offending_error;
   uint8_t compile_flags = 0;
   while(++code < end) {
      char_t c = *code;
      char_t const* not_escape_code_begin = code;
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
               for(uint32_t i = 0; i < max_hex_chars; ++i) {
                  char_t c = *++code, cl = c | 0x20;
                  hex <<= 4;
                  if(c >= '0' && c <= '9'){ hex |= (c - '0'); continue; }
                  if(cl >= 'a' && cl <= 'f'){ hex |= 10 + (cl - 'a'); continue; }
                  if(i < min_hex_chars) { return_not_escape_string(invalid_escape_sequence); }
                  else { --code; hex >>= 4; break; }
               }
               if(is_code_point && (*++code != '}')) { return_not_escape_string(missing_unicode_closing); }
            #if defined(UTF16)
               if(hex & 0xffff0000) {
                  if(hex > 0x10ffff) { return_not_escape_string(unicode_range); }
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
               if(c == '0' && !is_decimal(*(code + 1))){
                  *compiled++ = 0;
               } else if(!is_decimal(c)){
                  *compiled++ = c;
               } else if(!for_template && allow_annex()) {
                  if(compile_flags == 0) {
                     compile_flags = compile_flag_octal;
                     offending_position = make_given_position(state, code - 1);
                     offending_error = &error_octal_in_strict;
                  }
                  // legacy octal escape sequence
                  if(c >= '8') { *compiled++ = c; break; }
                  char_t value = c - '0';
                  char_t o = *(code + 1);
                  if(!is_octal(o)) { *compiled++ = value; break; }
                  value = (value << 3) | (o - '0');
                  ++code;
                  if(c >= '4') { *compiled++ = value; break; }
                  o = *(code + 1);
                  if(!(o >= '0' && o <= '7')) { *compiled++ = value; break; }
                  value = (value << 3) | (o - '0');
                  *compiled++ = value;
                  ++code;
               } else {
                  return_not_escape_string(invalid_escape_sequence);
               }
            }
         }
      }
   }
   compiled_string_t* compiled_string =
      parser_malloc(mm_compiled_strings, sizeof(compiled_string_t));
   *compiled_string = (compiled_string_t){
      .begin = compiled_begin, .end = compiled,
      .compile_flags = compile_flags,
      .offending_position = offending_position,
      .offending_error = offending_error
   };
   return compiled_string;
}
inline_spec int compile_string_literal(parse_state_t* const state, params_t params)
{
   position_t const begin_position = make_position(state);
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   ptrdiff_t length_and_flag = prescan_string_literal(state, begin, end, params);
   if(length_and_flag == 0) return 0;
   void* compiled_string = nullptr;
   size_t length = (length_and_flag & ~escaped_string_flag);
   if(length_and_flag & escaped_string_flag) {
      compiled_string = compile_string(state, 0, begin + 1, begin + length - 1, params);
      if(compiled_string == nullptr) return 0;
   }
   state->code = begin + length;
   make_token(state, begin, begin_position, tkn_string_literal, mask_literal, precedence_none, compiled_string);
   return 1;
}
inline_spec int scan_string_literal(parse_state_t* const state, params_t params)
{
   position_t const begin_position = make_position(state);
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
         } else if(allow_annex() && c >= '0' && c <= '9'){
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
   make_token(state, begin, begin_position, tkn_string_literal, mask_literal, precedence_none, nullptr);
   return 1;
}

inline_spec double compile_numeric_literal(
   char_t const* number_begin, int base,
   int integer_digits, int fraction_digits, int exponent
){
   //[BUG][TODO] cases that require big number arithmetic
   int digits = 0, number = 0;
   char_t const* code = number_begin;
   while(integer_digits > 0) {
      if(digits != 0 || *code != '0') {
         char_t c = *code;
         number *= base;
         if(base == 16) {
            c |= 0x20;
            number += c - (c >= 'a' ? 'a' - 10 : '0');
         } else {
            number += c - '0';
         }
         ++digits;
      }
      ++code; --integer_digits;
   }
   if(base != 10) return number;
   ++code; // decimal point
   while(fraction_digits > 0) {
      if(digits != 0 || *code != '0') {
         number *= 10; number += *code - '0'; ++digits;
      }
      ++code; --exponent; --fraction_digits;
   }
   if(exponent == 0) {
      return number;
   } else {
      int positive_exponent = (exponent < 0 ? -exponent : exponent);
      double multiplier = 1; while(--positive_exponent >= 0) multiplier *= 10;
      if(exponent < 0) {
         //print_number(number); print_double(multiplier);
         return number / multiplier;
      } else {
         //print_number(number); print_double(multiplier);
         return number * multiplier;
      }
   }
}

inline_spec int scan_numeric_literal(parse_state_t* const state, params_t params)
{
   //[TODO] spacing character _
   position_t const begin_position = make_position(state);
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t c = *code;
   int numeric_annex = 0;
   int base = 10, integer_digits = 0, fraction_digits = 0, exponent = 0;
   char_t const* number_begin = code;
   uint8_t integer_flag = compile_flag_integer;
   // parse the integer part
   if(c == '0') {
      if(++code == end) goto _make_numeric_token;
      char_t c = *code;
      //[TODO] octal compilation
      if(c >= '0' && c <= '9') {
         if(!allow_annex()) {
            state->error_position = begin_position;
            return_error(annex_numeral, 0);
         }
         numeric_annex = 1;
         base = (c & 0x08 ? 10 : 8); // '8' = 0x38, '9' = 0x39
         while(++code < end){
            char_t c = *code;
            if(c < '0' || c > '9') break;
            if(c & 0x08) base = 10;
         };
      } else {
         char_t lower = *code | 0x20;
         char_t const* digit_begin = code + 1;
         if(lower == 'x') { // hexadecimal number
            number_begin = code + 1;
            base = 16; while(++code < end && is_hex(*code));
         } else if(lower == 'b') {
            number_begin = code + 1;
            base = 2; while(++code < end && is_binary(*code));
         } else if(lower == 'o') {
            number_begin = code + 1;
            base = 8; while(++code < end && is_octal(*code));
         }
         if(code == digit_begin) return 0;
      }
   } else if(c >= '1' && c <= '9') {
      while(++code < end && is_decimal(*code));
   }
   integer_digits = code - number_begin;
   if(code == end) goto _make_numeric_token;
   if(base != 10) goto _verify_and_make_numeric_token;
   // parse the decimal part
   if(*code == '.') {
      integer_flag = 0;
      char_t const* fraction_begin = code + 1;
      while(++code < end && is_decimal(*code));
      fraction_digits = code - fraction_begin;
      if(code - begin == 1) return 0; // . must follow atleast a digit
      if(code == end) goto _make_numeric_token;
   }
   // parse the exponent
   if(((*code | 0x20) == 'e') && (code - begin > 0)) {
      if(code + 1 == end) return 0;
      char_t c = *(code + 1);
      int sign = 1;
      if(c == '+') { ++code; } else if(c == '-') { sign = -1; ++code; }
      char_t const* const exponent_begin = code + 1;
      while(++code < end && is_decimal(*code)) {
         exponent *= 10; exponent += *code - '0';
      }
      exponent *= sign;
      if(code == exponent_begin) return 0;
      if(code == end) goto _make_numeric_token;
   }
_verify_and_make_numeric_token:
   // https://tc39.es/ecma262/#sec-literals-numeric-literals
   // The SourceCharacter immediately following a NumericLiteral
   // must not be an IdentifierStart or DecimalDigit
   if(is_identifier_start(*code) || is_decimal(*code)) return 0;
_make_numeric_token:
   state->code = code;
   //make_token(state, begin, begin_position, tkn_numeric_literal, mask_literal, precedence_none, nullptr);
   ///*
   compiled_number_t* cn = parser_malloc(mm_compiled_numbers, sizeof(compiled_number_t));
   *cn = (compiled_number_t){
      //.offending_position = {},
      .value = compile_numeric_literal(
         number_begin, base, integer_digits, fraction_digits, exponent
      ),
      .compile_flags = compile_flag_numeric_annex | integer_flag
   };
   make_token(state, begin, begin_position, tkn_numeric_literal, mask_literal, precedence_none, cn);
   //print_number(base); print_number(integer_digits);
   //print_number(fraction_digits); print_number(exponent);
   //print_double(cn->value); print_string("\n");
   //*/
   return 1;
}

int unterminated_regexp_error(parse_state_t* const state, char_t const* code)
{
   return_scan_error(unterminated_regexp, code, 0);
}
int terminated_regexp_error(parse_state_t* const state, char_t const* code)
{
   return_scan_error(terminated_regexp, code, 0);
}
//[LIMITATION]: maximum number of allowed flags 1<<5 = 32.
inline_spec int scan_regexp_literal(parse_state_t* const state, params_t params)
{
   position_t const begin_position = make_position(state);
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   while(1) {
      if(++code == end) return unterminated_regexp_error(state, begin);
      char_t current = *code;
      if(current == '/') { ++code; break; }
      if(is_line_terminator(current)) return terminated_regexp_error(state, code);
      // take care of scenarios where '/' fails to serve as a closing tag
      if(current == '\\') {
         // for scanning it is enough to eat next character
         // as long as it is not a line terminator
         if(++code == end) return unterminated_regexp_error(state, begin);
         char_t next = *code;
         if(is_line_terminator(next)) return terminated_regexp_error(state, code);
      } else if(current == '[') {
         while(1) {
            if(++code == end) return unterminated_regexp_error(state, begin);
            current = *code;
            if(current == ']') break;
            if(is_line_terminator(current)) return terminated_regexp_error(state, code);
            if(current == '\\') {
               if(++code == end) return unterminated_regexp_error(state, begin);
               char_t next = *code;
               if(is_line_terminator(next)) return terminated_regexp_error(state, code);
            }
         }
      }
   }
   // parse flags
   char_t const* flags_begin = code;
   if(code < end) {
      uint8_t has_duplicate = 0, end_of_flags = 0;
      uint8_t has_g = 0, has_i = 0, has_m = 0, has_s = 0, has_u = 0, has_y = 0;
      do {
         char_t c = *code;
         switch(c) {
            case 'g': if(has_g) has_duplicate = 1; else has_g = 1; break;
            case 'i': if(has_i) has_duplicate = 1; else has_i = 1; break;
            case 'm': if(has_m) has_duplicate = 1; else has_m = 1; break;
            case 's': if(has_s) has_duplicate = 1; else has_s = 1; break;
            case 'u': if(has_u) has_duplicate = 1; else has_u = 1; break;
            case 'y': if(has_y) has_duplicate = 1; else has_y = 1; break;
            //default: set_error(invalid_regexp_flag); end_of_flags = 1; break; //pre-empted error
            default: {
               if(c >= 'a' && c <= 'z') { //[BUG][TODO] incomplete test
                  set_scan_error(invalid_regexp_flag, code);
               }
               end_of_flags = 1; break;
            }
         }
         if(has_duplicate) { return_scan_error(duplicate_regexp_flag, code, 0); }
         if(end_of_flags) break;
      } while(++code < end);
   }
   state->code = code;
   make_token(state, begin, begin_position, tkn_regexp_literal, mask_none, code - flags_begin, nullptr);
   return 1;
}

inline_spec int get_comment_begin_chars(parse_state_t* const state, params_t params)
{
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t const c = *code;
   if(c == '/') {
      char_t const n = (++code < end ? *code : 0);
      return ((n == '/' || n == '*') ? 2 : 0);
   }
   if(!(params & param_flag_annex) || (params & param_flag_module)) return 0;
   if(c == '<') {
      if(code + 4 > end) return 0;
      if(*++code == '!' && *++code == '-' && *++code == '-') return 4;
      return 0;
   }
   if(!(state->token_flags & (token_flag_begin | token_flag_newline))) return 0;
   if(c == '-') {
      if(code + 3 > end) return 0;
      if(*++code == '-' && *++code == '>') return 3;
      return 0;
   }
   return 0;
}
inline_spec int scan_comment(parse_state_t* const state, int comment_chars, params_t params)
{
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t type = *(++code);
   if(type == '/' || comment_chars > 2) {
      code += comment_chars - 2;
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
         } else if(consume_terminator_sequence(state, &code, 0)) {
            state->current_token_flags |= token_flag_newline;
            --code;
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
   ((uint32_t)(token_flags)) | (((uint32_t)(precedence)) << 4) | (((uint32_t)(id)) << 8) | (((uint32_t)(group)) << 16)
inline_spec int scan_punctuator(parse_state_t* const state, params_t params)
{
   #define return_scan(id, group, precedence, length) { \
      code += length; \
      aggregated_id = combine(id, group, precedence, state->token_flags); \
      goto _make_punctuator_token; \
   }
   uint32_t aggregated_id;
   position_t const begin_position = make_position(state);
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   char_t const* code = state->code;
   char_t c1 = *code;
   char_t c2 = (code + 1 < end ? *(code + 1) : 0);
   state->in_regexp_context = 1;
   //[14] { } ( ) [ ] ; , : . === == => =
   if(c1 == '(') {
      ++state->parenthesis_level;
      return_scan(c1, mask_parentheses, precedence_none, 1);
   }
   if(c1 == ')') {
      if(state->parenthesis_level == state->expect_statement_after_level) {
         state->in_regexp_context = 1;
         state->expect_statement_after_level = 0;
      } else {
         state->in_regexp_context = 0;
      }
      --state->parenthesis_level;
      return_scan(c1, mask_parentheses, precedence_none, 1);
   }
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
      ++state->curly_parenthesis_level;
      return_scan(c1, mask_parentheses | mask_binding_pattern, precedence_none, 1);
   }
   if(c1 == '}'){
      --state->curly_parenthesis_level;
      //state->in_regexp_context = (state->parenthesis_level == 0);
      return_scan(c1, mask_parentheses, precedence_none, 1);
   }
   if(c1 == '[') return_scan(c1, mask_parentheses | mask_binding_pattern, precedence_none, 1);
   if(c1 == ']') {
      state->in_regexp_context = 0;
      return_scan(c1, mask_parentheses, precedence_none, 1);
   }
#ifndef EXTENSIONS
   if(c1 == ':') return_scan(c1, mask_none, precedence_none, 1);
#else
   if(c1 == ':') {
      if(c2 == ':') {
         return_scan(pnct_namespace, mask_none, precedence_none, 2);
      } else {
         return_scan(c1, mask_none, precedence_none, 1);
      }
   }
#endif
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
            case '+': {
               state->in_regexp_context = 0;
               return_scan(pnct_increment, mask_update_ops, precedence_none, 2);
            }
            case '-': {
               state->in_regexp_context = 0;
               return_scan(pnct_decrement, mask_update_ops, precedence_none, 2);
            }
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
#ifdef EXTENSIONS
   if(c1 == '#') return_scan(c1, mask_none, precedence_none, 1);
#endif
   return 0;
_make_punctuator_token:
   state->code = code;
   make_aggregated_token(state, begin, begin_position, aggregated_id, nullptr);
   return 1;
   #undef return_scan
}

inline_spec int scan_template_characters(parse_state_t* const state, params_t params)
{
   position_t const begin_position = make_position(state);
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   int needs_compilation = 0;
   while(state->code < end) {
      switch(*state->code) {
         // \r, \r\n, \n are normalized to \n and hence require compiling
         case '`': {
            void* compiled_string = nullptr;
            if(needs_compilation) {
               compiled_string = compile_string(state, 1, begin, state->code, params);
               if(compiled_string == nullptr) return 0;
            }
            make_token(state, begin, begin_position, tkn_template_string, mask_none, precedence_none, compiled_string);
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
                  compiled_string = compile_string(state, 1, begin, state->code, params);
                  if(compiled_string == nullptr) return 0;
               }
               make_token(state, begin, begin_position, tkn_template_string, mask_none, precedence_none, compiled_string);
               make_char_token(state, '$');
               make_char_token(state, '{');
               ++state->curly_parenthesis_level;
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
         case '\\': ++state->code; // fallthrough
         case '\r': needs_compilation = 1; // fallthrough
         default: {
            if(consume_terminator_sequence(state, &state->code, params)) {
               --state->code;
            }
            break;
         }
      }
      ++state->code;
   }
   return 0;
}

inline_spec int scan_template_literal(parse_state_t* const state, params_t params)
{
   // the declartion below is purely for debugging
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   if(*state->code == '`'){
      if(state->template_level == 0) {
         state->template_parenthesis_offset = state->curly_parenthesis_level;
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
      --state->curly_parenthesis_level;
      if_verbose( print_string("template: }\n"); );
   }
   /*
   while(state->template_level > 0 && state->code < end) {
      state->token_flags = state->current_token_flags;
      if(!scan_template_characters(state, params)) return 0;
      if(state->in_template_expression) break;
   }
   */
   if(state->template_level > 0 && state->code < end) {
      state->token_flags = state->current_token_flags;
      if(!scan_template_characters(state, params)) return 0;
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

inline_spec uint32_t is_reserved(parse_state_t* const state, char_t const* string, char_t const first_char, int const length, params_t params)
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
   #define return_if(string) if(!_strncmp(string)) return _rwid(string);
   #define note_and_return_if(string) { \
      if(!_strncmp(string)) { \
         state->expect_statement_after_level = state->parenthesis_level + 1; \
         return _rwid(string); \
      } \
   }
   #define note_and_return_comparison_with(string) { \
      if(!_strncmp(string)) { \
         state->expect_statement_after_level = state->parenthesis_level + 1; \
         return _rwid(string); \
      } \
      return 0; \
   }
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
            case 9: return_comparison_with(arguments);
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
            case 11: return_comparison_with(constructor);
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
            case 4: return_comparison_with_vec3(else, enum, eval);
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
            case 3: note_and_return_comparison_with(for);
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
            case 2: note_and_return_if(if); return_comparison_with(in);
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
            case 5: note_and_return_comparison_with(while);
            case 4: note_and_return_comparison_with(with);
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

inline_spec int scan_ascii_identifier(parse_state_t* const state, params_t params)
{
   position_t const begin_position = make_position(state);
   char_t const* const begin = state->code;
   char_t const* const end = state->code_end;
   while(++state->code < end && is_ascii_identifier_continue(*state->code));
   aggregate_id_t reserved_word = {
      .aggregated_id = is_reserved(state, begin, *begin, state->code - begin, params)
   };
   if(reserved_word.aggregated_id == 0) {
      make_token(state, begin, begin_position, tkn_identifier, mask_identifier, precedence_none, nullptr);
      if_verbose(print_string("identifier: "));
   } else {
      if((reserved_word.group & mask_always_a_reserved_word) &&
         (state->token_count == 0 || previous_scan_token()->id != '.')
      ){
         state->in_regexp_context = 1;
      }
      make_aggregated_token(state, begin, begin_position, reserved_word.aggregated_id, nullptr);
      if_verbose(print_string("reserved_word: "));
   }
   return 1;
}

int scan_identifier(parse_state_t* const state, params_t params)
{
   // logic for scanning a non-ascii identifier is a bit complex for two reasons
   // 1) we have to account for a possible continuation of a previously scanned
   //    ascii identifier which could be an incomplete scan of an identifier
   // 2) this function is invoked as a possible identifier scan, we have to
   //    first ascertain a identifier scan and gracefully return in order to
   //    consider other possible scans
   token_t const* const token = (state->token_count > 0 ? previous_scan_token() : nullptr);
   // if previous token is a possible continuation we roll back current token
   int can_continue = token && (token->end == state->code) && (token->group & mask_idname);
   char_t const* const begin = (can_continue ? token->begin : state->code);
   char_t const* const end = state->code_end;
   position_t const begin_position = {
      .line = state->line_number, .column = begin - state->line_begin
   };
   int has_escape_sequence = 0;
   if(begin == state->code) {
      has_escape_sequence = (*state->code == '\\');
      if(!scan_identifier_start(*state->code)) return 0;
   }
   int has_continuation = 0;
   while(state->code < end) {
      has_escape_sequence |= (*state->code == '\\');
      if(!scan_identifier_continue(*state->code)) {
         if(can_continue && !has_continuation) { return 0; }
         if(state->parse_error) return 0;
         break;
      }
      has_continuation = 1;
   }
   compiled_string_t* compiled_identifier = nullptr;
   char_t const* identifier_begin;
   ptrdiff_t identifier_length;
   if(has_escape_sequence) {
      char_t* identifier_code = parser_malloc(mm_compiled_identifiers, (state->code - begin) * sizeof(char_t));
      identifier_begin = identifier_code;
      char_t const* const saved_code = state->code;
      state->code = begin;
      while(state->code < saved_code) {
         uint32_t code_point = compile_unicode_code_point(state, 1);
         if(code_point & 0xffff0000) {
            code_point -= 0x10000;
            *(identifier_code + 1) = (0b110111 << 10) | (code_point & 0x3ff); code_point >>= 10;
            *(identifier_code + 0) = (0b110110 << 10) | (code_point & 0x3ff); code_point >>= 10;
            identifier_code += 2;
         } else {
            *identifier_code++ = code_point;
         }
      }
      identifier_length = identifier_code - identifier_begin;
      compiled_identifier = parser_malloc(mm_compiled_identifiers, sizeof(compiled_string_t));
      *compiled_identifier = (compiled_string_t) {
         .begin = identifier_begin, .end = identifier_code,
         .compile_flags = flag_none,
         .offending_position = {.line = 0, .column = 0}
      };
   } else {
      identifier_begin = begin;
      identifier_length = state->code - begin;
   }
   if(can_continue) { decrement_current_scan_token(); }
   aggregate_id_t reserved_word = {
      .aggregated_id = is_reserved(state, identifier_begin, *identifier_begin, identifier_length, params)
   };
   if(has_escape_sequence && (reserved_word.group & mask_always_a_reserved_word)) {
      return_scan_error(unicode_keyword, begin, 0);
   }
   uint8_t token_flags = (has_escape_sequence ? token_flag_escaped : flag_none);
   if(reserved_word.aggregated_id == 0) {
      make_token(state, begin, begin_position, tkn_identifier, mask_identifier, token_flags, compiled_identifier);
      if_verbose(print_string("identifier: "));
   } else {
      make_aggregated_token(state, begin, begin_position, reserved_word.aggregated_id | token_flags, compiled_identifier);
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

inline_spec int is_common_whitespace(char_t const c)
{
   return (c == ' ' || c == '\t');
}
int is_whitespace(char_t const c)
{
   uint16_t const line_tabulation = 0x000B; // <VT>
   uint16_t const form_feed = 0x000C; // <FF>
   uint16_t const no_break_space = 0x00A0; // <NBSP>
   uint16_t const zero_width_no_break_space = 0xFEFF; // <ZWNBSP>
   // Whitespace - <USP>
   uint16_t const ogham_space_mark = 0x1680; // <USP>
   // 2000..200A    ; Common # Zs  [11] EN QUAD..HAIR SPACE
   uint16_t const en_quad = 0x2000;
   uint16_t const hair_space = 0x200A;
   uint16_t const narrow_no_break_space = 0x202F; // <USP>
   uint16_t const medium_mathematics_space = 0x205F; // <USP>
   uint16_t const ideographic_space = 0x3000; // <USP>

   if(c >= en_quad && c <= hair_space) return 1;
   switch(c) {
      case ' ':
      case '\t':
      case line_tabulation:
      case form_feed:
      case no_break_space:
      case zero_width_no_break_space:
      case ogham_space_mark:
      case narrow_no_break_space:
      case medium_mathematics_space:
      case ideographic_space: return 1;
      default: return 0;
   }
}

int scan_uncommon(parse_state_t* state, params_t params)
{
   // Newline
   uint16_t const line_separator = 0x2028; // <LS>
   uint16_t const paragraph_separator = 0x2029; // <PS>

   char_t c = *state->code;
   //[REVIEW] do we need (c & 0xffffff80) instaed of (c & 0xff80)
   if(c == '\\' || (c & 0xffffff80)) {
      //if_debug(print_string("continuing identifier\n"));
      if(scan_identifier(state, params)) return 1;
      if(state->parse_error) return 0;
   }
   if(c == line_separator || c == paragraph_separator) {
      //if_debug(print_string("continuing newline\n"));
      token_t const* const token = (state->token_count > 0 ? previous_scan_token() : nullptr);
      int can_continue = token && (token->end == state->code) && (token->id & tkn_terminator);
      char_t const* const begin = (can_continue ? token->begin : state->code);
      char_t const* const code_end = state->code_end;
      while(++state->code < code_end && is_line_terminator(*state->code));
      state->current_token_flags |= token_flag_newline;
      state->is_continuer = 1;
   } else if(is_whitespace(c)) {
      token_t const* const token = (state->token_count > 0 ? previous_scan_token() : nullptr);
      int can_continue = token && (token->end == state->code) && (token->id & tkn_whitespace);
      char_t const* const begin = (can_continue ? token->begin : state->code);
      char_t const* const code_end = state->code_end;
      while(++state->code < code_end && is_whitespace(*state->code));
      if(state->was_continuer) {
         state->current_token_flags |= (state->token_flags & token_flag_continuer);
         state->is_continuer = 1;
      }
   } else return 0;
   return 1;
   // Comment - Nothing to handle
   // CommonToken::Punctuator - Nothing to handle
   // CommonToken::NumericLiteral - Nothing to handle
   // CommonToken::StringLiteral - Nothing to handle
   // CommonToken::Template - Nothing to handle
   // DivPunctuator - Nothing to handle
   // RightBracePunctuator - Nothing to handle
   // RegularExpressionLiteral - Nothing to handle
   // TemplateSubstitutionTail - Nothing to handle
}

inline_spec int scan(parse_state_t* state, uint8_t incremental, params_t params)
{
   int result = 0, comment_chars = 0;
   state->is_continuer = 0;
   state->current_token_flags = token_flag_none;
   char_t current = *(state->code);
   char_t next = (state->code + 1 < state->code_end ? *(state->code + 1) : 0);
   //printf("%d %d\n", state->template_level, state->curly_parenthesis_level);
   if(is_ascii_identifier_start(current)) {
      debug_wrap("", identifier,
         state->in_regexp_context = 0;
         result = scan_ascii_identifier(state, params);
      );
   } else if(is_common_whitespace(current)) {
      debug_wrap("space", whitespace,
         if_debug(print_string("space"));
         char_t const* const code_end = state->code_end;
         while(++state->code < code_end && is_common_whitespace(*state->code));
         //make_token(state, begin, tkn_whitespace, mask_none, precedence_none, nullptr);
         if(state->was_continuer) {
            state->current_token_flags |= (state->token_flags & token_flag_continuer);
            state->is_continuer = 1;
         }
         result = 1;
      );
   //} else if(is_common_line_terminator(current)) {
   } else if(is_line_terminator(current)) {
      debug_wrap("newline", terminator,
         char_t const* const code_end = state->code_end;
         //while(++state->code < code_end && is_common_line_terminator(*state->code));
         while(state->code < code_end && consume_terminator_sequence(state, &state->code, 0));
         //make_token(state, begin, tkn_terminator, mask_none, precedence_none, nullptr);
         state->current_token_flags |= token_flag_newline;
         state->is_continuer = 1;
         result = 1;
      );
   } else if(is_decimal(current) || (current == '.' && is_decimal(next))) {
      debug_wrap("number", numeric_literal,
         state->in_regexp_context = 0;
         result = scan_numeric_literal(state, params);
      )
   } else if(current == '\'' || current == '"') {
      debug_wrap("string", string_literal,
         state->in_regexp_context = 0;
         //if(!scan_string_literal(state, params)) { errored = 1; break; }
         result = compile_string_literal(state, params);
      );
   } else if((comment_chars = get_comment_begin_chars(state, params))) {
      debug_wrap("comment", comment,
         result = scan_comment(state, comment_chars, params);
         if(state->was_continuer) {
            state->current_token_flags |= (state->token_flags & token_flag_continuer);
         }
         state->is_continuer = 1;
      );
   } else if(current == '/') {
      if(incremental && token_diff(state->scan_token, state->parse_token) != 0) {
         state->tokenization_status = (status_flag_incomplete | status_flag_pending);
         state->scan_token->aggregated_id = 0;
         return 1;
      }
      if(state->in_regexp_context) {
         debug_wrap("regexp", regexp_literal,
            result = scan_regexp_literal(state, params);
         );
      } else {
         debug_wrap("punctuator", punctuator,
            result = scan_punctuator(state, params);
         );
      }
   } else if(current == '`' || (state->template_level != 0 && current == '}' && state->template_level + state->template_parenthesis_offset == state->curly_parenthesis_level)) {
      result = scan_template_literal(state, params);
   } else {
      debug_wrap("punctuator", punctuator,
         result = scan_punctuator(state, params);
      );
      if(!result) {
         result = scan_uncommon(state, params);
      }
   }
   state->token_flags = state->current_token_flags;
   state->was_continuer = state->is_continuer;
   return result;
}

int scan_next_token(parse_state_t* const state, uint32_t params)
{
   if(!(state->tokenization_status & status_flag_incomplete)) return 0;
   while(token_diff(state->scan_token, state->parse_token) < 2) {
      if(state->code == state->code_end) {
         position_t const begin_position = make_position(state);
         make_token(state, state->code, begin_position, tkn_eot, 0, precedence_none, nullptr);
         state->tokenization_status = status_flag_complete;
         if_debug(print_string("tokenization successful\n"););
         return 1;
      }
      state->tokenization_status = status_flag_incomplete;
      if(!scan(state, 1, params)) {
         position_t const begin_position = make_position(state);
         make_token(state, state->code, begin_position, tkn_error, 0, precedence_none, nullptr);
         state->tokenization_status = status_flag_failed;
         if_debug(print_string("tokenization failed\n"););
         return 0;
      }
      if(state->tokenization_status & status_flag_pending) return 1;
   }
   return 0;
}

wasm_export void tokenize(parse_state_t* const state, uint32_t params)
{
   if_verbose( begin_group("tokenization"); )
   int result = 1;
   start_clock();
   char_t const* const code_end = state->code_end;
   while(state->code < code_end && (result = scan(state, 0, params)));
   if(result == 0) {
      if_debug(print_string("tokenization failed\n"););
      if_debug(if(state->parse_error) print_string(state->parse_error->message););
      state->tokenization_status = status_flag_failed;
      //printf("\nparse failed at %ld\n", string - begin);
   } else {
      if_debug(print_string("tokenization successful\n"););
      position_t const begin_position = make_position(state);
      make_token(state, state->code, begin_position, tkn_eot, 0, precedence_none, nullptr);
      state->tokenization_status = status_flag_complete;
      print_elapsed_time("tokenization");
   }
   if_verbose( end_group(); )
}

#ifdef __POP_BOOL__
   #pragma pop_macro("false")
   #pragma pop_macro("true")
   #pragma pop_macro("bool")
   #undef __POP_BOOL__
#endif

#endif //_SCANNER_BASE_H_
