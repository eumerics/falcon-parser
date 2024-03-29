#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdbool.h>
#include "common.h"
#include "constants.h"
#include "nodes.h"
#include "messages.h"

#define NONE flag_none
#define AWT param_flag_await
#define DEF param_flag_default
#define IN  param_flag_in
#define RET param_flag_return
#define YLD param_flag_yield
#define TAG param_flag_tagged

#define STRICT param_flag_strict_mode
#define NOSCOPE param_flag_no_scope

#define PARAM cover_flag_parameters
#define EXPR param_flag_expression
#define FUNC param_flag_function
#define VFUN param_flag_vanilla_function
#define METHOD param_flag_method
#define CONSTR param_flag_constructor
#define CLASS param_flag_class
#define DERIVED param_flag_derived
#define FORMAL param_flag_formal
#define UNIQUE param_flag_unique_params
#define LOOSE param_flag_loose_binding
#define EXPORT param_flag_export
#define ARR_BND change_flag_array_binding
#define COV_CALL param_flag_covered_call
#define LEXICAL param_flag_lexical_binding
#define COND param_flag_conditional
#define COND_BODY param_flag_conditional_body

#define RESET_FLAGS

#define _get_3rd_arg(arg1, arg2, arg3, ...) arg3
#define _get_4th_arg(arg1, arg2, arg3, arg4, ...) arg4
#define _get_5th_arg(arg1, arg2, arg3, arg4, arg5, ...) arg5
#define _get_6th_arg(arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6
#define _get_7th_arg(arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...) arg7

#define word(name) rw_##name
#define precedence(operator) (operator.precedence & 0xf8)

#define token_length(token) (token->end - token->begin)
#define raw_char(token, offset) (token->begin[offset])
#define token_is(name, token) ( \
   (token->end - token->begin == strlen(#name)) && \
   (strncmp_impl(token->begin, stringize(name), strlen(#name)) == 0) \
)
#if defined(MEMOPT)
   #define _offset_token(token, offset) ( \
      (token) += (((token) - state->token_begin + offset) % token_capacity) \
         - ((token) - state->token_begin) \
   )
   #define _token_at_offset(token, offset) (state->token_begin + ((token) - state->token_begin + offset) % token_capacity)
   #define increment_current_token() (state->parse_token = (token_t*)(_token_at_offset(current_token(), 1)))
#else
   #define _offset_token(token, offset) ((token) += offset)
   #define _token_at_offset(token, offset) ((token) + offset)
   #define increment_current_token() (++state->parse_token)
#endif
#define increment_token(token) _offset_token(token, 1)
#define current_token() (state->parse_token)
#define previous_token() _token_at_offset(current_token(), -1)
#define next_token() _token_at_offset(current_token(), 1)
#define current_token_id() (current_token()->id)
#define current_token_length() (token_length(current_token()))
#define current_token_is(name) token_is(name, current_token())
#define disable_pending_regexp_context() \
   if(state->tokenization_status & status_flag_pending) state->in_regexp_context = 0;
#define enable_pending_regexp_context() \
   if(state->tokenization_status & status_flag_pending) state->in_regexp_context = 1;

//#define consume_token() (++state->parse_token)
#define consume_token() ( \
   ++state->tokens_consumed, \
   increment_current_token(), \
   (params & param_flag_streaming) && scan_next_token(state, params) \
)
#ifdef verbose
   #define log_and_consume_token() (print_token_consumption(), consume_token())
#else
   #define log_and_consume_token() consume_token()
#endif
#define next() log_and_consume_token()

#define exists(token_id) (current_token()->id == token_id)
#define exists_word(name) (current_token()->id == word(name))
#define exists_unescaped_word(name) (current_token()->id == word(name) && !(current_token()->flags & token_flag_escaped))
#define exists_mask(mask) (current_token()->group & mask)
#define exists_newline() (current_token()->flags & token_flag_newline)
#define exists_newline_ahead(offset) (next_token()->flags & token_flag_newline)
#define optional(token_id) (current_token()->id == token_id ? (next(), 1) : 0)
#define optional_word(name) (current_token()->id == word(name) ? (next(), 1) : 0)
#define optional_mask(mask) (current_token()->group & mask ? (next(), 1) : 0)
#define expect(token_id) { \
   if(current_token()->id != token_id) { \
      state->expected_token_id = token_id; \
      passon(nullptr); \
   } \
   next(); \
}
#define expect_word(name) expect(word(name))
#define expect_mask(mask) { \
   if(!(current_token()->group & mask)) { \
      state->expected_mask = mask; \
      passon(nullptr); \
   } \
   next(); \
}
//#define ensure(token_id) if_else_debug(expect(token_id), next())
//#define ensure_word(name) if_else_debug(expect_word(name), next())
//#define ensure_mask(mask) if_else_debug(expect_mask(mask), next())
#define ensure(token_id) expect(token_id)
#define ensure_word(name) expect_word(name)
#define ensure_mask(mask) expect_mask(mask)
#define exists_ahead(token_id) (next_token()->id == token_id)
#define exists_ahead_word(name) (next_token()->id == word(name))
#ifndef MEMOPT
   #define ensure_non_annex_number() { \
      token_t const* const token = current_token(); \
      if(token->detail && (params & STRICT)) { \
         compiled_number_t* cn = token->detail; \
         if(cn->compile_flags & compile_flag_numeric_annex) { \
            return nullptr; \
         } \
      } \
   }
   #define ensure_non_annex_string() { \
      token_t const* const token = current_token(); \
      if(token->detail && (params & STRICT)) { \
         compiled_string_t* cs = token->detail; \
         if(cs->compile_flags & compile_flag_octal) { \
            return nullptr; \
         } \
      } \
   }
#else
   #define ensure_non_annex_number()
   #define ensure_non_annex_string()
#endif

#define initialize_node(node_type) { \
   print_make_node(node_type); \
   token_t const* token = current_token(); \
   node->begin = token->begin; \
   node->location = parser_malloc(mm_location, sizeof(location_t)); \
   *node->location = (location_t) { \
      .begin = token->location.begin, \
      .source = token->location.source \
   }; \
   node->type = pnt_##node_type; \
   node->group = png_##node_type; \
   if_extensions(node->data_type = nullptr;) \
}
#if defined(TEST)
   #define test_memset(p, i, n) memset(p, i, n)
#else
   #define test_memset(p, i, n)
#endif
#define make_node(node_type) \
   typedef node_type##_t parent_node_t; \
   node_type##_t* node = (node_type##_t*) parser_malloc(mm_parse_nodes, sizeof(node_type##_t)); \
   test_memset(node, 0xff, sizeof(node_type##_t)); \
   initialize_node(node_type);
#define make_child_node(node_type) \
   parent_node_t* parent = node; \
   typedef node_type##_t parent_node_t; \
   node_type##_t* node = (node_type##_t*) parser_malloc(mm_parse_nodes, sizeof(node_type##_t)); \
   test_memset(node, 0xff, sizeof(node_type##_t)); \
   initialize_node(node_type);
#define complete_node() (node->end = previous_token()->end, node->location->end = previous_token()->location.end)
#define completed_node() (complete_node(), node)
#define return_node() { complete_node(); passon(node); }
#define passon(node) { _print_parse_ascent(node); return node; }

#define save_begin() \
   char_t const* begin = current_token()->begin; \
   position_t const begin_position = current_token()->location.begin;
#define save_end() \
   char_t const* end = current_token()->end; \
   position_t const end_position = current_token()->location.end;
#define assign_begin() node->begin = begin; node->location->begin = begin_position;
//#define assign_end() node->end = end;
//#define copy_begin(object) node->begin = ((parse_node_t*)(object))->begin;
//#define assign_begin_to(object) ((parse_node_t*)(object))->begin = begin;
//#define assign_end_to(object) ((parse_node_t*)(object))->end = end;
#define assign(property, value) node->property = value;
#define assign_to_parent(property, value) parent->property = value;
#define assign_operator() { \
   token_t const* const token = current_token(); \
   node->operator.aggregated_id = token->aggregated_id; \
}
#define assign_token() { \
   token_t const* const token = current_token(); \
   node->flags = flag_none; \
   node->token_id = token->id; \
   node->token_group = token->group; \
   node->compiled_string = token->detail; \
}
#define assign_numeric_token() { \
   token_t const* const token = current_token(); \
   node->token_id = token->id; \
   node->token_group = token->group; \
   node->compiled_number = token->detail; \
}

inline_spec uint8_t node_type(void* node)
{
   return ((parse_node_t*)(node))->type;
}
#define type_equal(source, target) (((parse_node_t*)(source))->type ==  ((parse_node_t*)(target))->type)
#define node_has_signature(source, type) ( \
   node_type(source) == pnt_##type || ( \
      node_type(source) == pnt_logical_expression && \
      pnt_##type == pnt_binary_expression \
   ) \
)
#define node_is_an(type, node) (((parse_node_t*)(node))->group & node_group_##type)
#define node_is_a(type, node) node_is_an(type, node)
#define node_has(type, node) node_is_an(type, node)
#define node_type_is(node_type, node) (((parse_node_t*)(node))->type == pnt_##node_type)
#define _node_as2(target, node) ((target##_t*)(node))
#define _node_as3(target, node, var_name) \
   if_verbose( if(pnt_##target != 0) assert(node_has_signature(node, target), __FILE__, __LINE__); ) \
   target##_t* var_name = (target##_t*)(node);
#define _choose_node_as(...) _get_4th_arg(__VA_ARGS__, _node_as3, _node_as2, undefined, )
#define node_as(...) _choose_node_as(__VA_ARGS__)(__VA_ARGS__)
#define set_node_type_of(node, target_type) (((parse_node_t*)(node))->type = pnt_##target_type)
// clear the exclusive group mask before assigning the desired flag
#define set_change_flag_to(type, flags) \
   ((flags & change_mask_group) | change_flag_##type)

#include "scope.h"

#define _init_list(list) \
   list.node_count = 0; \
   list.head = nullptr; \
   list.current = nullptr;
#define _start_list(list_name) \
   parse_node_list_state_t list_name = {0, nullptr, nullptr};
#define start_list() _start_list(list_state)
#define start_named_list(list) _start_list(list)
#define init_named_list(list) _init_list(list)

parse_list_node_t* make_list_node(parse_state_t* state, void* parse_node) {
   parse_list_node_t* list_node =
      (parse_list_node_t*) parser_malloc(mm_parse_list_nodes, sizeof(parse_list_node_t));
   list_node->parse_node = parse_node;
   list_node->next = nullptr;
   return list_node;
}
#define _add_to_list(list, parse_node) { \
   parse_list_node_t* list_node = make_list_node(state, parse_node); \
   if(list.current == nullptr) { \
      list.head = list.current = list_node; \
   } else { \
      list.current->next = list_node; \
      list.current = list_node; \
   } \
   ++list.node_count; \
}
#define add_to_list(parse_node) _add_to_list(list_state, parse_node)
#define add_to_named_list(list, parse_node) _add_to_list(list, parse_node)
#define add_to_cover_list(node) { \
   cover_list_node_t* list_node = parser_malloc(mm_cover_list_nodes, sizeof(cover_list_node_t)); \
   list_node->cover_node = (parse_node_t*)(node); \
   if(state->cover_node_list.head == nullptr) { \
      list_node->prev = list_node->next = nullptr; \
      state->cover_node_list.head = state->cover_node_list.tail = list_node; \
   } else { \
      list_node->prev = state->cover_node_list.tail; \
      list_node->next = nullptr; \
      state->cover_node_list.tail->next = list_node; \
      state->cover_node_list.tail = list_node; \
   } \
   ++state->cover_node_list.count; \
   node->cover_node = list_node; \
}
#define remove_from_cover_list(node) { \
   cover_list_node_t* prev = node->cover_node->prev; \
   cover_list_node_t* next = node->cover_node->next; \
   if(prev == nullptr) state->cover_node_list.head = next; \
   else prev->next = next; \
   if(next == nullptr) state->cover_node_list.tail = prev; \
   else next->prev = prev; \
   --state->cover_node_list.count; \
}

#define _list_head(list) (list.head == nullptr ? (void*)(&empty_list) : (void*)(list.head))
#define list_head() _list_head(list_state)
#define named_list_head(list) _list_head(list)

#define _raw_list_head(list) list.head
#define raw_list_head() _raw_list_head(list_state)
#define raw_named_list_head(list) _raw_list_head(list)



#define is_a_directive(token) ( \
   token->id == tkn_string_literal && \
   ((increment_token(token) == state->parse_token) || \
    (token->id == ';' && increment_token(token) == state->parse_token) \
   ) \
)
#define is_use_strict(token) ( \
   (token->end - token->begin - 2 == strlen("use strict")) && \
   (strncmp_impl(token->begin + 1, stringize(use strict), strlen("use strict")) == 0) \
)
#define is_let_a_keyword(params) ( \
   !(current_token()->flags & token_flag_escaped) && ( \
      ((params & STRICT) && (next_token()->group & mask_reserved_word)) || \
      (next_token()->group & (mask_binding_pattern | mask_identifier)) \
   ) \
)
//(params & param_flag_strict_mode) ||
bool is_reserved_symbol(parse_state_t* state, identifier_t const* const identifier, params_t params)
{
   if(!identifier) return false;
   token_id_t token_id = identifier->token_id;
   token_group_t token_group = identifier->token_group;
   if(params & param_flag_strict_mode) {
      if(token_group & mask_strict_reserved_word) {
         return_node_error(invalid_strict_mode_identifier, identifier, true);
      } else if(token_id == rw_yield) {
         return_node_error(yield_in_strict_mode, identifier, true);
      } else if(token_id == rw_await && (params & param_flag_module)) {
         return_node_error(await_in_module, identifier, true);
      } else if(token_id == rw_eval || token_id == rw_arguments) {
         return_node_error(eval_args_in_strict_mode, identifier, true);
      }
   }
   return false;
}
inline_spec bool is_a_binding_identifier(parse_state_t* state, void const* const node, params_t params)
{
   if(!node_type_is(identifier, node)) {
      return_node_error(invalid_binding_target, node, false);
   } else if(params & STRICT) {
      token_id_t token_id = ((compiled_parse_node_t const*)(node))->token_id;
      if(token_id == rw_eval || token_id == rw_arguments) {
         return_node_error(eval_args_in_strict_mode, node, false);
      }
   }
   return true;
}
bool is_an_eventual_identifier(void* node)
{
   node_type_t type = node_type(node);
   if(type == pnt_identifier) return true;
   while(type == pnt_parenthesized_expression)
   {
      node = node_as(parenthesized_expression, node)->expression;
      type = node_type(node);
      if(type == pnt_identifier) return true;
   }
   return false;
}
void* get_parenthesized_node(parenthesized_expression_t* pe)
{
   if(node_type_is(parenthesized_expression, pe->expression)) {
      return get_parenthesized_node(pe->expression);
   }
   return pe->expression;
}
inline_spec bool is_an_assignment_target(parse_state_t* state, void* node, params_t params)
{
   //[TODO] strict mode exclusions of 'eval' and 'arguments'
   if(node_type_is(parenthesized_expression, node)) {
      node_as(parenthesized_expression, node, pe);
      if(node_type_is(expression, pe->expression)) {
         node_as(expression, pe->expression, expression);
         node_as(parse_list_node, expression->expressions, list_node);
         if(list_node->next != nullptr) return false;
         return is_an_assignment_target(state, list_node->parse_node, params);
      } else {
         return is_an_assignment_target(state, pe->expression, params);
      }
   }
   if(!node_is_an(assignment_target, node)) {
      if(state->parse_error) {
         // clear any errors the might come after this error
         location_t const* const location = node_as(parse_node, node)->location;
         if(state->error_position.line > location->begin.line ||
            (state->error_position.line == location->begin.line &&
             state->error_position.column >= location->begin.column)
         ){
            state->parse_error = nullptr;
         }
      }
      return false;
   }
   if((params & STRICT) && node_type_is(identifier, node)){
      token_id_t token_id = node_as(identifier, node)->token_id;
      if(token_id == rw_eval || token_id == rw_arguments) {
         return_node_error(eval_args_in_strict_mode, node, false);
      }
   }
   return true;
}
#define property_key_is(name, node) _property_key_is(state, node, stringize(name), strlen_impl(stringize(name)))
inline_spec bool _property_key_is(parse_state_t* state, property_t* property, char_t const* name, size_t const length)
{
   parse_node_t* key = (parse_node_t*)(property->key);
   char_t const* begin;
   char_t const* end;
   if(key->type == pnt_identifier) {
      begin = key->begin; end = key->end;
   } else if(key->type == pnt_string_literal) {
      begin = key->begin + 1; end = key->end - 1;
   } else {
      return false;
   }
   return (strncmp_impl(begin, name, length) == 0);
}
#define assert_unique_scope() if(!is_scope_unique(state)) return nullptr;
#define assert_lexical_uniqueness(_node, binding_flag, symbol_type) \
   if(!insert_symbol(state, (identifier_t*)(_node), binding_flag, symbol_type, params)) { \
      return_node_error(duplicate_symbol, _node, nullptr); \
   }
#define assert_label_uniqueness(_node) \
   if(!insert_label(state, (identifier_t*)(_node), params)) { \
      return_node_error(duplicate_label, _node, nullptr); \
   }
#define assert_export_uniqueness(_node) \
   if(!add_symbol_to_table(state, state->export_symbol_table, (identifier_t*)(_node), NONE, NONE)) { \
      return_node_error(duplicate_export, _node, nullptr); \
   }
#define validate_strict_mode() \
   if(state->current_scope_list_node->scope->flags & scope_flag_non_strict) { \
      return_token_error(invalid_strict_mode, directive_token, nullptr); \
   }
bool retro_act_strict_mode(parse_state_t* state, parse_list_node_t* list_node)
{
   assert_unique_scope();
   scope_t const* const scope = state->current_scope_list_node->scope;
   if(scope->identifier && is_reserved_symbol(state, scope->identifier, STRICT)) {
      return 0;
   }
   symbol_list_node_t const* symbol_list_node = scope->symbol_list.head;
   while(symbol_list_node) {
      if(is_reserved_symbol(state, symbol_list_node->symbol->identifier, STRICT)) return 0;
      // ideally we should use ->scope_next to retrieve the next symbol
      // but syntaxt leading to 'use strict' would not have introduced
      // a new scope, so ->sequence_next = ->scope_next
      symbol_list_node = symbol_list_node->sequence_next;
   }
   while(list_node->next != nullptr) {
      node_as(directive, list_node->parse_node, directive);
      node_as(string_literal, directive->expression, literal);
      if(literal->compiled_string && (literal->compiled_string->compile_flags & compile_flag_octal)) {
         //[TODO] provide proper error location
         //set_error(octal_in_strict); return false;
         return_compiled_error(literal->compiled_string, false);
      }
      list_node = list_node->next;
   }
   return true;
}

#define make_params(remove_filter, add_filter) (params & ~(params_t)(remove_filter)) | ((params_t)(add_filter))

// define parse with optional arguments
#define _parse1(type) _parse3(type, NONE, NONE)
#define _parse2(property, type) _parse4(property, type, NONE, NONE)
#define _parse3(type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(type == nullptr) passon(nullptr);
#define _parse4(property, type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* property##_##type = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(property##_##type == nullptr) passon(nullptr); \
   node->property = property##_##type;
#define _parse_with_arg2(arg, type) _parse_with_arg4(arg, type, NONE, NONE)
#define _parse_with_arg3(arg, property, type) _parse_with_arg5(arg, property, type, NONE, NONE)
#define _parse_with_arg4(arg, type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = parse_##type(state, tree_state, arg, make_params(remove_filter, add_filter)); \
   if(type == nullptr) passon(nullptr);
#define _parse_with_arg5(arg, property, type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* property##_##type = parse_##type(state, tree_state, arg, make_params(remove_filter, add_filter)); \
   if(property##_##type == nullptr) passon(nullptr); \
   node->property = property##_##type;
#define _continue_with4(type, object, begin, begin_position) _continue_with6(type, object, begin, begin_position, NONE, NONE)
#define _continue_with5(type, object, begin, begin_position, arg) _continue_with7(type, object, begin, begin_position, arg, NONE, NONE)
#define _continue_with6(type, object, begin, begin_position, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = continue_with_##type(state, tree_state, object, begin, begin_position, make_params(remove_filter, add_filter)); \
   if(type == nullptr) passon(nullptr);
#define _continue_with7(type, object, begin, begin_position, arg, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = continue_with_##type(state, tree_state, object, begin, begin_position, arg, make_params(remove_filter, add_filter)); \
   if(type == nullptr) passon(nullptr);
#define _enparse1(type) _enparse3(type, NONE, NONE)
#define _enparse2(property, type) _enparse4(property, type, NONE, NONE)
#define _enparse3(type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = ensure_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(type == nullptr) passon(nullptr);
#define _enparse4(property, type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* property##_##type = ensure_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(property##_##type == nullptr) passon(nullptr); \
   node->property = property##_##type;
#define _list_parse1(type) _list_parse3(type, NONE, NONE)
#define _list_parse2(property, type) _list_parse4(property, type, NONE, NONE)
#define _list_parse3(type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(type == nullptr) passon(nullptr); \
   if(type == &empty_list) { \
      type = nullptr; \
   }
#define _list_parse4(property, type, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* property##_##type = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(property##_##type == nullptr) passon(nullptr); \
   if(property##_##type == &empty_list) { \
      node->property = nullptr; \
   } else { \
      node->property = property##_##type; \
   }
#define _optional_parse1(type) _optional_parse3(type, NONE, NONE)
#define _optional_parse3(type, remove_filter, add_filter) \
   size_t const type##_tokens_consumed = state->tokens_consumed; \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(type == errptr || type == nullptr && state->tokens_consumed != type##_tokens_consumed) { \
      passon(nullptr); \
   }
#define _try_parse1(type) _try_parse3(type, NONE, NONE)
#define _try_parse3(type, remove_filter, add_filter) { \
   optional_parse(type); \
   if(type) passon(type); \
}
#define _assign_parsed2(type, var_name) _assign_parsed4(type, var_name, NONE, NONE)
#define _assign_parsed4(type, var_name, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   var_name = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(var_name == nullptr) passon(nullptr);
#define _declare_parsed2(type, var_name) _declare_parsed4(type, var_name, NONE, NONE)
#define _declare_parsed4(type, var_name, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* var_name = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(var_name == nullptr) passon(nullptr);
//   void* node = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
//   if(node) passon(node); \
//}
#define _passon_parsed1(type) { parse(type); passon(type); }
#define _passon_parsed3(type, remove_filter, add_filter) { parse(type, remove_filter, add_filter); passon(type); }
#define _passon_enparsed1(type) { enparse(type); passon(type); }
#define _passon_enparsed3(type, remove_filter, add_filter) { enparse(type, remove_filter, add_filter); passon(type); }
#define _choose_parse(...) _get_5th_arg(__VA_ARGS__, _parse4, _parse3, _parse2, _parse1, )
#define parse(...) _choose_parse(__VA_ARGS__)(__VA_ARGS__)
#define _choose_parse_with_arg(...) _get_6th_arg(__VA_ARGS__, _parse_with_arg5, _parse_with_arg4, _parse_with_arg3, _parse_with_arg2, undefined, )
#define parse_with_arg(...) _choose_parse_with_arg(__VA_ARGS__)(__VA_ARGS__)
#define _choose_continue_with(...) _get_7th_arg(__VA_ARGS__, _continue_with6, _continue_with5, _continue_with4, _continue_with3, undefined, undefined, )
#define continue_with(...) _choose_continue_with(__VA_ARGS__)(__VA_ARGS__)
#define _choose_enparse(...) _get_5th_arg(__VA_ARGS__, _enparse4, _enparse3, _enparse2, _enparse1, )
#define enparse(...) _choose_enparse(__VA_ARGS__)(__VA_ARGS__)
#define _choose_list_parse(...) _get_5th_arg(__VA_ARGS__, _list_parse4, _list_parse3, _list_parse2, _list_parse1, )
#define list_parse(...) _choose_list_parse(__VA_ARGS__)(__VA_ARGS__)
#define _choose_optional_parse(...) _get_4th_arg(__VA_ARGS__, _optional_parse3, undefined, _optional_parse1, )
#define optional_parse(...) _choose_optional_parse(__VA_ARGS__)(__VA_ARGS__)
#define _choose_try_parse(...) _get_4th_arg(__VA_ARGS__, _try_parse3, undefined, _try_parse1, )
#define try(...) _choose_try_parse(__VA_ARGS__)(__VA_ARGS__)
#define _choose_assign_parsed(...) _get_5th_arg(__VA_ARGS__, _assign_parsed4, undefined, _assign_parsed2, undefined, )
#define assign_parsed(...) _choose_assign_parsed(__VA_ARGS__)(__VA_ARGS__)
#define _choose_declare_parsed(...) _get_5th_arg(__VA_ARGS__, _declare_parsed4, undefined, _declare_parsed2, undefined, )
#define declare_parsed(...) _choose_declare_parsed(__VA_ARGS__)(__VA_ARGS__)
#define _choose_passon_parsed(...) _get_4th_arg(__VA_ARGS__, _passon_parsed3, undefined, _passon_parsed1, )
#define passon_parsed(...) _choose_passon_parsed(__VA_ARGS__)(__VA_ARGS__)
#define _choose_passon_enparsed(...) _get_4th_arg(__VA_ARGS__, _passon_enparsed3, undefined, _passon_enparsed1, )
#define passon_enparsed(...) _choose_passon_enparsed(__VA_ARGS__)(__VA_ARGS__)

#define save_tree_flags(filter) \
   uint32_t saved_tree_flags = (tree_state->flags & filter);
#define set_tree_flags(filter) tree_state->flags |= filter;
#define mask_tree_flags(filter) tree_state->flags &= ~filter;
#define restore_tree_flags(filter) \
   mask_tree_flags(filter); \
   tree_state->flags |= saved_tree_flags;
#define save_and_mask_tree_flags(filter) \
   save_tree_flags(filter); \
   mask_tree_flags(filter);

void* parse_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_assignment_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_lhs_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);

#define parse_semicolon() { \
   if(exists(';')) { \
      ensure(';'); \
   } else { \
      if(!exists('}') && !exists(tkn_eot) && !exists_newline()) expect(';'); \
   } \
}

bool change_node_types(parse_state_t* state, parse_list_node_t* list_node, bool has_trailing_comma, uint8_t flags, params_t params);
bool lexically_bind_pattern_nodes(parse_state_t* state, parse_list_node_t* list_node, uint8_t flags, params_t params);
inline_spec node_type_t select_array_pattern_for(uint8_t flags)
{
   if(flags & change_flag_assignment) return pnt_array_assignment_pattern;
   return pnt_array_pattern;
}
inline_spec node_type_t select_object_pattern_for(uint8_t flags)
{
   if(flags & change_flag_assignment) return pnt_object_assignment_pattern;
   return pnt_object_pattern;
}
bool lexically_bind_pattern(parse_state_t* state, void* node, uint8_t flags, params_t params)
{
   switch(node_type(node)) {
      case pnt_array_pattern:
      case pnt_array_assignment_pattern: {
         node_as(array_pattern, node, ap);
         flags = set_change_flag_to(array, flags);
         return lexically_bind_pattern_nodes(state, ap->elements, flags, params);
      }
      case pnt_object_pattern:
      case pnt_object_assignment_pattern: {
         node_as(object_pattern, node, op);
         flags = set_change_flag_to(object, flags);
         return lexically_bind_pattern_nodes(state, op->properties, flags, params);
      }
      default: {
         /*
         if(!is_a_binding_identifier(state, node, params)) {
            return_error(expecting_binding_identifier, false);
         }
         */
         if(!is_a_binding_identifier(state, node, params)) return false;
         assert_lexical_uniqueness(node, flags & LOOSE, NONE);
         return true;
      }
   }
}
bool lexically_bind_pattern_nodes(parse_state_t* state, parse_list_node_t* list_node, uint8_t flags, params_t params)
{
   while(list_node != nullptr) {
      parse_node_t* parse_node = (parse_node_t*)(list_node->parse_node);
      if(parse_node == nullptr) {
         return_error(elision_in_binding_pattern, false);
      }
      if(parse_node->type == pnt_rest_element) {
         parse_node = node_as(rest_element, parse_node)->argument;
      } else if(flags & change_flag_object) {
         if(!node_type_is(property, parse_node)) {
            return_error(is_not_a_property_node, false);
         }
         node_as(property, parse_node, property);
         parse_node = property->value;
      }
      if(parse_node == nullptr) return_error(null_node_in_bind_nodes, false);
      if(!lexically_bind_pattern(state, parse_node, flags, params)) return false;
      list_node = list_node->next;
   }
   return true;
}
bool change_lhs_node_type(parse_state_t* state, void* node, uint8_t flags, params_t params)
{
   switch(node_type(node)) {
      case pnt_array_expression: {
      //case pnt_array_assignment_pattern: {
         node_as(array_expression, node, ap);
         if(flags & change_flag_binding) {
            ap->type = pnt_array_pattern;
            ap->group = png_array_pattern;
         } else {
            ap->type = pnt_array_assignment_pattern;
            ap->group = png_array_assignment_pattern;
         }
         uint8_t change_flags = set_change_flag_to(array, flags);
         return change_node_types(state, ap->elements, ap->has_trailing_comma, change_flags, params);
      }
      case pnt_object_expression: {
      //case pnt_object_assignment_pattern: {
         node_as(object_expression, node, op);
         if(flags & change_flag_binding) {
            op->type = pnt_object_pattern;
            op->group = png_object_pattern;
         } else {
            op->type = pnt_object_assignment_pattern;
            op->group = png_object_assignment_pattern;
         }
         uint8_t change_flags = set_change_flag_to(object, flags);
         return change_node_types(state, op->properties, op->has_trailing_comma, change_flags, params);
      }
      default: {
         if(flags & change_flag_binding) {
            return lexically_bind_pattern(state, node, flags, params);
         }
         if(!is_an_assignment_target(state, node, params)) {
            if(state->parse_error) return false;
            else if(flags & change_flag_binding) {
               return_node_error(invalid_binding_target, node, false);
            } else {
               return_node_error(invalid_assignment_target, node, false);
            }
         }
         return true;
      }
   }
}
bool change_node_types(parse_state_t* state, parse_list_node_t* list_node, bool has_trailing_comma, uint8_t flags, params_t params)
{
   while(list_node != nullptr) {
      bool enforce_non_strict_mode = true;
      parse_node_t* parse_node = (parse_node_t*)(list_node->parse_node);
      parse_node_t* error_node = parse_node;
      if(parse_node != nullptr) {
         // get the RestElement argument
         rest_element_t* rest_element = nullptr;
         if(parse_node->type == pnt_spread_element) {
            rest_element = (rest_element_t*)(parse_node);
            if(rest_element->cover_node) remove_from_cover_list(rest_element);
            parse_node->type = pnt_rest_element;
            void* argument = node_as(spread_element, parse_node)->argument;
            if(flags & change_flag_assignment) {
               if(flags & change_flag_object) {
                  // 12.15.7.1: Static Semantics: Early Errors
                  //    AssignmentRestProperty: ... DestructuringAssignmentTarget
                  // It is a Syntax Error if DestructuringAssignmentTarget is an
                  // ArrayLiteral or an ObjectLiteral
                  uint8_t argument_type = node_type(argument);
                  if(argument_type == pnt_array_expression ||
                     argument_type == pnt_object_expression
                  ) return_error(object_assignment_rest, false);
               }
               if(list_node->next != nullptr) { return_node_error(middle_rest, rest_element, false); }
               //if(has_trailing_comma) { return_node_error(trailing_comma, parse_node, false); }
               if(has_trailing_comma) { return_node_error(middle_rest, rest_element, false); }
               //if(flags & change_flag_object) break;
               //if(!is_a_binding_identifier(state, argument, params)) return false;
               //return_error(missing_assignment_or_binding_flag, false);
            }
            parse_node = error_node = argument;
         }
         if(!rest_element && (flags & change_flag_object)) {
            if(!node_type_is(property, parse_node)) {
               return_error(is_not_a_property_node, false);
            }
            node_as(property, parse_node, property);
            /*
            if((property->kind != property_kind_init) ||
               ((property->flags & ~property_flag_shorthand) != flag_none)
            ){
               return_error(invalid_binding_element, false);
            }
            */
            parse_node = property->value;
         }
         if(parse_node == nullptr) return_error(null_node_in_change_types, false);
         switch(node_type(parse_node)) {
            case pnt_initialized_name: {
               node_as(initialized_name, parse_node, init_name);
               remove_from_cover_list(init_name);
               /*
               if(!is_a_binding_identifier(state, init_name->left, params)){
                  return_node_error(invalid_binding_target, init_name->left, false);
               }
               */
               if(flags & change_flag_binding) {
                  assert_lexical_uniqueness(init_name->left, flags & LOOSE, NONE);
               }
               break;
            }
            case pnt_assignment_expression: {
               node_as(assignment_expression, parse_node, ae);
               if(ae->operator.id != '=') return_error(non_assignment, false);
               ae->type = pnt_assignment_pattern;
               if(flags & change_flag_binding) {
                  if(!change_lhs_node_type(state, ae->left, flags, params)) return false;
               }
               break;
            }
            case pnt_array_expression: {
               node_as(array_expression, parse_node, ae);
               ae->type = select_array_pattern_for(flags);
               //uint8_t change_flags = (flags & change_mask_cover) | change_flag_array;
               uint8_t change_flags = set_change_flag_to(array, flags);
               if(!change_node_types(state, ae->elements, ae->has_trailing_comma, change_flags, params)) return false;
               break;
            }
            case pnt_object_expression: {
               node_as(object_expression, parse_node, oe);
               oe->type = select_object_pattern_for(flags);
               //uint8_t change_flags = (flags & change_mask_cover) | change_flag_object;
               uint8_t change_flags = set_change_flag_to(object, flags);
               if(!change_node_types(state, oe->properties, oe->has_trailing_comma, change_flags, params)) return false;
               break;
            }
            default: {
               if(flags & change_flag_assignment) {
                  if(!is_an_assignment_target(state, parse_node, params)) {
                     if(state->parse_error) return false;
                     else return_node_error(invalid_assignment_target, error_node, false);
                  }
               }
               if(flags & change_flag_binding) {
                  /*
                  if(node_type_is(rest_element, parse_node)) {
                     if(list_node->next != nullptr) return_error(middle_rest, false);
                     break;
                  }
                  */
                  /*
                  if(!is_a_binding_identifier(state, parse_node, params)) {
                     return_node_error(invalid_binding_target, parse_node, false);
                  }
                  */
                  if(!is_a_binding_identifier(state, parse_node, params)) return false;
                  assert_lexical_uniqueness(parse_node, flags & LOOSE, NONE);
                  if(!rest_element) enforce_non_strict_mode = false;
               }
               ///*
               if(rest_element) {
                  if(list_node->next != nullptr) { return_node_error(middle_rest, rest_element, false); }
                  //if(has_trailing_comma) { return_node_error(trailing_comma, parse_node, false); }
                  if(has_trailing_comma) { return_node_error(middle_rest, rest_element, false); }
               }
               //*/
            }
         }
         if(enforce_non_strict_mode && (flags & change_flag_binding)) {
            state->current_scope_list_node->scope->flags |= scope_flag_non_strict;
         }
      } else {
         if(!(flags & change_flag_array)) return false;
      }
      //list_node = (parse_list_node_t*)(list_node->next);
      list_node = list_node->next;
   }
   return true;
}

// ====== IDENTIFIERS / LITERALS ====== //
/*
IdentifierReference[Yield, Await]:
   Identifier
   [~Yield] yield
   [~Await] await
BindingIdentifier[Yield, Await]:
   Identifier
   yield
   await
LabelIdentifier[Yield, Await]:
   Identifier
   [~Yield] yield
   [~Await] await
Identifier:
   IdentifierName but not ReservedWord
Literal:
   NullLiteral
   BooleanLiteral
   NumericLiteral
   StringLiteral
RegularExpressionLiteral
*/
#ifdef EXTENSIONS
inline_spec identifier_t* _parse_identifier(parse_state_t* state, parse_tree_state_t* tree_state, bool for_binding_id, params_t params);
type_identifier_t* parse_type_identifier(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(type_identifier);
   {
      start_list();
      if(optional(pnct_namespace)) {
         add_to_list(nullptr);
      }
      while(exists_ahead(pnct_namespace)) {
         identifier_t* namespace = _parse_identifier(state, tree_state, false, params);
         add_to_list(namespace);
         expect(pnct_namespace);
      }
      assign(namespace, raw_list_head());
   }
   identifier_t* identifier = _parse_identifier(state, tree_state, false, params);
   assign(type_name, identifier);
   {
      start_list();
      if(optional('[')) {
         do {
            parse(type_identifier);
            add_to_list(type_identifier);
         } while(optional(','));
         expect(']');
      }
      assign(parameters, raw_list_head());
   }
   return_node();
}
#endif
inline_spec identifier_t* _parse_identifier(parse_state_t* state, parse_tree_state_t* tree_state, bool for_binding_id, params_t params)
{
   token_t const* const token = current_token();
   token_id_t token_id = token->id;
   if(params & param_flag_strict_mode) {
      if(token->group & mask_strict_reserved_word) {
         return_error(invalid_strict_mode_identifier, nullptr);
      } else if(token_id == rw_yield) {
         return_error(yield_in_strict_mode, nullptr);
      } else if(token_id == rw_await && (params & param_flag_module)) {
         return_error(await_in_module, nullptr);
      } else if(for_binding_id && (token_id == rw_eval || token_id == rw_arguments)) {
         return_error(eval_args_in_strict_mode, nullptr);
      }
   }
   if(((params & YLD) && (token_id == rw_yield)) || ((params & AWT) && (token_id == rw_await))) {
      return_error(contextual_identifier, nullptr);
   }
   make_node(identifier); assign_token(); ensure_mask(mask_identifier);
#ifdef COMPILER
   node->offset = -1;
#endif
   complete_node();
#ifdef EXTENSIONS
   assign(type_identifier, nullptr);
   assign(data_type, nullptr);
   if(for_binding_id) {
      if(optional(':')) {
         parse(type_identifier, type_identifier);
      }
   }
#endif
   if((params & COV_CALL) && token_id == rw_await) {
      scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
      if(!hoisting_scope->first_yield_or_await) {
         hoisting_scope->first_yield_or_await = node;
      }
   }
   //return completed_node();
   return node;
}
inline_spec identifier_t* parse_identifier_reference(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   identifier_t* reference = _parse_identifier(state, tree_state, false, params);
#ifdef COMPILER
   resolve_reference(state, reference);
#endif
   passon(reference);
}
inline_spec identifier_t* parse_binding_identifier(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   identifier_t* identifier = _parse_identifier(state, tree_state, true, params);
#ifdef COMPILER
   //[REVIEW] possibly merge conditional param and identifier flags
   identifier->flags |= identifier_flag_declaration;
   if(params & param_flag_conditional) {
      identifier->flags |= identifier_flag_conditional;
   }
#endif
   passon(identifier);
}
inline_spec identifier_t* parse_label_identifier(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   identifier_t* label = _parse_identifier(state, tree_state, false, params);
   passon(label);
}
inline_spec identifier_t* parse_identifier_name(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(identifier); assign_token(); ensure_mask(mask_idname);
#ifdef COMPILER
   node->offset = -1;
#endif
#ifdef EXTENSIONS
   node->type_identifier = nullptr;
#endif
   return_node();
}
inline_spec literal_t* parse_literal(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(literal);
   assign(token_id, current_token_id());
   ensure_mask(mask_literal);
   return_node();
}
inline_spec numeric_literal_t* parse_numeric_literal(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   ensure_non_annex_number();
   make_node(numeric_literal);
   assign_numeric_token();
#ifdef EXTENSIONS
   token_t const* const token = current_token();
   compiled_number_t const* const detail = token->detail;
   data_type_t* data_type = ((detail->compile_flags & compile_flag_integer)
      ? &std_data_type[vt_int64] : &std_data_type[vt_float64]
   );
   assign(data_type, data_type);
#endif
   ensure(tkn_numeric_literal);
   return_node();
}
inline_spec string_literal_t* parse_string_literal(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   ensure_non_annex_string();
   make_node(string_literal);
   assign_token();
   ensure(tkn_string_literal);
   return_node();
}
inline_spec regexp_literal_t* parse_regexp_literal(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(regexp_literal);
   assign(flags_length, current_token()->flags_length);
   ensure(tkn_regexp_literal);
   return_node();
}

// ====== PROPERTY NAME ====== //
/*
PropertyName[Yield, Await]:
   LiteralPropertyName
   ComputedPropertyName[?Yield, ?Await]
LiteralPropertyName:
   IdentifierName
   StringLiteral
   NumericLiteral
ComputedPropertyName[Yield, Await]:
   [ AssignmentExpression[+In, ?Yield, ?Await] ]
*/
inline_spec void* parse_computed_property_name(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   expect('['); parse(assignment_expression, NONE, IN); expect(']');
   passon(assignment_expression);
}
inline_spec void* parse_property_name(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(exists_mask(mask_idname)) {
      passon_parsed(identifier_name);
   } else if(exists(tkn_string_literal)) {
      passon_parsed(string_literal);
   } else if(exists(tkn_numeric_literal)) {
      passon_parsed(numeric_literal);
   } else {
      passon_parsed(computed_property_name);
   }
}

// ====== STATEMENT LISTS ====== //
void* parse_import_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_export_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_var_variable_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
/*
StatementList[Yield, Await, Return]:
   StatementListItem[?Yield, ?Await, ?Return]
   StatementList[?Yield, ?Await, ?Return] StatementListItem[?Yield, ?Await, ?Return]
StatementListItem[Yield, Await, Return]:
   Statement[?Yield, ?Await, ?Return]
   Declaration[?Yield, ?Await]
*/
void* parse_statement_list_with_end_token(parse_state_t* state, parse_tree_state_t* tree_state, uint8_t end_token, params_t params)
{
   start_list();
   while(!exists(end_token)) {
      optional_parse(declaration, RET, NONE);
      if(declaration) {
         add_to_list(declaration);
      } else {
         parse(statement);
         add_to_list(statement);
      }
   }
   passon(list_head());
}
void* parse_directive_statement_list_with_end_token(
   parse_state_t* state, parse_tree_state_t* tree_state, uint8_t end_token_id, params_t params
){
   bool look_for_directive = true;
   bool look_for_strict_directive = true;
   start_list();
   while(!exists(end_token_id)) {
      optional_parse(declaration, RET, NONE);
      if(declaration) {
         add_to_list(declaration);
         look_for_directive = false;
      } else {
         token_t const* token = state->parse_token;
         token_t const* const directive_token = token;
         parse(statement);
         add_to_list(statement);
         if(look_for_directive && is_a_directive(token)) {
            // this seems to be a bug in language definition
            // how can a method definition defined in strict mode can be executed in non-strict mode
            //if(!(params & param_flag_strict_mode) && is_use_strict(directive_token)) {
            if(look_for_strict_directive && is_use_strict(directive_token)) {
               validate_strict_mode(); to_strict_mode();
               unwind_for_use_strict(state->parse_token);
               if(!retro_act_strict_mode(state, raw_list_head())) {
                  passon(nullptr);
               }
               look_for_strict_directive = false;
            }
            set_node_type_of(statement, directive);
         } else {
            look_for_directive = false;
         }
      }
   }
   passon(list_head());
}
void* parse_case_clause_statement_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   start_list();
   while(!exists_word(case) && !exists_word(default) && !exists('}')) {
      optional_parse(declaration);
      if(declaration != nullptr) {
         add_to_list(declaration);
      } else {
         parse(statement);
         add_to_list(statement);
      }
   }
   passon(list_head());
}
void* parse_block_statement_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   parse_with_arg('}', statement_list_with_end_token);
   passon(statement_list_with_end_token);
}
/*
ScriptBody:
   StatementList[~Yield, ~Await, ~Return]
*/
inline_spec void* parse_script_body(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   parse_with_arg(tkn_eot, directive_statement_list_with_end_token, YLD|AWT|RET, NONE);
   passon(directive_statement_list_with_end_token);
}
/*
Module:
   ModuleBody_opt
ModuleBody:
   ModuleItemList
ModuleItemList:
   ModuleItem
   ModuleItemList ModuleItem
ModuleItem:
   ImportDeclaration
   ExportDeclaration
   StatementListItem[~Yield, ~Await, ~Return]
*/
inline_spec void* parse_module_body(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   bool look_for_directive = true;
   start_list();
   while(!exists(tkn_eot)) {
      if(exists_word(import) && !exists_ahead('.') && !exists_ahead('(')) {
         parse(import_declaration);
         add_to_list(import_declaration);
      } else if(exists_word(export)) {
         parse(export_declaration);
         add_to_list(export_declaration);
      } else {
         optional_parse(declaration, YLD|AWT|RET, NONE);
         if(declaration) {
            add_to_list(declaration);
            look_for_directive = false;
         } else {
            token_t const* token = state->parse_token;
            token_t const* const directive_token = token;
            parse(statement, YLD|AWT|RET, NONE);
            add_to_list(statement);
            if(look_for_directive && is_a_directive(token)) {
               //(strncmp_impl(token->begin + 1, stringize(use strict), strlen("use strict")) == 0)
               if(!(params & param_flag_strict_mode) && is_use_strict(directive_token)) {
                  validate_strict_mode(); to_strict_mode();
                  unwind_for_use_strict(state->parse_token);
                  if(!retro_act_strict_mode(state, raw_list_head())) {
                     passon(nullptr);
                  }
               }
               set_node_type_of(statement, directive);
            } else {
               look_for_directive = false;
            }
         }
      }
   }
   passon(list_head());
}

// ====== BINDING PATTERNS ====== //
/*
BindingElement[Yield, Await]:
   SingleNameBinding[?Yield, ?Await]
   BindingPattern[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
SingleNameBinding[Yield, Await]:
   BindingIdentifier[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
*/
void* parse_binding_pattern(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_binding_element(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   /*
   make_node(assignment_property);
   if(exists_mask(mask_identifier)) {
      // SingleNameBinding: BindingIdentifier Initializer_opt
      parse(key, identifier);
      assign(flags, 0);
   } else {
      // BindingPattern[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
      parse(key, binding_pattern);
      assign(flags, 0);
   }
   if(optional('=')) {
      parse(value, assignment_expression, NONE, IN);
   } else {
      assign(value, nullptr);
   }
   assign(kind, property_kind_init);
   return_node();
   */
   if(exists_mask(mask_identifier)) {
      // SingleNameBinding: BindingIdentifier Initializer_opt
      save_begin();
      if(exists_word(let) && (params & LEXICAL)) {
         return_token_error(let_in_lexical, current_token(), nullptr);
      }
      parse(binding_identifier);
      assert_lexical_uniqueness(binding_identifier, params & LOOSE, NONE);
      if(params & EXPORT) { assert_export_uniqueness(binding_identifier); }
      if(optional('=')) {
         make_node(binding_assignment);
         assign_begin();
         assign(left, binding_identifier);
         parse(right, assignment_expression, EXPORT|LEXICAL, IN);
         return_node();
      } else {
         passon(binding_identifier);
      }
   } else {
      // BindingPattern[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
      save_begin();
      //parse(binding_pattern, LOOSE, NONE);
      parse(binding_pattern);
      if(optional('=')) {
         make_node(binding_assignment);
         assign_begin();
         assign(left, binding_pattern);
         parse(right, assignment_expression, EXPORT|LEXICAL, IN);
         return_node();
      } else {
         passon(binding_pattern);
      }
   }
}
/*
ObjectBindingPattern[Yield, Await]:
   { }
   { BindingRestProperty[?Yield, ?Await] }
   { BindingPropertyList[?Yield, ?Await] }
   { BindingPropertyList[?Yield, ?Await] , BindingRestProperty[?Yield, ?Await]opt }
BindingRestProperty[Yield, Await]:
   ... BindingIdentifier[?Yield, ?Await]
BindingPropertyList[Yield, Await]:
   BindingProperty[?Yield, ?Await]
   BindingPropertyList[?Yield, ?Await] , BindingProperty[?Yield, ?Await]
BindingProperty[Yield, Await]:
   SingleNameBinding[?Yield, ?Await]
   PropertyName[?Yield, ?Await] : BindingElement[?Yield, ?Await]
SingleNameBinding[Yield, Await]:
   BindingIdentifier[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
*/
void* parse_object_binding_pattern(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(object_pattern);
   start_list();
   ensure('{');
   while(!exists('}')) {
      if(exists(pnct_spread)) {
         // BindingRestProperty
         make_node(rest_element);
         ensure(pnct_spread);
         if(exists_word(let) && (params & LEXICAL)) {
            return_token_error(let_in_lexical, current_token(), nullptr);
         }
         parse(argument, binding_identifier);
         assign(cover_node, nullptr);
         assert_lexical_uniqueness(node->argument, params & LOOSE, NONE);
         if(params & EXPORT) { assert_export_uniqueness(node->argument); }
         add_to_list(completed_node());
         break;
      } else {
         // BindingProperty
         make_node(assignment_property);
         assign(kind, property_kind_init);
         if(exists_mask(mask_identifier) && !exists_ahead(':')) {
            // SingleNameBinding: BindingIdentifier Initializer_opt
            save_begin();
            if(exists_word(let) && (params & LEXICAL)) {
               return_token_error(let_in_lexical, current_token(), nullptr);
            }
            parse(binding_identifier);
            assign(key, binding_identifier);
            assert_lexical_uniqueness(binding_identifier, params & LOOSE, NONE);
            if(params & EXPORT) { assert_export_uniqueness(binding_identifier); }
            assign(flags, property_flag_shorthand);
            if(optional('=')) {
               make_child_node(binding_assignment);
               assign_begin();
               assign(left, binding_identifier);
               parse(right, assignment_expression, EXPORT|LEXICAL, IN);
               assign_to_parent(value, completed_node());
            } else {
               assign(value, binding_identifier);
            }
         } else {
            // PropertyName : BindingElement
            if(exists('[')) {
               assign(flags, property_flag_computed);
            } else {
               assign(flags, flag_none);
            }
            parse(key, property_name);
            expect(':');
            parse(value, binding_element);
         }
         add_to_list(completed_node());
         if(!optional(',')) break;
      }
   }
   assign(has_trailing_comma, false);
   assign(properties, raw_list_head());
   expect('}');
   return_node();
}
/*
ArrayBindingPattern[Yield, Await]:
   [ Elision_opt BindingRestElement[?Yield, ?Await]opt ]
   [ BindingElementList[?Yield, ?Await] ]
   [ BindingElementList[?Yield, ?Await] , Elision_opt BindingRestElement[?Yield, ?Await]opt ]
BindingElementList[Yield, Await]:
   BindingElisionElement[?Yield, ?Await]
   BindingElementList[?Yield, ?Await] , BindingElisionElement[?Yield, ?Await]
BindingElisionElement[Yield, Await]:
   Elision_opt BindingElement[?Yield, ?Await]
BindingRestElement[Yield, Await]:
   ... BindingIdentifier[?Yield, ?Await]
   ... BindingPattern[?Yield, ?Await]
*/
void* parse_binding_rest_element(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(rest_element);
   ensure(pnct_spread);
   if(exists_mask(mask_identifier)) {
      // BindingIdentifier
      if(exists_word(let) && (params & LEXICAL)) {
         return_token_error(let_in_lexical, current_token(), nullptr);
      }
      parse(argument, binding_identifier);
      assert_lexical_uniqueness(node->argument, params & LOOSE, NONE);
      if(params & EXPORT) { assert_export_uniqueness(node->argument); }
   } else {
      // BindingPattern
      parse(argument, binding_pattern);
   }
   assign(cover_node, nullptr);
   return_node();
}
void* parse_array_binding_pattern(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(array_pattern);
   start_list();
   ensure('[');
   while(!exists(']')) {
      // BindingRestElement
      if(exists(',')) {
         add_to_list(nullptr);
      } else if(exists(pnct_spread)) {
         parse(binding_rest_element);
         add_to_list(binding_rest_element);
         break;
      } else {
         // BindingElement
         parse(binding_element);
         add_to_list(binding_element);
      }
      if(!optional(',')) break;
   }
   assign(has_trailing_comma, false);
   assign(elements, raw_list_head());
   expect(']');
   return_node();
}
/*
BindingPattern[Yield, Await]:
   ObjectBindingPattern[?Yield, ?Await]
   ArrayBindingPattern[?Yield, ?Await]
*/
void* parse_binding_pattern(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   //params |= (params & FUNC ? UNIQUE : NONE);
   if(exists('{')) {
      passon_parsed(object_binding_pattern);
   } else if(exists('[')) {
      passon_parsed(array_binding_pattern);
   } else {
      passon(nullptr);
   }
}

// ====== FUNCTIONS ====== //
// ====== FUNCTIONS::FunctionDeclaration ====== //
// ====== FUNCTIONS::FunctionExpression ======= //
/*
UniqueFormalParameters[Yield, Await]:
   FormalParameters[?Yield, ?Await]
FormalParameters[Yield, Await]:
   [empty]
   FunctionRestParameter[?Yield, ?Await]
   FormalParameterList[?Yield, ?Await]
   FormalParameterList[?Yield, ?Await] ,
   FormalParameterList[?Yield, ?Await] , FunctionRestParameter[?Yield, ?Await]
FormalParameterList[Yield, Await]:
   FormalParameter[?Yield, ?Await]
   FormalParameterList[?Yield, ?Await] , FormalParameter[?Yield, ?Await]
FunctionRestParameter[Yield, Await]:
   BindingRestElement[?Yield, ?Await]
FormalParameter[Yield, Await]:
   BindingElement[?Yield, ?Await]
*/
void* parse_formal_parameter(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   passon_parsed(binding_element);
}
void* parse_formal_parameter_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params = params | FORMAL;
   if(params & STRICT) params |= UNIQUE;
   //params = params | FORMAL | LOOSE;
   start_list();
   while(!exists(')')) {
      if(exists_mask(mask_identifier) && !exists_ahead('=')) {
         parse(binding_identifier);
         assert_lexical_uniqueness(binding_identifier, params & LOOSE, NONE);
         add_to_list(binding_identifier);
      } else {
         // if any of the formal parameters is a binding pattern switch to
         // unique formal parameter list; before proceeding though ensure all
         // the existing formal parameters are unique
         if(!(params & UNIQUE)) { assert_unique_scope(); params |= UNIQUE; }
         state->current_scope_list_node->scope->flags |= scope_flag_non_strict;
         if(exists(pnct_spread)) {
            parse(binding_rest_element);
            add_to_list(binding_rest_element);
            if(!exists(')')) {
               return_error(middle_rest, nullptr);
            }
            break;
         } else {
            parse(formal_parameter);
            add_to_list(formal_parameter);
         }
      }
      if(!optional(',')) break;
   }
   passon(list_head());
}
void* parse_formal_parameters(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   passon_parsed(formal_parameter_list);
}
void* parse_unique_formal_parameters(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   passon_parsed(formal_parameters, NONE, UNIQUE);
}
/*
FunctionStatementList[Yield, Await]:
   StatementList[?Yield, ?Await, +Return]opt
*/
inline_spec void* parse_function_statement_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   parse_with_arg('}', directive_statement_list_with_end_token, NONE, RET);
   passon(directive_statement_list_with_end_token);
}
/*
FunctionBody[Yield, Await]:
   FunctionStatementList[?Yield, ?Await]
*/
inline_spec void* parse_function_body(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(function_body);
   list_parse(body, function_statement_list);
   return_node();
}
inline_spec void* parse_function_body_container(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   uint32_t saved_semantic_flags = state->semantic_flags;
   state->semantic_flags = flag_none;
   make_node(block_statement);
   expect('{');
      list_parse(body, function_statement_list);
      if(params & EXPR) disable_pending_regexp_context();
   expect('}');
   state->semantic_flags = saved_semantic_flags;
   return_node();
}
/*
HoistableDeclaration[Yield, Await, Default]:
   FunctionDeclaration[?Yield, ?Await, ?Default]
   GeneratorDeclaration[?Yield, ?Await, ?Default]
   AsyncFunctionDeclaration[?Yield, ?Await, ?Default]
   AsyncGeneratorDeclaration[?Yield, ?Await, ?Default]
FunctionDeclaration[Yield, Await, Default]:
   function BindingIdentifier[?Yield, ?Await]
      ( FormalParameters[~Yield, ~Await] )
      { FunctionBody[~Yield, ~Await] }
   [+Default] function
      ( FormalParameters[~Yield, ~Await] )
      { FunctionBody[~Yield, ~Await] }
GeneratorDeclaration[Yield, Await, Default]:
   function * BindingIdentifier[?Yield, ?Await]
      ( FormalParameters[+Yield, ~Await] ) { GeneratorBody }
   [+Default] function *
      ( FormalParameters[+Yield, ~Await] ) { GeneratorBody }
AsyncFunctionDeclaration[Yield, Await, Default]:
   async [no LineTerminator here] function BindingIdentifier[?Yield, ?Await]
      ( FormalParameters[~Yield, +Await] ) { AsyncFunctionBody }
   [+Default] async [no LineTerminator here] function
      ( FormalParameters[~Yield, +Await] ) { AsyncFunctionBody }
AsyncGeneratorDeclaration[Yield, Await, Default]:
   async [no LineTerminator here] function * BindingIdentifier[?Yield, ?Await]
      ( FormalParameters[+Yield, +Await] ) { AsyncGeneratorBody }
   [+Default] async [no LineTerminator here] function *
      ( FormalParameters[+Yield, +Await] ) { AsyncGeneratorBody }
GeneratorBody:
   FunctionBody[+Yield, ~Await]
AsyncFunctionBody:
   FunctionBody[~Yield, +Await]
AsyncGeneratorBody:
   FunctionBody[+Yield, +Await]
*/
void* parse_hoistable_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params_t saved_params = params;
   params = make_params(DERIVED|CLASS|METHOD|CONSTR|UNIQUE|EXPORT|PARAM|EXPR, FUNC);
   params_t add_params = 0;
   uint8_t function_flags = flag_none;
   save_begin();
#ifdef EXTENSIONS
   uint8_t operator_id = 0;
#endif
   if(!(params & param_flag_vanilla_function)) {
      if(exists_word(async)) {
         if(exists_newline_ahead() || !exists_ahead_word(function)) {
            passon(nullptr);
         }
         ensure_word(async);
         function_flags |= function_flag_async;
         add_params |= param_flag_await;
      }
   }
   make_node(function_declaration);
   assign_begin();
   expect_word(function);
   if(!(params & param_flag_vanilla_function)) {
      if(optional('*')) {
         function_flags |= function_flag_generator;
         add_params |= param_flag_yield;
      }
   }
   if((params & param_flag_default) && !exists_mask(mask_identifier)) {
      assign(id, nullptr);
#ifdef EXTENSIONS
   } else if(exists_mask(mask_binary_ops)) {
      assign(id, nullptr);
      operator_id = current_token()->id;
      assign(operator_id, operator_id);
      function_flags |= function_flag_operator;
      ensure_mask(mask_binary_ops);
#endif
   } else {
      parse(id, binding_identifier);
      scope_t const* const scope = state->current_scope_list_node->scope;
      uint8_t binding_flag = (
         (scope->flags & (scope_flag_script | scope_flag_function)) ? LOOSE :
         (function_flags == NONE) && allow_annex() ? binding_flag_function: NONE
      );
      assert_lexical_uniqueness(node->id, binding_flag, symbol_flag_function_id);
      //assert_lexical_uniqueness(node->id, LOOSE);
      if(saved_params & EXPORT) { assert_export_uniqueness(node->id); }
   }
   scope_list_node_t* scope_list_node = new_scope(state, scope_flag_function | scope_flag_hoisting, node->id);
   expect('(');
      list_parse(params, formal_parameters, YLD|AWT|VFUN, add_params|LOOSE);
   expect(')');
#ifdef EXTENSIONS
   if(optional(':')) {
      parse(return_type_identifier, type_identifier);
      assign(return_type, get_type(state, node->return_type_identifier));
   } else {
      assign(return_type, nullptr);
      assign(return_type_identifier, nullptr);
   }
   if(function_flags & function_flag_operator) {
      insert_operator_overload(state, operator_id, node);
   }
#endif
   //expect('{'); parse(body, function_body, YLD|AWT, flags); expect('}');
   parse(body, function_body_container, YLD|AWT|VFUN, add_params);
   assign(flags, function_flags);
   end_scope(state);
#ifdef COMPILER
   node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   return_node();
}
/*
FunctionExpression:
   function BindingIdentifier[~Yield, ~Await]opt
      ( FormalParameters[~Yield, ~Await] )
      { FunctionBody[~Yield, ~Await] }
GeneratorExpression:
   function * BindingIdentifier[+Yield, ~Await]opt
      ( FormalParameters[+Yield, ~Await] ) { GeneratorBody }
AsyncFunctionExpression:
   async [no LineTerminator here] function
      ( FormalParameters[~Yield, +Await] ) { AsyncFunctionBody }
   async [no LineTerminator here] function BindingIdentifier[~Yield, +Await]
      ( FormalParameters[~Yield, +Await] ) { AsyncFunctionBody }
AsyncGeneratorExpression:
   async [no LineTerminator here] function * BindingIdentifier[+Yield, +Await]opt
      ( FormalParameters[+Yield, +Await] ) { AsyncGeneratorBody }
*/
void* parse_function_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params = make_params(DERIVED|CLASS|METHOD|CONSTR|UNIQUE|PARAM, FUNC|EXPR);
   make_node(function_expression);
   params_t add_params = flag_none;
   uint8_t function_flags = flag_none;
   if(optional_word(async)) {
      function_flags |= function_flag_async;
      add_params |= param_flag_await;
   }
   expect_word(function);
   if(optional('*')) {
      function_flags |= function_flag_generator;
      add_params |= param_flag_yield;
   }
   if(!exists('(')) {
      parse(id, binding_identifier, YLD|AWT, add_params);
   } else {
      assign(id, nullptr);
   }
   scope_list_node_t* scope_list_node = new_scope(state, scope_flag_function | scope_flag_hoisting, node->id);
   expect('(');
      list_parse(params, formal_parameters, YLD|AWT|COV_CALL, add_params|LOOSE);
   expect(')');
   //expect('{'); list_parse(body, function_body); expect('}');
   //list_parse(body, function_body_container);
   parse(body, function_body_container, YLD|AWT|COV_CALL, add_params);
   assign(flags, function_flags);
   end_scope(state);
#ifdef COMPILER
   node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   return_node();
}
// ====== FUNCTIONS::MethodDefinition ====== //
/*
PropertySetParameterList:
   FormalParameter[~Yield, ~Await]
*/
inline_spec void* parse_property_set_parameter_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(!exists_mask(mask_identifier) || exists_ahead('=')) {
      state->current_scope_list_node->scope->flags |= scope_flag_non_strict;
   }
   start_list(); parse(formal_parameter);
   add_to_list(formal_parameter);
   passon(list_head());
}
/*
MethodDefinition[Yield, Await]:
   PropertyName[?Yield, ?Await] ( UniqueFormalParameters[~Yield, ~Await] ) { FunctionBody[~Yield, ~Await] }
   GeneratorMethod[?Yield, ?Await]
   AsyncMethod[?Yield, ?Await]
   AsyncGeneratorMethod[?Yield, ?Await]
   get PropertyName[?Yield, ?Await] ( ) { FunctionBody[~Yield, ~Await] }
   set PropertyName[?Yield, ?Await] ( PropertySetParameterList ) { FunctionBody[~Yield, ~Await] }
GeneratorMethod[Yield, Await]:
   * PropertyName[?Yield, ?Await]
      ( UniqueFormalParameters[+Yield, ~Await] ) { GeneratorBody }
AsyncMethod[Yield, Await]:
   async [no LineTerminator here] PropertyName[?Yield, ?Await]
      ( UniqueFormalParameters[~Yield, +Await] ) { AsyncFunctionBody }
AsyncGeneratorMethod[Yield, Await]:
   async [no LineTerminator here] * PropertyName[?Yield, ?Await]
      ( UniqueFormalParameters[+Yield, +Await] ) { AsyncGeneratorBody }
GeneratorBody:
   FunctionBody[+Yield, ~Await]
AsyncFunctionBody:
   FunctionBody[~Yield, +Await]
AsyncGeneratorBody:
   FunctionBody[+Yield, +Await]
PropertySetParameterList:
   FormalParameter[~Yield, ~Await]
*/
// Partial production
// ( UniqueFormalParameters[Yield, Await] ) { FunctionBody[?Yield, ?Await] }
inline_spec void* parse_method_function(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params |= (FUNC | METHOD);
   make_node(function_expression);
   assign(id, nullptr);
   scope_list_node_t* scope_list_node = new_scope(state, scope_flag_function | scope_flag_hoisting, nullptr);
   ensure('('); list_parse(params, unique_formal_parameters); expect(')');
   //expect('{'); list_parse(body, function_body); expect('}');
   //list_parse(body, function_body_container);
   parse(body, function_body_container);
   assign(flags, flag_none);
   end_scope(state);
#ifdef COMPILER
   node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   return_node();
}
/*
inline_spec void* parse_method_function(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(exists('(')) passon_enparsed(method_function);
   passon(nullptr);
}
*/
method_definition_t* parse_method_only_definition(parse_state_t* state, parse_tree_state_t* tree_state, uint8_t state_flags, params_t params)
{
   params = make_params(UNIQUE|PARAM|EXPR|COV_CALL, METHOD|FUNC);
   bool is_get_set = false, is_get = false, is_set = false;
   uint8_t property_kind = property_kind_method;
   uint8_t property_flags = property_flag_method;
   uint8_t function_flags = flag_none;
   params_t param_flags = flag_none;
   make_node(method_definition);
   if(optional_word(async)) {
      function_flags |= function_flag_async;
      param_flags |= param_flag_await;
      if(optional('*')) function_flags |= function_flag_generator;
   } else if(optional('*')) {
      function_flags |= function_flag_generator;
      param_flags |= param_flag_yield;
   } else {
      if(exists_word(get)) {
         is_get_set = is_get = true;
         property_kind = property_kind_get;
         property_flags &= ~property_flag_method;
         property_flags |= method_flag_special; next();
      } else if(exists_word(set)) {
         is_get_set = is_set = true;
         property_kind = property_kind_set;
         property_flags &= ~property_flag_method;
         property_flags |= method_flag_special; next();
      }
   }
   if(exists('[')) property_flags |= property_flag_computed;
   parse(key, property_name);
   if((params & CLASS) && !(property_flags & property_flag_computed)) {
      if(state_flags & method_flag_static){
         if(property_key_is(prototype, node)){
            return_token_error(static_prototype, previous_token(), nullptr);
         }
      } else if(property_key_is(constructor, node)) {
         return_token_error(invalid_constructor, previous_token(), nullptr);
      }
   }
   {
      scope_list_node_t* scope_list_node = new_scope(state, scope_flag_function | scope_flag_hoisting, nullptr);
      make_child_node(function_expression);
      assign(id, nullptr);
      expect('(');
      if(!is_get_set) {
         list_parse(params, unique_formal_parameters, YLD|AWT, param_flags);
      } else {
         if(is_set) {
            list_parse(params, property_set_parameter_list, YLD|AWT, param_flags);
         } else {
            assign(params, nullptr);
         }
      }
      expect(')');
      //expect('{'); list_parse(body, function_body, YLD|AWT, flags); expect('}');
      //list_parse(body, function_body_container, YLD|AWT, param_flags);
      parse(body, function_body_container, YLD|AWT, param_flags);
      assign(flags, function_flags);
      end_scope(state);
#ifdef COMPILER
      node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
      assign_to_parent(value, completed_node());
   }
   assign(kind, property_kind);
   assign(flags, property_flags);
   return_node();
}
method_definition_t* parse_method_definition(parse_state_t* state, parse_tree_state_t* tree_state, uint8_t state_flags, params_t params)
{
   bool computed = false;
   //[NOTE] this criterion must be subject to review with grammar changes
   //    this criterion is valid as of ECMA2020
   if((computed = exists('[')) || exists_ahead('('))
   {
      // MethodDefinition[Yield, Await]:
      //    PropertyName[?Yield, ?Await]
      //       ( UniqueFormalParameters[~Yield, ~Await] )
      //       { FunctionBody[~Yield, ~Await] }
      make_node(method_definition);
      uint8_t flags = (computed ? property_flag_computed : flag_none);
      uint8_t kind = property_kind_method;
      parse(key, property_name);
      if((params & CLASS) && !computed){
         if(state_flags & method_flag_static){
            if(property_key_is(prototype, node)) {
               return_token_error(static_prototype, previous_token(), nullptr);
            }
         } else if(property_key_is(constructor, node)) {
            if(state_flags & method_flag_constructor) {
               return_token_error(duplicate_constructor, previous_token(), nullptr);
            }
            kind = property_kind_constructor;
            flags |= method_flag_constructor;
            params |= param_flag_constructor;
         }
      }
      if(exists('(')) {
         parse(value, method_function, YLD|AWT|EXPR|COV_CALL, NONE);
         flags |= property_flag_method;
      } else {
         passon(nullptr);
      }
      assign(kind, kind);
      assign(flags, flags);
      return_node();
   }
   parse_with_arg(state_flags, method_only_definition);
   passon(method_only_definition);
}
// ====== FUNCTIONS::YieldExpression ====== //
/*
YieldExpression[In, Await]:
   yield
   yield [no LineTerminator here] AssignmentExpression[?In, +Yield, ?Await]
   yield [no LineTerminator here] * AssignmentExpression[?In, +Yield, ?Await]
*/
void* parse_yield_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   uint8_t yield_flags = flag_none;
   make_node(yield_expression)
   scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
   if(!hoisting_scope->first_yield_or_await) hoisting_scope->first_yield_or_await = node;
   enable_pending_regexp_context();
   expect_word(yield);
   if(!exists_newline()) {
      if(optional('*')) {
         yield_flags |= yield_flag_delegate;
         parse(argument, assignment_expression, NONE, YLD);
      } else {
         optional_parse(assignment_expression, NONE, YLD);
         assign(argument, assignment_expression);
      }
   } else {
      assign(argument, nullptr);
   }
   assign(flags, yield_flags);
   return_node();
}

// ====== CLASSES ====== //
/*
ClassDeclaration[Yield, Await, Default]:
   class BindingIdentifier[?Yield, ?Await] ClassTail[?Yield, ?Await]
   [+Default] class ClassTail[?Yield, ?Await]
ClassExpression[Yield, Await]:
   class BindingIdentifier[?Yield, ?Await]opt ClassTail[?Yield, ?Await]
ClassTail[Yield, Await]:
   ClassHeritage[?Yield, ?Await]opt { ClassBody[?Yield, ?Await]opt }
ClassHeritage[Yield, Await]:
   extends LeftHandSideExpression[?Yield, ?Await]
ClassBody[Yield, Await]:
   ClassElementList[?Yield, ?Await]
ClassElementList[Yield, Await]:
   ClassElement[?Yield, ?Await]
   ClassElementList[?Yield, ?Await] ClassElement[?Yield, ?Await]
ClassElement[Yield, Await]:
   MethodDefinition[?Yield, ?Await]
   static MethodDefinition[?Yield, ?Await]
   ;
*/
void* parse_class_element_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   start_list();
   uint8_t state_flags = 0;
   while(!exists('}')) {
      if(optional(';')) continue;
      uint8_t method_flags = 0;
      save_begin();
      // static is a valid method name
      if(exists_word(static) && !exists_ahead('(')){
         ensure_word(static);
         method_flags = method_flag_static;
      }
      parse_with_arg(method_flags | state_flags, method_definition);
      node_as(method_definition, method_definition, md);
      state_flags |= (md->flags & method_flag_constructor);
      md->begin = begin;
      md->location->begin = begin_position;
      md->flags |= method_flags;
      add_to_list(method_definition);
   }
   passon(list_head());
}
void* parse_class_body(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(class_body);
   list_parse(body, class_element_list);
   return_node();
}
void* parse_class_body_container(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(class_body);
   expect('{');
      list_parse(body, class_element_list, NONE, CLASS);
      if(params & EXPR) disable_pending_regexp_context();
   expect('}');
   return_node();
}
void* parse_class_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(class_declaration);
   params |= STRICT;
   expect_word(class);
   if((params & param_flag_default) && !exists_mask(mask_identifier)) {
      assign(id, nullptr);
   } else {
      parse(id, binding_identifier);
      assert_lexical_uniqueness(node->id, NONE, NONE);
      if(params & EXPORT) { assert_export_uniqueness(node->id); }
   }
   if(optional_word(extends)) {
      parse(super_class, lhs_expression);
      params |=  DERIVED;
   } else {
      assign(super_class, nullptr);
   }
   //expect('{'); parse(body, class_body); expect('}');
   parse(body, class_body_container, EXPORT|EXPR|COV_CALL, NONE);
   return_node();
}
void* parse_class_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(class_expression);
   params |= STRICT;
   expect_word(class);
   if(exists_mask(mask_identifier)) {
      parse(id, binding_identifier);
   } else {
      assign(id, nullptr);
   }
   if(optional_word(extends)) {
      parse(super_class, lhs_expression);
      params |=  DERIVED;
   } else {
      assign(super_class, nullptr);
   }
   //expect('{'); parse(body, class_body); expect('}');
   parse(body, class_body_container, COV_CALL, EXPR);
   return_node();
}

// ====== MODULES ====== //
/*
ImportDeclaration:
   import ImportClauseFromClause ;
   import ModuleSpecifier ;
ImportClause:
   ImportedDefaultBinding
   NameSpaceImport
   NamedImports
   ImportedDefaultBinding , NameSpaceImport
   ImportedDefaultBinding , NamedImports
ImportedDefaultBinding:
   ImportedBinding
NameSpaceImport:
   * as ImportedBinding
NamedImports:
   { }
   { ImportsList }
   { ImportsList , }
FromClause:
   fromModuleSpecifier
ImportsList:
   ImportSpecifier
   ImportsList , ImportSpecifier
ImportSpecifier:
   ImportedBinding
   IdentifierName as ImportedBinding
ModuleSpecifier:
   StringLiteral
ImportedBinding:
   BindingIdentifier[~Yield, ~Await]
*/
void* parse_import_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(import_declaration);
   ensure_word(import);
   if(exists(tkn_string_literal)) {
      assign(specifiers, nullptr);
   } else {
      start_list();
      // parse the default specifier if exists
      bool has_specifiers = true;
      if(exists_mask(mask_identifier)) {
         make_node(import_default_specifier);
         parse(binding_identifier, YLD|AWT, NONE);
         assert_lexical_uniqueness(binding_identifier, NONE, NONE);
         assign(local, binding_identifier);
         add_to_list(completed_node());
         has_specifiers = optional(',');
      }
      if(has_specifiers) {
         if(exists('*')) {
            make_node(import_namespace_specifier);
            ensure('*'); expect_word(as);
            parse(binding_identifier, YLD|AWT, NONE);
            assert_lexical_uniqueness(binding_identifier, NONE, NONE);
            assign(local, binding_identifier);
            add_to_list(completed_node());
         } else if(exists('{')) {
            ensure('{');
            while(!exists('}')) {
               make_node(import_specifier);
               if(exists_ahead_word(as)) {
                  parse(imported, identifier_name);
                  ensure_word(as);
                  parse(binding_identifier, YLD|AWT, NONE);
                  assert_lexical_uniqueness(binding_identifier, NONE, NONE);
                  assign(local, binding_identifier);
               } else {
                  parse(binding_identifier, YLD|AWT, NONE);
                  assert_lexical_uniqueness(binding_identifier, NONE, NONE);
                  assign(imported, binding_identifier);
                  assign(local, binding_identifier);
               }
               add_to_list(completed_node());
               if(!optional(',')) break;
            }
            expect('}');
         } else {
            return_error(missing_import_specifier, nullptr);
         }
      }
      assign(specifiers, raw_list_head());
      expect_word(from);
   }
   parse(source, string_literal);
   parse_semicolon();
   return_node();
}
/*
ExportDeclaration:
   export ExportFromClause FromClause ;
   export NamedExports ;
   export VariableStatement[~Yield, ~Await]
   export Declaration[~Yield, ~Await]
   export default HoistableDeclaration[~Yield, ~Await, +Default]
   export default ClassDeclaration[~Yield, ~Await, +Default]
   export default [lookahead ∉ { function, async [no LineTerminator here] function, class }]
      AssignmentExpression[+In, ~Yield, ~Await];
ExportFromClause:
   *
   * as IdentifierName
   NamedExports
NamedExports:
   { }
   { ExportsList }
   { ExportsList , }
ExportsList:
   ExportSpecifier
   ExportsList , ExportSpecifier
ExportSpecifier:
   IdentifierName
   IdentifierName as IdentifierName
*/
void* parse_export_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   ensure_word(export);
   if(optional('*')) {
      make_node(export_all_declaration);
      assign_begin();
      if(optional_word(as)) {
         if(exists_word(default)) {
            if(state->has_default_export) {
               return_error(duplicate_default_export, nullptr);
            }
            parse(exported, identifier_name);
            state->has_default_export = true;
         } else {
            parse(exported, identifier_name);
            assert_export_uniqueness(node->exported);
         }
      } else {
         assign(exported, nullptr);
      }
      expect_word(from);
      parse(source, string_literal);
      parse_semicolon();
      return_node();
   } else if(optional('{')) {
      make_node(export_named_declaration);
      assign_begin();
      start_list();
      symbol_list_t* reference_list = nullptr;
      while(!exists('}')) {
         make_node(export_specifier);
         parse(identifier_name);
         if(optional_word(as)) {
            assign(local, identifier_name);
            if(exists_word(default)) {
               if(state->has_default_export) {
                  return_error(duplicate_default_export, nullptr);
               }
               parse(exported, identifier_name);
               state->has_default_export = true;
            } else {
               parse(exported, identifier_name);
               assert_export_uniqueness(node->exported);
            }
         } else {
            assign(exported, identifier_name);
            assign(local, identifier_name);
            assert_export_uniqueness(node->exported);
         }
         add_symbol_to_list(state, &reference_list, reference_list, (identifier_t*)(node->local), NONE, NONE);
         add_to_list(completed_node());
         if(!optional(',')) break;
      }
      assign(specifiers, raw_list_head());
      expect('}');
      if(optional_word(from)) {
         parse(source, string_literal);
      } else {
         if(!state->export_reference_list) {
            state->export_reference_list = reference_list;
         } else {
            state->export_reference_list->tail->next = reference_list->head;
            state->export_reference_list->tail = reference_list->tail;
         }
         assign(source, nullptr);
      }
      assign(declaration, nullptr);
      parse_semicolon();
      return_node();
   } else if(optional_word(default)) {
      if(state->has_default_export) {
         return_error(duplicate_default_export, nullptr);
      }
      make_node(export_default_declaration);
      assign_begin();
      void* default_declaration = nullptr;
      if(exists_word(function) || exists_word(async)) {
         optional_parse(hoistable_declaration, YLD|AWT, DEF);
         default_declaration = hoistable_declaration;
      } else if(exists_word(class)) {
         optional_parse(class_declaration, YLD|AWT, DEF);
         default_declaration = class_declaration;
      }
      if(default_declaration == nullptr){
         parse(assignment_expression, YLD|AWT, IN);
         parse_semicolon();
         default_declaration = assignment_expression;
      }
      assign(declaration, default_declaration);
      state->has_default_export = 1;
      return_node();
   } else {
      make_node(export_named_declaration);
      assign_begin();
      if(exists_word(var)) {
         parse(declaration, var_variable_statement, YLD|AWT, EXPORT);
      } else {
         parse(declaration, declaration, YLD|AWT, EXPORT);
      }
      assign(specifiers, nullptr);
      assign(source, nullptr);
      return_node();
   }
}

// ====== ARRAY LITERAL ====== //
/*
ArrayLiteral[Yield, Await]:
   [ Elision_opt ]
   [ ElementList[?Yield, ?Await] ]
   [ ElementList[?Yield, ?Await] , Elision_opt ]
ElementList[Yield, Await]:
   Elision_opt AssignmentExpression[+In, ?Yield, ?Await]
   Elision_opt SpreadElement[?Yield, ?Await]
   ElementList[?Yield, ?Await] , Elision_opt AssignmentExpression[+In, ?Yield, ?Await]
   ElementList[?Yield, ?Await] , Elision_opt SpreadElement[?Yield, ?Await]
Elision:
   ,
   Elision ,
SpreadElement[Yield, Await]:
   ... AssignmentExpression[+In, ?Yield, ?Await]
*/
void* parse_spread_element(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(spread_element);
   ensure(pnct_spread);
   parse(argument, assignment_expression, NONE, IN);
   assign(cover_node, nullptr);
   return_node();
}
void* parse_array_literal(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(array_expression);
   start_list();
   ensure('[');
   bool has_trailing_comma = false;
#ifdef EXTENSIONS
   //[BUG][IMPROVE] currently only allows 32 elements in an array
   int shift = 0;
   uint64_t operators = 0;
   data_type_t const* data_type = nullptr;
#endif
   while(!exists(']')) {
      if(!exists(',')) {
         if(exists(pnct_spread)) {
            parse(spread_element);
            add_to_list(spread_element);
         } else {
            parse(assignment_expression, NONE, IN);
            add_to_list(assignment_expression);
#ifdef EXTENSIONS
            parse_node_t* parse_node = assignment_expression;
            if(data_type == nullptr) {
               data_type = parse_node->data_type;
            } else if(parse_node->data_type != data_type) {
               data_type = &std_data_type[vt_any];
            }
#endif
         }
      } else {
         add_to_list(nullptr);
      }
#ifndef EXTENSIONS
      if(!(has_trailing_comma = optional(','))) break;
#else
      if(optional(','));
      else if(optional('#')) operators |= 0x01 << shift;
      else if(optional(';')) operators |= 0x02 << shift;
      else break;
      shift += 2;
#endif
   };
   expect(']');
   assign(elements, raw_list_head());
   assign(has_trailing_comma, has_trailing_comma);
#ifdef EXTENSIONS
   assign(operators, operators);
   data_type = get_template_instance(state, &std_data_type[vt_matrix], &data_type);
   assign(data_type, data_type);
   printf("array type: "); print_type(data_type, true); printf("\n");
#endif
   return_node();
}

// ====== OBJECT LITERAL ====== //
/*
ObjectLiteral[Yield, Await]:
   { }
   { PropertyDefinitionList[?Yield, ?Await] }
   { PropertyDefinitionList[?Yield, ?Await] , }
PropertyDefinitionList[Yield, Await]:
   PropertyDefinition[?Yield, ?Await]
   PropertyDefinitionList[?Yield, ?Await] , PropertyDefinition[?Yield, ?Await]
PropertyDefinition[Yield, Await]:
   IdentifierReference[?Yield, ?Await]
   CoverInitializedName[?Yield, ?Await]
   PropertyName[?Yield, ?Await] : AssignmentExpression[+In, ?Yield, ?Await]
   MethodDefinition[?Yield, ?Await]
   ... AssignmentExpression[+In, ?Yield, ?Await]
CoverInitializedName[Yield, Await]:
   IdentifierReference[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]
Initializer[In, Yield, Await]:
   = AssignmentExpression[?In, ?Yield, ?Await]
*/
void* parse_object_literal(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(object_expression);
   start_list();
   ensure('{');
   bool has_trailing_comma = false;
   bool has_prototype = false;
   while(!exists('}')) {
      if(exists(pnct_spread)) {
         // ... AssignmentExpression[+In, ?Yield, ?Await]
         parse(spread_element);
         add_to_list(spread_element);
      } else if(exists_ahead(':') || exists_ahead('(') || exists('[')) {
         // first resolve all productions that start with Identifier or IdentifierName
         //[NOTE] this criterion must be subject to review with grammar changes
         //    this criterion is valid as of ECMA2020
         //
         // PropertyDefinitionList[Yield, Await]:
         //    PropertyName[?Yield, ?Await]
         //       : AssignmentExpression[+In, ?Yield, ?Await]
         // MethodDefinition[Yield, Await]:
         //    PropertyName[?Yield, ?Await]
         //       ( UniqueFormalParameters[~Yield, ~Await] )
         //       { FunctionBody[~Yield, ~Await] }
         make_node(property);
         bool is_computed = exists('[');
         uint8_t flags = (is_computed ? property_flag_computed: flag_none);
         parse(key, property_name);
         if(optional(':')) {
            if(!is_computed && (params & param_flag_annex) && property_key_is(__proto__, node)) {
               if(has_prototype) { return_node_error(duplicate_prototype, node->key, nullptr); }
               has_prototype = true;
            }
            parse(value, assignment_expression, NONE, IN);
         } else if(exists('(')) {
            parse(value, method_function, YLD|AWT|DERIVED|CLASS|CONSTR|PARAM|EXPR|COV_CALL, NULL);
            flags |= property_flag_method;
         } else {
            passon(nullptr);
         }
         assign(kind, property_kind_init);
         assign(flags, flags);
         add_to_list(completed_node());
      } else if(exists_ahead(',') || exists_ahead('}')) {
         //[NOTE] this criterion must be subject to review with grammar changes
         //    this criterion is valid as of ECMA2020
         // IdentifierReference
         make_node(property);
         parse(identifier_reference);
         assign(key, identifier_reference);
         assign(value, identifier_reference);
         assign(kind, property_kind_init);
         assign(flags, property_flag_shorthand);
         add_to_list(completed_node());
      //} else if(exists_ahead('=') && (params & cover_flag_initializer)) {
      //} else if(exists_ahead('=')) {
      } else if(exists_ahead('=')) {
         save_begin();
         make_node(property);
         assign(kind, property_kind_init);
         parse(identifier_reference);
         assign(key, identifier_reference);
         assign(flags, property_flag_shorthand);
         {
            make_child_node(initialized_name);
            assign_begin();
            assign(left, identifier_reference);
            if(!is_a_binding_identifier(state, node->left, params)) return nullptr;
            ensure('=');
            parse(right, assignment_expression, NONE, IN);
            assign_to_parent(value, completed_node());
            add_to_cover_list(node);
         }
         add_to_list(completed_node());
      } else {
         parse_with_arg(NONE, method_only_definition, DERIVED|CLASS|CONSTR|PARAM|EXPR|COV_CALL, NONE);
         set_node_type_of(method_only_definition, property);
         node_as(property, method_only_definition, property);
         if(!(property->flags & method_flag_special)) {
            property->kind = property_kind_init;
         }
         add_to_list(method_only_definition);
      }
      if(!(has_trailing_comma = optional(','))) break;
   };
   disable_pending_regexp_context();
   expect('}');
   assign(properties, raw_list_head());
   assign(has_trailing_comma, has_trailing_comma);
   return_node();
}

/*
Template::
   NoSubstitutionTemplate
   TemplateHead
NoSubstitutionTemplate::
   ` TemplateCharacters_opt `
TemplateHead::
   ` TemplateCharacters_opt $ {
TemplateSubstitutionTail::
   TemplateMiddle
   TemplateTail
TemplateMiddle::
   } TemplateCharacters_opt $ {
TemplateTail::
   } TemplateCharacters_opt `
TemplateCharacters::
   TemplateCharacter TemplateCharacters_opt
TemplateCharacter::
   $[lookahead ≠ {]
   \ EscapeSequence
   \ NotEscapeSequence
   LineContinuation
   LineTerminatorSequence
   SourceCharacter but not one of ` or \ or $ or LineTerminator
NotEscapeSequence::
   0 DecimalDigit
   DecimalDigit but not 0
   x [lookahead ∉ HexDigit]
   x HexDigit[lookahead ∉ HexDigit]
   u [lookahead ∉ HexDigit][lookahead ≠ {]
   u HexDigit[lookahead ∉ HexDigit]
   u HexDigit HexDigit[lookahead ∉ HexDigit]
   u HexDigit HexDigit HexDigit[lookahead ∉ HexDigit]
   u { [lookahead ∉ HexDigit]
   u { NotCodePoint [lookahead ∉ HexDigit]
   u { CodePoint [lookahead ∉ HexDigit][lookahead ≠ }]
NotCodePoint::
   HexDigits[~Sep] but only if MV of HexDigits > 0x10FFFF
CodePoint::
   HexDigits[~Sep] but only if MV of HexDigits ≤ 0x10FFFF

TemplateLiteral[Yield, Await, Tagged]:
   NoSubstitutionTemplate
   SubstitutionTemplate[?Yield, ?Await, ?Tagged]
SubstitutionTemplate[Yield, Await, Tagged]:
   TemplateHeadExpression[+In, ?Yield, ?Await] TemplateSpans[?Yield, ?Await, ?Tagged]
TemplateSpans[Yield, Await, Tagged]:
   TemplateTail
   TemplateMiddleList[?Yield, ?Await, ?Tagged] TemplateTail
TemplateMiddleList[Yield, Await, Tagged]:
   TemplateMiddleExpression[+In, ?Yield, ?Await]
   TemplateMiddleList[?Yield, ?Await, ?Tagged] TemplateMiddleExpression[+In, ?Yield, ?Await]
*/
void* parse_template_literal(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(template_literal);
   //start_list();
   start_named_list(quasis);
   start_named_list(expressions);
   ensure('`');
   while(true) {
      save_begin();
      token_t const* const token = current_token();
      ensure(tkn_template_string);
      bool is_tail = exists('`');
      make_node(template_element);
      assign_begin();
      //assign_token(); //[REVIEW] does not work
      node->compiled_string = token->detail;
      if(token->detail != nullptr) {
         compiled_string_t* compiled_string = (compiled_string_t*)(token->detail);
         if((compiled_string->compile_flags & compile_flag_not_escape) &&
            !(params & TAG)
         ){
            return_compiled_error(compiled_string, nullptr);
         }
      }
      //assign(token, token);
      assign(flags, (is_tail ? template_flag_tail : flag_none));
      //add_to_list(completed_node());
      add_to_named_list(quasis, completed_node());
      if(is_tail) break;
      if(optional('$')) {
         expect('{'); parse(expression); expect('}');
         //add_to_list(expression);
         add_to_named_list(expressions, expression);
      } else {
         passon(nullptr);
      }
   }
   //assign(elements, raw_list_head());
   assign(quasis, raw_named_list_head(quasis));
   assign(expressions, raw_named_list_head(expressions));
   expect('`');
   return_node();
}

/*
[List]:
   ElementList[Yield, Await]:
      Elision_opt AssignmentExpression[+In, ?Yield, ?Await]
      Elision_opt SpreadElement[?Yield, ?Await]
      ElementList[?Yield, ?Await] , Elision_opt AssignmentExpression[+In, ?Yield, ?Await]
      ElementList[?Yield, ?Await] , Elision_opt SpreadElement[?Yield, ?Await]
   -------------------------------------------------
   AssignmentElementList[Yield, Await]:
      AssignmentElisionElement[?Yield, ?Await]
      AssignmentElementList[?Yield, ?Await] , AssignmentElisionElement[?Yield, ?Await]
   AssignmentElisionElement[Yield, Await]:
      Elision_opt AssignmentElement[?Yield, ?Await]
   AssignmentElement[Yield, Await]:
      DestructuringAssignmentTarget[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
   DestructuringAssignmentTarget[Yield, Await]:
      LeftHandSideExpression[?Yield, ?Await]
================================================================================
[NOTE] effectively
   ArrayElement => AssignmentExpression
   AssignmentElement => LeftHandSideExpression Initializer_opt
hence AssignmentElement ⊂ ArrayElement = AssignmentExpression
the differences in the elements are:
   1) ArrayLiteral can have multiple SpreadElements whereas
      DestructuringAssignments can have a single RestElement
   2) Ensure SpreadElement expression is LeftHandSideExpression
   3) Only the production of AssignmentExpression with AssignmentOperator '='
      is valid for AssignmentElement
   4) Ensure other productions of ArrayElement reduce to LeftHandSideExpression
================================================================================
[RestElement]:
   SpreadElement[Yield, Await]:
      ... AssignmentExpression[+In, ?Yield, ?Await]
   -------------------------------------------------
   AssignmentRestElement[Yield, Await]:
      ... DestructuringAssignmentTarget[?Yield, ?Await]
   DestructuringAssignmentTarget[Yield, Await]:
      LeftHandSideExpression[?Yield, ?Await]
*/

void* parse_this_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(this_expression); ensure_word(this); return_node();
}

/*
Expression[In, Yield, Await]:
   AssignmentExpression[?In, ?Yield, ?Await]
   Expression[?In, ?Yield, ?Await] , AssignmentExpression[?In, ?Yield, ?Await]
*/
void* parse_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(assignment_expression);
   if(!exists(',')) passon(assignment_expression);
   make_node(expression);
   assign_begin();
   start_list();
   add_to_list(assignment_expression);
   while(optional(',')) {
      parse(assignment_expression);
      add_to_list(assignment_expression);
   }
   //assign(expressions, list_head());
   assign(expressions, raw_list_head());
   return_node();
}
void* parse_covering_parenthesized_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   size_t count = 0;
   token_t const* trailing_comma = nullptr;
   save_begin();
   ensure('(');
   make_node(expression);
   start_list();
   scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
   //if(!(params & PARAM)) hoisting_scope->first_yield_or_await = nullptr;
   hoisting_scope->first_yield_or_await = nullptr;
   while(!exists(')')) {
      ++count;
      trailing_comma = nullptr;
      if(exists(pnct_spread)) {
         //[REVIEW] should we parse as rest element or spread element
         // rest element immediately add indentifiers to the scope whereas
         // identifiers from earlier expression are yet to be added
         //parse(binding_rest_element, NONE, LOOSE);
         //add_to_list(binding_rest_element);
         parse(spread_element);
         add_to_list(spread_element);
         spread_element_t* se = spread_element;
         add_to_cover_list(se);
         if(!exists(')')) {
            return_location_end_error(missing_parenthesis, se->location, nullptr);
         }
         break;
      }
      //params_t add_params = ((exists('[') || exists('{')) ? PARAM : NONE) | IN;
      //parse(assignment_expression, NONE, add_params);
      parse(assignment_expression, NONE, IN);
      add_to_list(assignment_expression);
      if(exists(',')) {
         trailing_comma = state->parse_token;
         ensure(',');
      } else break;
   }
   assign(expressions, raw_list_head());
   expression_t* expression = completed_node();
   expect(')');
   if(!exists(pnct_arrow) || exists_newline()) {
      if(count == 0) {
         return_token_error(empty_parenthetical, previous_token(), nullptr);
      } else if(trailing_comma != nullptr) {
         return_token_error(trailing_comma, trailing_comma, nullptr);
      }
      /*
      if(count == 0 || trailing_comma != nullptr || first_cover != nullptr) {
         passon(nullptr);
      }
      */
      // reduce expression list to a single expression
      // [TODO] reuse memory used for expression list
      if(count == 1) expression = node_as(expression, raw_list_head()->parse_node);
   } else {
      // [TODO] reuse memory used for expression list
      if(hoisting_scope->first_yield_or_await) {
         location_t const* location = node_as(parse_node, hoisting_scope->first_yield_or_await)->location;
         return_location_error(yield_await_in_arrow_params, location, nullptr);
      }
      if(count != 0) {
         uint8_t change_flags = change_flag_array_binding | change_flag_loose_binding;
         if(!change_node_types(state, expression->expressions, !!trailing_comma, change_flags, params|UNIQUE)) {
            passon(nullptr);
         }
      }
      //passon(expression->expressions);
   }
   {
      make_node(parenthesized_expression);
      assign_begin();
      assign(expression, expression);
      return_node();
   }
}
/*
ParenthesizedExpression[Yield, Await]:
   ( Expression[+In, ?Yield, ?Await] )
*/
void* parse_parenthesized_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(parenthesized_expression);
   ensure('('); parse(expression, expression, NONE, IN); expect(')');
   return_node();
}

// ====== PRIMARY EXPRESSION ====== //
/*
PrimaryExpression[Yield, Await]:
   this
   IdentifierReference[?Yield, ?Await]
   Literal
   ArrayLiteral[?Yield, ?Await]
   ObjectLiteral[?Yield, ?Await]
   FunctionExpression
   ClassExpression[?Yield, ?Await]
   GeneratorExpression
   AsyncFunctionExpression
   AsyncGeneratorExpression
   RegularExpressionLiteral
   TemplateLiteral[?Yield, ?Await, ~Tagged]
   CoverParenthesizedExpressionAndArrowParameterList[?Yield, ?Await]
CoverParenthesizedExpressionAndArrowParameterList[Yield, Await]:
   ( Expression[+In, ?Yield, ?Await] )
   ( Expression[+In, ?Yield, ?Await] , )
   ( )
   ( ... BindingIdentifier[?Yield, ?Await] )
   ( ... BindingPattern[?Yield, ?Await] )
   ( Expression[+In, ?Yield, ?Await] , ... BindingIdentifier[?Yield, ?Await] )
   ( Expression[+In, ?Yield, ?Await] , ... BindingPattern[?Yield, ?Await] )

When processing an instance of the production
   PrimaryExpression[Yield, Await]:
      CoverParenthesizedExpressionAndArrowParameterList[?Yield, ?Await]
the interpretation of CoverParenthesizedExpressionAndArrowParameterList is
refined using the following grammar:
ParenthesizedExpression[Yield, Await]:
   ( Expression[+In, ?Yield, ?Await] )
*/
void* parse_primary_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   switch(current_token()->id) {
      case rw_this: passon_parsed(this_expression);
      case tkn_identifier: passon_parsed(identifier_reference);
      case rw_null: case rw_true: case rw_false: passon_parsed(literal);
      case tkn_numeric_literal: passon_parsed(numeric_literal);
      case tkn_string_literal: passon_parsed(string_literal);
      case tkn_regexp_literal: passon_parsed(regexp_literal);
      case '[': passon_parsed(array_literal);
      case '{': passon_parsed(object_literal);
      case rw_class: passon_parsed(class_expression);
      case '`': passon_parsed(template_literal, TAG, NONE);
      //case '(': passon_parsed(parenthesized_expression);
      case '(': if(params & cover_flag_parameters) {
         passon_parsed(covering_parenthesized_expression);
      } else {
         passon_parsed(parenthesized_expression);
      }
      case rw_function: passon_parsed(function_expression, YLD|AWT, NONE);
      case rw_async: {
         if(!exists_newline_ahead() && exists_ahead_word(function)) {
            passon_parsed(function_expression, YLD|AWT, NONE);
         }
      } // fallthrough
      default: {
         // contextual keyword
         if(exists_mask(mask_identifier)) passon_parsed(identifier_reference);
         passon(nullptr);
      }
   }
}

/*
Arguments[Yield, Await]:
   ( )
   ( ArgumentList[?Yield, ?Await] )
   ( ArgumentList[?Yield, ?Await] , )
ArgumentList[Yield, Await]:
   AssignmentExpression[+In, ?Yield, ?Await]
   ... AssignmentExpression[+In, ?Yield, ?Await]
   ArgumentList[?Yield, ?Await] , AssignmentExpression[+In, ?Yield, ?Await]
   ArgumentList[?Yield, ?Await] , ... AssignmentExpression[+In, ?Yield, ?Await]
*/
void* parse_arguments_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   expect('(');
   start_list();
   while(!exists(')')) {
      if(exists(pnct_spread)) {
         make_node(spread_element);
         ensure(pnct_spread);
         parse(argument, assignment_expression, NONE, IN);
         assign(cover_node, nullptr);
         add_to_list(completed_node());
      } else {
         parse(assignment_expression, NONE, IN);
         add_to_list(assignment_expression);
      }
      if(!optional(',')) break;
   }
   expect(')');
   passon(list_head());
}

/*
MemberExpression[Yield, Await]:
   PrimaryExpression[?Yield, ?Await]
   MemberExpression[?Yield, ?Await] [ Expression[+In, ?Yield, ?Await] ]
   MemberExpression[?Yield, ?Await] . IdentifierName
   MemberExpression[?Yield, ?Await] TemplateLiteral[?Yield, ?Await, +Tagged]
   SuperProperty[?Yield, ?Await]
   MetaProperty
   new MemberExpression[?Yield, ?Await] Arguments[?Yield, ?Await]
SuperProperty[Yield, Await]:
   super[ Expression[+In, ?Yield, ?Await] ]
   super . IdentifierName
MetaProperty:
   NewTarget
   ImportMeta
NewTarget:
   new . target
ImportMeta:
   import . meta
*/
void* parse_member_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* continue_with_member_expression(parse_state_t* state, parse_tree_state_t* tree_state, void* object, char_t const* begin, position_t const begin_position, uint8_t flag, params_t params);
void* parse_member_only_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   void* object = nullptr;
   switch(current_token()->id) {
      case rw_super: {
         save_begin();
         make_node(super);
         ensure_word(super);
         object = completed_node();
         if(!exists('[') && !exists('.')) {
            return_token_error(standalone_super, previous_token(), nullptr);
         } else if(!(params & METHOD)) {
            return_token_error(misplaced_super_property, previous_token(), nullptr);
         }
         break;
      }
      case rw_new: {
         if(exists_ahead('.')) {
            make_node(meta_property);
            parse(meta, identifier_name);
            if(!(params & param_flag_function)) {
               return_token_error(new_meta, previous_token(), nullptr);
            }
            ensure('.');
            if(!current_token_is(target)) passon(nullptr);
            parse(property, identifier_name);
            object = completed_node();
         } else {
            make_node(new_expression);
            ensure_word(new);
            parse(callee, member_expression);
            if(exists('(')) {
               list_parse(arguments, arguments_list);
            } else {
               assign(arguments, nullptr);
            }
            object = completed_node();
         }
         break;
      }
      case rw_import: {
         make_node(meta_property);
         parse(meta, identifier_name);
         if(!(params & param_flag_module)) {
            return_token_error(import_in_non_module, previous_token(), nullptr);
         }
         expect('.');
         if(!current_token_is(meta)) passon(nullptr);
         parse(property, identifier_name);
         object = completed_node();
         break;
      }
      default: passon(nullptr);
   }
   continue_with(member_expression, object, begin, begin_position, flag_none);
   passon(member_expression);
}
void* continue_with_member_expression(parse_state_t* state, parse_tree_state_t* tree_state, void* object, char_t const* begin, position_t const begin_position, uint8_t flag, params_t params)
{
   void* property = nullptr;
   bool is_optional = (flag == optional_flag_optional);
   while(object) {
      uint8_t flags = flag_none | flag;
      if(optional('[')) {
         assign_parsed(expression, property, NONE, IN); expect(']');
         flags |= member_flag_computed;
      } else if(exists('`')) {
         make_node(tagged_template_expression);
         assign_begin();
         assign(tag, object);
         parse(quasi, template_literal, NONE, TAG);
         complete_node();
         object = node;
         continue;
      } else if(is_optional || optional('.')) {
         is_optional = false;
         flag = flag_none;
         assign_parsed(identifier_name, property);
      } else {
         passon(object);
      }
      make_node(member_expression);
      assign_begin();
      assign(object, object);
      assign(property, property);
      assign(flags, flags);
      complete_node();
      object = node;
   }
   passon(nullptr);
}
void* parse_member_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   try(member_only_expression);
   parse(primary_expression);
   continue_with(member_expression, primary_expression, begin, begin_position, flag_none);
   passon(member_expression);
}

/*
CallExpression[Yield, Await]:
   CoverCallExpressionAndAsyncArrowHead[?Yield, ?Await]
   SuperCall[?Yield, ?Await]
   ImportCall[?Yield, ?Await]
   CallExpression[?Yield, ?Await] Arguments[?Yield, ?Await]
   CallExpression[?Yield, ?Await] [ Expression[+In, ?Yield, ?Await] ]
   CallExpression[?Yield, ?Await] . IdentifierName
   CallExpression[?Yield, ?Await] TemplateLiteral[?Yield, ?Await, +Tagged]
SuperCall[Yield, Await]:
   super Arguments[?Yield, ?Await]
ImportCall[Yield, Await]:
   import ( AssignmentExpression[+In, ?Yield, ?Await] )
Arguments[Yield, Await]:
   ( )
   ( ArgumentList[?Yield, ?Await] )
   ( ArgumentList[?Yield, ?Await] , )
ArgumentList[Yield, Await]:
   AssignmentExpression[+In, ?Yield, ?Await]
   ... AssignmentExpression[+In, ?Yield, ?Await]
   ArgumentList[?Yield, ?Await] , AssignmentExpression[+In, ?Yield, ?Await]
   ArgumentList[?Yield, ?Await] , ... AssignmentExpression[+In, ?Yield, ?Await]
CoverCallExpressionAndAsyncArrowHead:
CallMemberExpression[Yield, Await]:
   MemberExpression[?Yield, ?Await] Arguments[?Yield, ?Await]
*/
void* continue_with_call_expression(parse_state_t* state, parse_tree_state_t* tree_state, void* callee, char_t const* begin, position_t const begin_position, uint8_t flag, params_t params);
void* parse_covering_call_only_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   if(exists_word(async) && exists_ahead('(') && !exists_newline_ahead()) {
      scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
      hoisting_scope->first_yield_or_await = nullptr;
      make_node(call_expression);
      parse(callee, identifier_reference);
      assign(flags, flag_none);
      list_parse(arguments, arguments_list, NONE, PARAM|COV_CALL);
      complete_node();
      if(exists(pnct_arrow) && !exists_newline()) {
         if(hoisting_scope->first_yield_or_await) {
            location_t const* location = node_as(parse_node, hoisting_scope->first_yield_or_await)->location;
            return_location_error(yield_await_in_arrow_params, location, nullptr);
         }
         set_node_type_of(node, covered_call_expression);
         if(!change_node_types(state, node->arguments, false, ARR_BND|LOOSE, params|UNIQUE)) {
            passon(nullptr);
         }
         passon(node);
      } else {
         //[TODO] account for offending cover grammar
         if(exists('(')) {
            continue_with(call_expression, node, begin, begin_position, flag_none);
            passon(call_expression);
         } else if(exists('[') || exists('.') || exists('`')) {
            continue_with(member_expression, node, begin, begin_position, flag_none);
            passon(member_expression);
         } else {
            passon(node);
         }
      }
   }
   passon(nullptr);
}
void* parse_call_only_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(exists_word(super)) {
      if(!exists_ahead('(')) { passon(nullptr); }
      if(!(params & DERIVED) || !(params & CONSTR)) {
         return_error(misplaced_super_call, errptr);
      }
      make_node(call_expression);
      {
         make_child_node(super);
         ensure_word(super);
         assign_to_parent(callee, completed_node());
      }
      assign(flags, flag_none);
      list_parse(arguments, arguments_list);
      return_node();
   } else if(exists_word(import)) {
      if(exists_ahead('.')) passon(nullptr);
      make_node(import_call);
      ensure_word(import); expect('(');
         parse(source, assignment_expression, NONE, IN);
      expect(')');
      return_node();
   } else {
      passon_parsed(covering_call_only_expression);
      //passon(nullptr);
   }
}
void* continue_with_call_expression(parse_state_t* state, parse_tree_state_t* tree_state, void* callee, char_t const* begin, position_t const begin_position, uint8_t flag, params_t params)
{
   make_node(call_expression);
   assign_begin();
   assign(callee, callee);
   assign(flags, flag_none | flag);
   list_parse(arguments, arguments_list);
   complete_node();
   void* result_node = node;
   while(result_node) {
      if(exists('(')) {
         continue_with(call_expression, result_node, begin, begin_position, flag_none);
         result_node = call_expression;
      } else if(exists('[') || exists('.') || exists('`')) {
         continue_with(member_expression, result_node, begin, begin_position, flag_none);
         result_node = member_expression;
      } else {
         passon(result_node);
      }
   }
   passon(nullptr);
}
void* parse_call_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   try(call_only_expression);
   parse(member_expression);
   continue_with(call_expression, member_expression, begin, begin_position, flag_none);
   passon(call_expression);
}
/*
NewExpression[Yield, Await]:
   MemberExpression[?Yield, ?Await]
   new NewExpression[?Yield, ?Await]
*/
/* looks redundant given MemberExpression
void* parse_new_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_new_only_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(!exists_word(new) || exists_ahead('.')) passon(nullptr);
   make_node(new_expression);
   next();
   parse(expression, new_expression);
   return_node();
}
void* parse_new_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   try(new_only_expression);
   parse(member_expression);
   continue_with(new_expression, member_expression, begin);
   passon(new_expression);
}
*/

/*
OptionalExpression[Yield, Await]:
   MemberExpression[?Yield, ?Await] OptionalChain[?Yield, ?Await]
   CallExpression[?Yield, ?Await] OptionalChain[?Yield, ?Await]
   OptionalExpression[?Yield, ?Await] OptionalChain[?Yield, ?Await]
OptionalChain[Yield, Await]:
   ?. Arguments[?Yield, ?Await]
   ?. [ Expression[+In, ?Yield, ?Await] ]
   ?. IdentifierName
   ?. TemplateLiteral[?Yield, ?Await, +Tagged]
   OptionalChain[?Yield, ?Await] Arguments[?Yield, ?Await]
   OptionalChain[?Yield, ?Await] [ Expression[+In, ?Yield, ?Await] ]
   OptionalChain[?Yield, ?Await] . IdentifierName
   OptionalChain[?Yield, ?Await] TemplateLiteral[?Yield, ?Await, +Tagged]
*/
void* continue_with_optional_expression(parse_state_t* state, parse_tree_state_t* tree_state, void* left, char_t const* begin, position_t const begin_position, params_t params)
{
   make_node(chain_expression);
   assign_begin();
   while(left != nullptr && optional(pnct_optional)) {
      uint8_t flag = optional_flag_optional;
      if(!exists('(')) {
         continue_with(member_expression, left, begin, begin_position, flag);
         left = member_expression;
         flag = flag_none;
      }
      if(exists('(')) {
         continue_with(call_expression, left, begin, begin_position, flag);
         left = call_expression;
      }
   }
   assign(expression, left);
   return_node();
}

/*
LeftHandSideExpression[Yield, Await]:
   NewExpression[?Yield, ?Await]
   CallExpression[?Yield, ?Await]
   OptionalExpression[?Yield, ?Await]
*/
void* parse_lhs_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   //try(new_only_expression);
   try(call_only_expression);
   parse(member_expression);
   if(exists('(')) {
      continue_with(call_expression, member_expression, begin, begin_position, flag_none);
      passon(call_expression);
   } else if(exists(pnct_optional)) {
      continue_with(optional_expression, member_expression, begin, begin_position);
      passon(optional_expression);
   }
   passon(member_expression);
}

/*
UpdateExpression[Yield, Await]:
   LeftHandSideExpression[?Yield, ?Await]
   LeftHandSideExpression[?Yield, ?Await] [no LineTerminator here] ++
   LeftHandSideExpression[?Yield, ?Await] [no LineTerminator here] --
   ++ UnaryExpression[?Yield, ?Await]
   -- UnaryExpression[?Yield, ?Await]
*/
void* parse_unary_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_update_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(exists_mask(mask_update_ops)) {
      state->in_regexp_context = 1;
      make_node(update_expression);
      assign_operator();
      ensure_mask(mask_update_ops);
      parse(argument, unary_expression);
      assign(flags, operator_flag_prefix);
      //[TODO] update location
      if(!is_an_assignment_target(state, node->argument, params)) {
         if(state->parse_error) return nullptr;
         else return_node_error(invalid_update, node->argument, nullptr);
      }
      return_node();
   } else {
      save_begin();
      parse(lhs_expression);
      if(exists_newline() || !exists_mask(mask_update_ops)) {
         passon(lhs_expression);
      }
      make_node(update_expression);
      assign_begin();
      assign(argument, lhs_expression);
      assign_operator();
      ensure_mask(mask_update_ops);
      assign(flags, flag_none);
      //[TODO] update location
      if(!is_an_assignment_target(state, node->argument, params)) {
         if(state->parse_error) return nullptr;
         else return_node_error(invalid_update, node->argument, nullptr);
      }
      return_node();
   }
}

/*
UnaryExpression[Yield, Await]:
   UpdateExpression[?Yield, ?Await]
   delete UnaryExpression[?Yield, ?Await]
   void UnaryExpression[?Yield, ?Await]
   typeof UnaryExpression[?Yield, ?Await]
   + UnaryExpression[?Yield, ?Await]
   - UnaryExpression[?Yield, ?Await]
   ~ UnaryExpression[?Yield, ?Await]
   ! UnaryExpression[?Yield, ?Await]
   [+Await] AwaitExpression[?Yield]
AwaitExpression[Yield]:
   await UnaryExpression[?Yield, +Await]
*/
void* parse_unary_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* parse_await_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(await_expression);
   scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
   if(!hoisting_scope->first_yield_or_await) hoisting_scope->first_yield_or_await = node;
   enable_pending_regexp_context();
   ensure_word(await);
   parse(argument, unary_expression, NONE, AWT);
   return_node();
}
void* parse_unary_only_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(exists_mask(mask_unary_ops)) {
      make_node(unary_expression);
      assign_operator();
      assign(flags, operator_flag_prefix);
      ensure_mask(mask_unary_ops);
      parse(argument, unary_expression);
      if(node->operator.id == rw_delete && (params & STRICT) &&
         is_an_eventual_identifier(node->argument)
      ){
         void* identifier = node->argument;
         if(!node_type_is(identifier, identifier)) {
            identifier = get_parenthesized_node(node->argument);
         }
         return_node_error(identifier_deletion, identifier, nullptr);
      }
      return_node();
   } else if(exists_word(await) && (params & param_flag_await)) {
      passon_parsed(await_expression, AWT, NONE);
   }
   passon(nullptr);
}
void* parse_unary_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   try(unary_only_expression);
   parse(update_expression);
   passon(update_expression);
}

//[WATCHOUT] relies on binary_expression_t and logical_expression_t to be identical types
void* precedence_adjusted(binary_expression_t* node, bool is_right)
{
   //printf("%d %d\n", node->type, ((parse_node_t*)(node->right))->type);
   if(!type_equal(node, node->right)) return node;
   node_as(binary_expression, node->right, right);
   //if(!reduces_to(node->right, logical_expression)) return node;
   // adjust justification and precedence operators
   int sign = precedence(node->operator) - precedence(right->operator);
   if((sign > 0) || (sign == 0 && is_right)) return node;
   node_as(parse_node, right->left, right_left);
   node->end = right_left->end;
   right->begin = node->begin;
   node->location->end = right_left->location->end;
   right->location->begin = node->location->begin;
   node->right = right->left;
   right->left = precedence_adjusted(node, is_right);
   //print_string("swapped\n");
   /*
   right->begin = node->begin;
   right->end = right_left->end;
   node->right = right->right;
   right->right = right->left;
   right->left = node->left;
   node->left = right;
   */
   return right;
}

/*
ExponentiationExpression[Yield, Await]:
   UnaryExpression[?Yield, ?Await]
   UpdateExpression[?Yield, ?Await] ** ExponentiationExpression[?Yield, ?Await]
*/
void* parse_exponentiation_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   try(unary_only_expression);
   parse(update_expression);
   if(!exists(pnct_exponentitation)) {
      passon(update_expression);
   }
   make_node(binary_expression);
   assign_begin();
   assign(left, update_expression);
   assign_operator();
   ensure(pnct_exponentitation);
   parse(right, exponentiation_expression);
   complete_node();
   passon(precedence_adjusted(node, true));
}

void* parse_binary_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(exponentiation_expression);
   if(!exists_mask(mask_binary_ops) ||
      (exists_word(in) && !(params & param_flag_in))
   ){
      passon(exponentiation_expression);
   }
   make_node(binary_expression);
   assign_begin();
   assign(left, exponentiation_expression);
   assign_operator();
   ensure_mask(mask_binary_ops);
   parse(right, binary_expression);
   complete_node();
   passon(precedence_adjusted(node, false));
}

/*
LogicalANDExpression[In, Yield, Await]:
   BitwiseORExpression[?In, ?Yield, ?Await]
   LogicalANDExpression[?In, ?Yield, ?Await] && BitwiseORExpression[?In, ?Yield, ?Await]
LogicalORExpression[In, Yield, Await]:
   LogicalANDExpression[?In, ?Yield, ?Await]
   LogicalORExpression[?In, ?Yield, ?Await] || LogicalANDExpression[?In, ?Yield, ?Await]
*/
void* parse_logical_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* continue_with_logical_expression(parse_state_t* state, parse_tree_state_t* tree_state, void* binary_expression, char_t const* begin, position_t const begin_position, params_t params)
{
   make_node(logical_expression);
   assign_begin();
   assign(left, binary_expression);
   assign_operator();
   ensure_mask(mask_logical_ops);
   parse(right, logical_expression);
   complete_node();
   passon(precedence_adjusted(node, false));
}
void* parse_logical_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(binary_expression);
   if(!exists_mask(mask_logical_ops)) passon(binary_expression);
   continue_with(logical_expression, binary_expression, begin, begin_position);
   passon(logical_expression);
}

/*
CoalesceExpression[In, Yield, Await]:
   CoalesceExpressionHead[?In, ?Yield, ?Await] ?? BitwiseORExpression[?In, ?Yield, ?Await]
CoalesceExpressionHead[In, Yield, Await]:
   CoalesceExpression[?In, ?Yield, ?Await]
   BitwiseORExpression[?In, ?Yield, ?Await]
[NOTE] a BitwiseORExpression is not a CoalesceExpression
*/
void* parse_coalesce_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params);
void* continue_with_coalesce_expression(parse_state_t* state, parse_tree_state_t* tree_state, void* binary_expression, char_t const* begin, position_t const begin_position, params_t params)
{
   make_node(logical_expression);
   assign_begin();
   assign(left, binary_expression);
   assign_operator();
   ensure(pnct_logical_coalesce);
   parse(right, coalesce_expression);
   complete_node();
   passon(precedence_adjusted(node, false));
}
//[TODO] calling parse(coalesce_expression) should not be allowed as it can
// produce a BinaryExpression (aka BitwiseORExpression) which is not allowed
// per grammar. Instead ShortCircuitExpression should be the entry point for
// for CoalesceExpression
void* parse_coalesce_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(binary_expression);
   if(!exists_mask(pnct_logical_coalesce)) passon(binary_expression);
   continue_with(coalesce_expression, binary_expression, begin, begin_position);
   passon(coalesce_expression);
}

/*
ShortCircuitExpression[In, Yield, Await]:
   LogicalORExpression[?In, ?Yield, ?Await]
   CoalesceExpression[?In, ?Yield, ?Await]
*/
void* parse_short_circuit_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(binary_expression);
   if(exists_mask(mask_logical_ops)) {
      continue_with(logical_expression, binary_expression, begin, begin_position);
      passon(logical_expression);
   } else if(exists(pnct_logical_coalesce)) {
      continue_with(coalesce_expression, binary_expression, begin, begin_position);
      passon(coalesce_expression);
   } else {
      passon(binary_expression);
   }
}

/*
ConditionalExpression[In, Yield, Await]:
   ShortCircuitExpression[?In, ?Yield, ?Await]
   ShortCircuitExpression[?In, ?Yield, ?Await] ?
      AssignmentExpression[+In, ?Yield, ?Await] :
      AssignmentExpression[?In, ?Yield, ?Await]
*/
void* parse_conditional_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(short_circuit_expression);
   if(!optional('?')) passon(short_circuit_expression);
   make_node(conditional_expression);
   assign_begin();
   assign(test, short_circuit_expression);
   parse(consequent, assignment_expression, NONE, IN);
   expect(':'); parse(alternate, assignment_expression);
   return_node();
}

/*
https://tc39.es/ecma262/#prod-ArrowParameters
ArrowFunction[In, Yield, Await]:
   ArrowParameters[?Yield, ?Await] [no LineTerminator here] => ConciseBody[?In]
ArrowParameters[Yield, Await]:
   BindingIdentifier[?Yield, ?Await]
   CoverParenthesizedExpressionAndArrowParameterList[?Yield, ?Await]
ConciseBody[In]:
   [lookahead ≠ {] ExpressionBody[?In, ~Await]
   { FunctionBody[~Yield, ~Await] }
ExpressionBody[In, Await]:
   AssignmentExpression[?In, ~Yield, ?Await]

Supplemental Syntax:
   When processing an instance of the production
      ArrowParameters[Yield, Await]:
         CoverParenthesizedExpressionAndArrowParameterList[?Yield, ?Await]
   the interpretation of CoverParenthesizedExpressionAndArrowParameterList is
   refined using the following grammar:
      ArrowFormalParameters[Yield, Await]:
         ( UniqueFormalParameters[?Yield, ?Await] )
*/
/*
https://tc39.es/ecma262/#prod-AsyncArrowFunction
AsyncArrowFunction[In, Yield, Await]:
   async [no LineTerminator here] AsyncArrowBindingIdentifier[?Yield]
      [no LineTerminator here] => AsyncConciseBody[?In]
   CoverCallExpressionAndAsyncArrowHead[?Yield, ?Await]
      [no LineTerminator here] => AsyncConciseBody[?In]
AsyncConciseBody[In]:
   [lookahead ≠ {] ExpressionBody[?In, +Await]
   { AsyncFunctionBody }
AsyncArrowBindingIdentifier[Yield]:
   BindingIdentifier[?Yield, +Await]
CoverCallExpressionAndAsyncArrowHead[Yield, Await]:
   MemberExpression[?Yield, ?Await] Arguments[?Yield, ?Await]

Supplemental Syntax:
   When processing an instance of the production
      AsyncArrowFunction:
         CoverCallExpressionAndAsyncArrowHead => AsyncConciseBody
   the interpretation of CoverCallExpressionAndAsyncArrowHead is refined using the
   following grammar:
      AsyncArrowHead:
         async [no LineTerminator here] ArrowFormalParameters[~Yield, +Await]
*/
void* continue_with_arrow_function(
   parse_state_t* state, parse_tree_state_t* tree_state,
   arrow_function_expression_t* node, char_t const* begin, position_t const begin_position, params_t add_params, params_t params
){
   params = make_params(COV_CALL|COND|COND_BODY, NONE);
   if(exists_newline()) passon(nullptr);
   ensure(pnct_arrow);
   if(exists('{')) {
      parse(body, function_body_container, YLD|AWT, add_params);
   } else {
      node->flags |= function_flag_expression;
      parse(body, assignment_expression, YLD|AWT, add_params);
   }
   return_node();
}
/*
AssignmentExpression[In, Yield, Await]:
   ConditionalExpression[?In, ?Yield, ?Await]
   [+Yield] YieldExpression[?In, ?Await]
   ArrowFunction[?In, ?Yield, ?Await]
   AsyncArrowFunction[?In, ?Yield, ?Await]
   LeftHandSideExpression[?Yield, ?Await] = AssignmentExpression[?In, ?Yield, ?Await]
   LeftHandSideExpression[?Yield, ?Await] AssignmentOperator AssignmentExpression[?In, ?Yield, ?Await]
   LeftHandSideExpression[?Yield, ?Await] &&= AssignmentExpression[?In, ?Yield, ?Await]
   LeftHandSideExpression[?Yield, ?Await] ||= AssignmentExpression[?In, ?Yield, ?Await]
   LeftHandSideExpression[?Yield, ?Await] ??= AssignmentExpression[?In, ?Yield, ?Await]
AssignmentOperator:one of
   *= /= %= += -= <<= >>= >>>= &= ^= |= **=

In certain circumstances when processing an instance of the production
AssignmentExpression[In, Yield, Await]:
   LeftHandSideExpression[?Yield, ?Await] = AssignmentExpression[?In, ?Yield, ?Await]
the interpretation of LeftHandSideExpression is refined using the following grammar:
AssignmentPattern[Yield, Await]:
   ObjectAssignmentPattern[?Yield, ?Await]
   ArrayAssignmentPattern[?Yield, ?Await]
ObjectAssignmentPattern[Yield, Await]:
   { }
   { AssignmentRestProperty[?Yield, ?Await] }
   { AssignmentPropertyList[?Yield, ?Await] }
   { AssignmentPropertyList[?Yield, ?Await] , AssignmentRestProperty[?Yield, ?Await]opt }
ArrayAssignmentPattern[Yield, Await]:
   [ Elision_opt AssignmentRestElement[?Yield, ?Await]opt ]
   [ AssignmentElementList[?Yield, ?Await] ]
   [ AssignmentElementList[?Yield, ?Await] , Elision_opt AssignmentRestElement[?Yield, ?Await]opt ]
AssignmentRestProperty[Yield, Await]:
   ... DestructuringAssignmentTarget[?Yield, ?Await]
AssignmentPropertyList[Yield, Await]:
   AssignmentProperty[?Yield, ?Await]
   AssignmentPropertyList[?Yield, ?Await] , AssignmentProperty[?Yield, ?Await]
AssignmentElementList[Yield, Await]:
   AssignmentElisionElement[?Yield, ?Await]
   AssignmentElementList[?Yield, ?Await] , AssignmentElisionElement[?Yield, ?Await]
AssignmentElisionElement[Yield, Await]:
   Elision_opt AssignmentElement[?Yield, ?Await]
AssignmentProperty[Yield, Await]:
   IdentifierReference[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
   PropertyName[?Yield, ?Await] : AssignmentElement[?Yield, ?Await]
AssignmentElement[Yield, Await]:
   DestructuringAssignmentTarget[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
AssignmentRestElement[Yield, Await]:
   ... DestructuringAssignmentTarget[?Yield, ?Await]
DestructuringAssignmentTarget[Yield, Await]:
   LeftHandSideExpression[?Yield, ?Await]
*/
void* parse_assignment_expression(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   void* expression = nullptr;
   save_begin();
   if(exists_word(yield) &&
      (params & param_flag_yield) && !(params & param_flag_formal)
   ){
      passon_parsed(yield_expression, YLD, NONE);
   }
   bool has_async = exists_word(async) && !exists_newline_ahead();
   bool has_arrow = false;
   scope_list_node_t* scope_list_node = nullptr;
   token_t const* const plus_one_token = next_token();
   if(has_async) {
      scope_list_node = new_scope(state, scope_flag_function | scope_flag_hoisting, nullptr);
      assign_parsed(conditional_expression, expression);
      // make sure we do not have an async expression
      if(current_token() == plus_one_token) {
         has_async = !exists(pnct_arrow);
         if(exists_mask(mask_identifier) &&
            exists_ahead(pnct_arrow) && !exists_newline_ahead()
         ){
            assign_parsed(binding_identifier, expression, NONE, AWT);
            assert_lexical_uniqueness(expression, LOOSE, NONE);
         }
      }
   } else {
      bool has_parenthesis = exists('(');
      params_t add_params = (has_parenthesis ? PARAM : NONE);
      if(has_parenthesis || exists_ahead(pnct_arrow)) {
         scope_list_node = new_scope(state, scope_flag_function | scope_flag_hoisting, nullptr);
      }
      assign_parsed(conditional_expression, expression, NULL, add_params);
   }
   if(exists(pnct_arrow) && !exists_newline()) {
      if(current_token() == plus_one_token) {
         if(is_reserved_symbol(state, expression, params)) passon(nullptr);
         assert_lexical_uniqueness(expression, LOOSE, NONE);
      }
      make_node(arrow_function_expression);
      assign_begin();
      assign(id, nullptr);
      switch(node_type(expression)) {
         case pnt_parenthesized_expression: {
            node_as(parenthesized_expression, expression, pe);
            node_as(expression, pe->expression, expr);
            assign(params, expr->expressions);
            //change_node_types(state, expr->expressions, change_flag_array_binding, params);
            break;
         }
         case pnt_identifier: {
            start_list(); add_to_list(expression);
            assign(params, raw_list_head());
            break;
         }
         case pnt_covered_call_expression: {
            //[BUG][TODO] insert call symbol into scope
            node_as(covered_call_expression, expression, ce);
            assign(params, ce->arguments);
            //change_node_types(state, ce->arguments, false, change_flag_array_binding, params);
            break;
         }
         default: passon(nullptr);
      }
      assign(flags, (has_async ? function_flag_async : flag_none));
      params_t add_params = (has_async ? param_flag_await : flag_none);
      continue_with(arrow_function, node, begin, begin_position, add_params);
      end_scope(state);
#ifdef COMPILER
      node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
      passon(arrow_function);
   }
   if(scope_list_node != nullptr) {
      // adjust for introduction of new scope while parsing covering_parenthesized_expression
      scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
      scope_t* parent_hoisting_scope = state->hoisting_scope_list_node->parent->hoisting_parent->scope;
      if(!parent_hoisting_scope->first_yield_or_await) {
         parent_hoisting_scope->first_yield_or_await = hoisting_scope->first_yield_or_await;
      }
      //end_scope(state); //[REVIEW]
      collapse_scope(state);
   }
   if(!exists_mask(mask_assign_ops)) { passon(expression); }
   else if(!node_is_a(lhs_production, expression)) {
      return_node_error(invalid_assignment_target, expression, nullptr);
   }
   if(!exists_mask(mask_assign_ops)) passon(expression);
   make_node(assignment_expression);
   assign_begin();
   assign(left, expression);
   bool lhs_is_valid;
   if(exists('=')) {
      if(!change_lhs_node_type(state, expression, change_flag_assignment, params)) {
         passon(nullptr);
      }
   } else {
      if(!is_an_assignment_target(state, expression, params)) {
         if(state->parse_error) return nullptr;
         else return_node_error(lvalue, expression, nullptr);
      }
   }
   assign_operator();
   ensure_mask(mask_assign_ops);
   parse(right, assignment_expression);
   return_node();
}

// ============ STATEMENTS ============= //
/*
BlockStatement[Yield, Await, Return]:
   Block[?Yield, ?Await, ?Return]
Block[Yield, Await, Return]:
   { StatementList[?Yield, ?Await, ?Return]opt }
*/
void* parse_block_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   scope_list_node_t* scope_list_node = nullptr;
   if(!(params & NOSCOPE)) {
      scope_list_node = new_scope(state, (params & COND_BODY ? scope_flag_conditional : NONE), nullptr);
      params = make_params(COND_BODY, NONE);
   }
   make_node(block_statement);
   expect('{'); list_parse(body, block_statement_list, NOSCOPE, NONE); expect('}');
   if(!(params & NOSCOPE)) {
      end_scope(state);
#ifdef COMPILER
      node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   }
   return_node();
}
/*
LexicalDeclaration[In, Yield, Await]:
   LetOrConst BindingList[?In, ?Yield, ?Await] ;
LetOrConst:
   let
   const
BindingList[In, Yield, Await]:
   LexicalBinding[?In, ?Yield, ?Await]
   BindingList[?In, ?Yield, ?Await] , LexicalBinding[?In, ?Yield, ?Await]
LexicalBinding[In, Yield, Await]:
   BindingIdentifier[?Yield, ?Await] Initializer[?In, ?Yield, ?Await]opt
   BindingPattern[?Yield, ?Await] Initializer[?In, ?Yield, ?Await]
VariableStatement[Yield, Await]:
   var VariableDeclarationList[+In, ?Yield, ?Await] ;
VariableDeclarationList[In, Yield, Await]:
   VariableDeclaration[?In, ?Yield, ?Await]
   VariableDeclarationList[?In, ?Yield, ?Await] , VariableDeclaration[?In, ?Yield, ?Await]
VariableDeclaration[In, Yield, Await]:
   BindingIdentifier[?Yield, ?Await] Initializer[?In, ?Yield, ?Await]opt
   BindingPattern[?Yield, ?Await] Initializer[?In, ?Yield, ?Await]
//
[NOTE] LexicalDeclaration and VariableStatement are identical productions except
for the differences in In parameter. We will handle all var, let, const
declaratioins identically with conditional parameters.
*/
void* parse_lexical_binding_list(parse_state_t* state, parse_tree_state_t* tree_state, uint8_t token_id, params_t params)
{
   start_list();
   bool first_element = true;
   params_t optional_binding_init = params & param_flag_for_binding;
   params = make_params(param_flag_for_binding, NULL);
   do {
      make_node(variable_declarator);
      if(exists_mask(mask_identifier)) {
         if(exists_word(let) && (params & LEXICAL)) {
            return_token_error(let_in_lexical, current_token(), nullptr);
         }
         parse(id, binding_identifier);
         assert_lexical_uniqueness(node->id, params & LOOSE, NONE);
         if(params & EXPORT) { assert_export_uniqueness(node->id); }
         if(token_id == rw_const && !exists('=')) {
            if(first_element && optional_binding_init) {
               if(exists_word(in) || exists_word(of)) {
                  assign(init, nullptr);
                  add_to_list(completed_node());
                  passon(list_head());
               }
            }
            return_error(missing_const_initializer, nullptr);
         }
         if(optional('=')) {
            parse(init, assignment_expression, EXPORT|LEXICAL, NONE);
         } else {
            assign(init, nullptr);
         }
      } else if(exists_mask(mask_binding_pattern)) {
         parse(id, binding_pattern);
         if(first_element && !exists('=') && optional_binding_init) {
            if(!exists_word(in) && !exists_word(of)) {
               return_error(missing_binding_initializer, nullptr);
            }
            assign(init, nullptr);
            add_to_list(completed_node());
            passon(list_head());
         } else {
            if(!exists('=')) {
               return_error(missing_binding_initializer, nullptr);
            }
            expect('=');
            parse(init, assignment_expression, EXPORT|LEXICAL, NONE);
         }
      } else {
         if(exists_mask(mask_always_a_reserved_word)) {
            return_error(reserved_word_as_variable, nullptr);
         } else {
            return_error(missing_variable_name, nullptr);
         }
      }
      add_to_list(completed_node());
      first_element = false;
   } while(optional(','));
   passon(list_head());
}
void* parse_variable_statement(parse_state_t* state, parse_tree_state_t* tree_state, uint8_t reserved_word, params_t params)
{
   make_node(variable_declaration);
   ensure(reserved_word);
   assign(kind, reserved_word);
   parse_with_arg(reserved_word, declarations, lexical_binding_list);
   parse_semicolon();
   //expect(';');
   //if(!exists('}')) expect(';');
   return_node();
}
void* parse_var_variable_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   return parse_variable_statement(state, tree_state, word(var), make_params(NONE, IN|LOOSE));
}
void* parse_let_variable_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(!is_let_a_keyword(params)){ passon(nullptr); }
   return parse_variable_statement(state, tree_state, word(let), params | LEXICAL);
}
void* parse_const_variable_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   return parse_variable_statement(state, tree_state, word(const), params | LEXICAL);
}
/*
EmptyStatement:
   ;
*/
void* parse_empty_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(empty_statement);
   ensure(';');
   return_node();
}
/*
ExpressionStatement[Yield, Await]:
   [lookahead ∉ { {, function, async [no LineTerminator here] function, class, let [ }]
      Expression[+In, ?Yield, ?Await] ;
//
[NOTE] We do not have to worry about the negative looakaheads here, as they are
just meant to avoid ambiguities between other Statement productions and
ExpressionStatement. All we have to do is check for ExpressionStatement at
the end after all other productions are tried. This is exactly what is done in
parse_statement below
*/
void* parse_expression_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(expression_statement);
   parse(expression, expression, NONE, IN);
   parse_semicolon();
   //expect(';');
   //if(!exists('}')) { expect(';'); }
   return_node();
}
/*
IfStatement[Yield, Await, Return]:
   if ( Expression[+In, ?Yield, ?Await] ) Statement[?Yield, ?Await, ?Return]
      else Statement[?Yield, ?Await, ?Return]
   if ( Expression[+In, ?Yield, ?Await] ) Statement[?Yield, ?Await, ?Return]
Annex B.3.4: https://tc39.es/ecma262/#sec-functiondeclarations-in-ifstatement-statement-clauses
   IfStatement[Yield, Await, Return]:
   if ( Expression[+In, ?Yield, ?Await] ) FunctionDeclaration[?Yield, ?Await, ~Default]
      else Statement[?Yield, ?Await, ?Return]
   if ( Expression[+In, ?Yield, ?Await] ) Statement[?Yield, ?Await, ?Return]
      else FunctionDeclaration[?Yield, ?Await, ~Default]
   if ( Expression[+In, ?Yield, ?Await] ) FunctionDeclaration[?Yield, ?Await, ~Default]
      else FunctionDeclaration[?Yield, ?Await, ~Default]
   if ( Expression[+In, ?Yield, ?Await] ) FunctionDeclaration[?Yield, ?Await, ~Default]
*/
void* parse_if_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params |= param_flag_conditional | param_flag_conditional_body;
   make_node(if_statement);
   ensure_word(if); expect('(');
      parse(test, expression, RET, IN);
   enable_pending_regexp_context();
   expect(')');
   if(exists_word(function) && allow_annex()) {
      // NOTE: this scope has no local variable declarations
      new_scope(state, NONE, nullptr);
      parse(consequent, hoistable_declaration, DEF, param_flag_vanilla_function);
      end_scope(state);
   } else {
      current_token()->flags |= token_flag_no_labeled_function;
      parse(consequent, statement);
   }
   if(optional_word(else)) {
      if(exists_word(function) && allow_annex()) {
         // NOTE: this scope has no local variable declarations
         new_scope(state, NONE, nullptr);
         parse(alternate, hoistable_declaration, DEF, param_flag_vanilla_function);
         end_scope(state);
      } else {
         current_token()->flags |= token_flag_no_labeled_function;
         parse(alternate, statement);
      }
   } else {
      assign(alternate, nullptr);
   }
   return_node();
}
/*
IterationStatement[Yield, Await, Return]:
   do Statement[?Yield, ?Await, ?Return]
      while ( Expression[+In, ?Yield, ?Await] ) ;
*/
void* parse_do_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params |= param_flag_conditional | param_flag_conditional_body;
   make_node(do_statement);
   ensure_word(do);
   uint32_t saved_semantic_flags = state->semantic_flags;
   state->semantic_flags |= (semantic_flag_break | semantic_flag_continue);
   //current_token()->flags |= token_flag_loop;
   current_token()->flags |= token_flag_no_labeled_function;
   parse(body, statement);
   state->semantic_flags = saved_semantic_flags;
   expect_word(while); expect('(');
      parse(test, expression, RET, IN);
   expect(')');
   optional(';');
   //parse_semicolon();
   //expect(';');
   //if(!exists('}')) { expect(';'); }
   return_node();
}
/*
IterationStatement[Yield, Await, Return]:
   while ( Expression[+In, ?Yield, ?Await] ) Statement[?Yield, ?Await, ?Return]
*/
void* parse_while_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params |= param_flag_conditional | param_flag_conditional_body;
   make_node(while_statement);
   ensure_word(while); expect('(');
      parse(test, expression, RET, IN);
   enable_pending_regexp_context();
   expect(')');
   uint32_t saved_semantic_flags = state->semantic_flags;
   state->semantic_flags |= (semantic_flag_break | semantic_flag_continue);
   //current_token()->flags |= token_flag_loop;
   current_token()->flags |= token_flag_no_labeled_function;
   parse(body, statement);
   state->semantic_flags = saved_semantic_flags;
   return_node();
}
// ====== STATEMENTS::For ============== //
/*
IterationStatement[Yield, Await, Return]:
   for (
      [lookahead ≠ let [] Expression[~In, ?Yield, ?Await]opt ;
      Expression[+In, ?Yield, ?Await]opt ;
      Expression[+In, ?Yield, ?Await]opt
   ) Statement[?Yield, ?Await, ?Return]
   for (
      var VariableDeclarationList[~In, ?Yield, ?Await] ;
      Expression[+In, ?Yield, ?Await]opt ;
      Expression[+In, ?Yield, ?Await]opt
   ) Statement[?Yield, ?Await, ?Return]
   for (
      LexicalDeclaration[~In, ?Yield, ?Await]
      Expression[+In, ?Yield, ?Await]opt ;
      Expression[+In, ?Yield, ?Await]opt
   ) Statement[?Yield, ?Await, ?Return]
   for (
      [lookahead ≠ let [] LeftHandSideExpression[?Yield, ?Await]
         in Expression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   for (
      var ForBinding[?Yield, ?Await] in Expression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   for (
      ForDeclaration[?Yield, ?Await] in Expression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   for (
      [lookahead ≠ let] LeftHandSideExpression[?Yield, ?Await]
         of AssignmentExpression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   for (
      var ForBinding[?Yield, ?Await] of AssignmentExpression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   for (
      ForDeclaration[?Yield, ?Await] of AssignmentExpression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   [+Await] for await (
      [lookahead ≠ let] LeftHandSideExpression[?Yield, ?Await]
         of AssignmentExpression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   [+Await] for await (
      var ForBinding[?Yield, ?Await] of AssignmentExpression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
   [+Await] for await (
      ForDeclaration[?Yield, ?Await] of AssignmentExpression[+In, ?Yield, ?Await]
   ) Statement[?Yield, ?Await, ?Return]
ForDeclaration[Yield, Await]:
   LetOrConst ForBinding[?Yield, ?Await]
ForBinding[Yield, Await]:
   BindingIdentifier[?Yield, ?Await]
   BindingPattern[?Yield, ?Await]
[NOTE] The difference between ForBinding and LexicalBinding is that ForBinding
does not have an initializer.
*/
void* parse_for_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   ///*
   params |= param_flag_conditional | param_flag_conditional_body;
   void* production = nullptr;
   void* for_statement = nullptr;
   bool is_declarator = false;
   uint8_t declarator_id = 0;
   bool in_of_possible = false;
   bool has_invalid_initializer = false;
   parse_node_t const* initializer = nullptr;
   bool has_let = false;

   save_begin();
   scope_list_node_t* scope_list_node = new_scope(state, NONE, nullptr);

   ensure_word(for);
   bool is_await = exists_word(await);
   if(is_await) {
      if(!(params & param_flag_await)) {
         return_token_error(unexpected_for_await, current_token(), nullptr);
      }
      enable_pending_regexp_context();
      ensure_word(await);
   }
   expect('(');
   if(is_await || !exists(';')) {
      if(exists_mask(mask_variable_declarator) &&
         (!(has_let = exists_word(let)) || is_let_a_keyword(params))
      ){
         is_declarator = true;
         declarator_id = current_token_id();
         make_node(variable_declaration);
         production = node;
         assign(kind, declarator_id);
         params_t add_params = param_flag_for_binding;
         if(declarator_id != rw_var) add_params |= LEXICAL;
         if(exists_word(var)){ add_params |= LOOSE; }
         ensure_mask(mask_variable_declarator);
         parse_with_arg(declarator_id, declarations, lexical_binding_list, IN, add_params);
         complete_node();
         node_as(parse_list_node, node->declarations, declarations);
         if(declarations->next == nullptr) { // has only one declartion
            node_as(variable_declarator, declarations->parse_node, declarator);
            if(declarator->init == nullptr){ // has no initializer
               in_of_possible = true;
            } else {
               in_of_possible = node_type_is(identifier, declarator->id);
               initializer = declarator->init;
               has_invalid_initializer = true;
            }
         }
      } else if(is_await) {
         parse(lhs_expression, RET, NONE);
         production = lhs_expression;
         in_of_possible = true;
      } else {
         parse(expression, IN, NONE);
         production = expression;
         in_of_possible = node_is_a(lhs_production, expression);
      }
   }
   if(is_await || in_of_possible) {
      if(exists_word(of)) {
         if(has_invalid_initializer) {
            return_node_error(initializer_in_for, initializer, nullptr);
         }
         if(!is_declarator) {
            if(has_let) {
               return_node_error(for_of_begins_with_let, production, nullptr);
            }
            if(!change_lhs_node_type(state, production, change_flag_assignment, params)) {
               return_node_error(invalid_for_assignment, production, nullptr);
            }
         }
         enable_pending_regexp_context();
         expect_word(of);
         make_node(for_of_statement);
         assign_begin();
         assign(left, production);
         parse(right, assignment_expression, RET, IN);
         assign(flags, (is_await ? for_flag_await : flag_none));
         for_statement = node;
      } else if(is_await) {
         return_error(expecting_of, nullptr);
      } else if(optional_word(in)) {
         if(has_invalid_initializer && !(declarator_id == word(var) && allow_annex())) {
            return_node_error(initializer_in_for, initializer, nullptr);
         }
         if(!is_declarator) {
            if(!change_lhs_node_type(state, production, change_flag_assignment, params)) {
               return_node_error(invalid_for_assignment, production, nullptr);
            }
         }
         make_node(for_in_statement);
         assign_begin();
         assign(left, production);
         parse(right, expression, RET, IN);
         for_statement = node;
      }
   }
   if(!for_statement) {
      make_node(for_statement);
      assign_begin();
      assign(init, production);
      expect(';');
      if(!exists(';')) {
         parse(test, expression, NONE, IN);
      } else {
         assign(test, nullptr);
      }
      expect(';');
      if(!exists(')')) {
         parse(update, expression, NONE, IN);
      } else {
         assign(update, nullptr);
      }
      for_statement = node;
   }
   enable_pending_regexp_context();
   expect(')');

   for_statement_t* node = for_statement;
   uint32_t saved_semantic_flags = state->semantic_flags;
   state->semantic_flags |= (semantic_flag_break | semantic_flag_continue);
   //current_token()->flags |= token_flag_for | token_flag_loop;
   current_token()->flags |= token_flag_no_labeled_function;
   parse(body, statement);
   end_scope(state);
#ifdef COMPILER
   node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   state->semantic_flags = saved_semantic_flags;
   return_node();
   //*/
   /*
   ensure_word(for); expect('(');
   bool offset = (exists_mask(mask_variable_declarator) ? 1 : 0);
   if(offset_lookahead(offset, tkn_identifier) &&
      offset_lookahead(offset + 1, word(in))
   ){
      make_node(for_in_statement);
      parse(left, identifier);
      expect_word(in);
      parse(right, expression);
      expect(')')
      parse(body, statement);
      return_node();
   } else {
      make_node(for_statement);
      if(!exists(';')) {
         if(offset != 0) { // has variable declarator
            make_child_node(variable_declaration);
            assign(kind, current_token()->id);
            ensure_mask(mask_variable_declarator);
            parse_with_arg(current_token()->id, declarations, lexical_binding_list);
            complete_node();
            assign_to_parent(init, node);
         } else {
            parse(init, expression);
         }
      }
      expect(';');
      if(!exists(';')) { parse(test, expression); } expect(';');
      if(!exists(')')) { parse(update, expression); } expect(')');
      parse(body, statement);
      return_node();
   }
   //*/
}
/*
ContinueStatement[Yield, Await]:
   continue ;
   continue [no LineTerminator here] LabelIdentifier[?Yield, ?Await] ;
*/
void* parse_continue_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(continue_statement);
   ensure_word(continue);
   if(!(state->semantic_flags & semantic_flag_continue)) {
      return_token_error(unsyntatic_continue, previous_token(), nullptr);
   }
   if(!exists('}')) {
      //if(!exists(';')) expect_mask(mask_idname);
      if(!exists(';') && !exists_newline()) {
         parse(label, label_identifier);
         if(!has_label(state, node->label, params)) {
            return_token_error(undefined_label, previous_token(), nullptr);
         }
      } else {
         assign(label, nullptr);
      }
      parse_semicolon();
      //expect(';');
      //if(!exists('}')) expect(';');
   } else {
      assign(label, nullptr);
   }
   return_node();
}
/*
BreakStatement[Yield, Await]:
   break ;
   break [no LineTerminator here] LabelIdentifier[?Yield, ?Await] ;
*/
void* parse_break_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(break_statement);
   ensure_word(break);
   if(!(state->semantic_flags & semantic_flag_break)) {
      return_token_error(unsyntatic_break, previous_token(), nullptr);
   }
   if(!exists('}')) {
      if(!exists(';') && !exists_newline()) {
         parse(label, label_identifier);
         if(!has_label(state, node->label, params)) {
            return_token_error(undefined_label, previous_token(), nullptr);
         }
      } else {
         assign(label, nullptr);
      }
      parse_semicolon();
      //expect(';');
      //if(!exists('}')) expect(';');
   } else {
      assign(label, nullptr);
   }
   return_node();
}
/*
ReturnStatement[Yield, Await]:
   return ;
   return [no LineTerminator here] Expression[+In, ?Yield, ?Await] ;
*/
void* parse_return_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(return_statement);
   ensure_word(return);
   if(!exists('}')) {
      if(!exists(';') && !exists_newline()) {
         parse(argument, expression, NONE, IN);
      } else {
         assign(argument, nullptr);
      }
      parse_semicolon();
      //expect(';');
      //if(!exists('}')) expect(';');
   } else {
      assign(argument, nullptr);
   }
   return_node();
}
/*
WithStatement[Yield, Await, Return]:
   with ( Expression[+In, ?Yield, ?Await] ) Statement[?Yield, ?Await, ?Return]
*/
void* parse_with_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   if(params & param_flag_strict_mode) {
      return_token_error(with_in_strict_mode, current_token(), nullptr);
   }
   make_node(with_statement);
   ensure_word(with); expect('(');
      parse(object, expression, RET, IN);
   expect(')');
   current_token()->flags |= token_flag_no_labeled_function;
   parse(body, statement);
   return_node();
}
/*
SwitchStatement[Yield, Await, Return]:
   switch ( Expression[+In, ?Yield, ?Await] ) CaseBlock[?Yield, ?Await, ?Return]
CaseBlock[Yield, Await, Return]:
   { CaseClauses[?Yield, ?Await, ?Return]opt }
   { CaseClauses[?Yield, ?Await, ?Return]opt
      DefaultClause[?Yield, ?Await, ?Return]
      CaseClauses[?Yield, ?Await, ?Return]opt }
CaseClauses[Yield, Await, Return]:
   CaseClause[?Yield, ?Await, ?Return]
   CaseClauses[?Yield, ?Await, ?Return] CaseClause[?Yield, ?Await, ?Return]
CaseClause[Yield, Await, Return]:
   case Expression[+In, ?Yield, ?Await] : StatementList[?Yield, ?Await, ?Return]opt
DefaultClause[Yield, Await, Return]:
   default : StatementList[?Yield, ?Await, ?Return]opt
*/
void* parse_case_clause_list(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   bool has_default = false;
   //position_t default_position;
   start_list();
   uint32_t saved_semantic_flags = state->semantic_flags;
   state->semantic_flags |= semantic_flag_break;
   while(true) {
      if(exists_word(case)) {
         make_node(case_clause);
         ensure_word(case);
         parse(test, expression, RET, IN);
         expect(':');
         list_parse(consequent, case_clause_statement_list);
         add_to_list(completed_node());
      } else if(exists_word(default)) {
         if(has_default) {
            return_token_error(duplicate_default_clause, current_token(), nullptr);
         }
         make_node(case_clause);
         //default_position = make_position(state);
         ensure_word(default);
         assign(test, nullptr);
         expect(':');
         list_parse(consequent, case_clause_statement_list);
         add_to_list(completed_node());
         has_default = true;
      } else {
         state->semantic_flags = saved_semantic_flags;
         passon(list_head());
      }
   }
}
void* parse_switch_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   params |= param_flag_conditional | param_flag_conditional_body;
   make_node(switch_statement);
   ensure_word(switch); expect('(');
      parse(discriminant, expression, RET, IN);
   expect(')');
   scope_list_node_t* scope_list_node = new_scope(state, scope_flag_switch, nullptr);
   expect('{');
      list_parse(cases, case_clause_list);
   expect('}');
   end_scope(state);
#ifdef COMPILER
   node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   return_node();
}
/*
LabelledStatement[Yield, Await, Return]:
   LabelIdentifier[?Yield, ?Await] : LabelledItem[?Yield, ?Await, ?Return]
LabelledItem[Yield, Await, Return]:
   Statement[?Yield, ?Await, ?Return]
   FunctionDeclaration[?Yield, ?Await, ~Default]
Static Semantics:
   Regular: https://tc39.es/ecma262/#sec-labelled-statements-static-semantics-early-errors
      LabelledItem: FunctionDeclaration
         It is a Syntax Error if any source text matches this rule.
   Annex B.3.4: https://tc39.es/ecma262/#sec-labelled-function-declarations
      LabelledItem: FunctionDeclaration
         It is a Syntax Error if any strict mode source code matches this rule.
*/
void* parse_labeled_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   //bool in_loop = current_token()->flags & token_flag_loop;
   uint8_t no_label = current_token()->flags & token_flag_no_labeled_function;
   make_node(labeled_statement);
   parse(label, label_identifier, RET, NONE);
   if(exists(':')) { assert_label_uniqueness(node->label); } expect(':');
   if(exists_word(function) && allow_annex()) {
      if(no_label) { return_token_error(no_labeled_function, current_token(), nullptr); }
      parse(body, hoistable_declaration, DEF|RET, param_flag_vanilla_function);
   } else {
      state->semantic_flags |= semantic_flag_break;
      current_token()->flags |= no_label;
      parse(body, statement);
   }
   ascend_label_chain(state);
   return_node();
}
/*
ThrowStatement[Yield, Await]:
   throw [no LineTerminator here] Expression[+In, ?Yield, ?Await] ;
*/
void* parse_throw_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(throw_statement);
   ensure_word(throw);
   if(exists_newline()) passon(nullptr);
   parse(argument, expression, NONE, IN);
   parse_semicolon();
   // /expect(';');
   //if(!exists('}')) { expect(';'); }
   return_node();
}
/*
TryStatement[Yield, Await, Return]:
   try Block[?Yield, ?Await, ?Return] Catch[?Yield, ?Await, ?Return]
   try Block[?Yield, ?Await, ?Return] Finally[?Yield, ?Await, ?Return]
   try Block[?Yield, ?Await, ?Return] Catch[?Yield, ?Await, ?Return] Finally[?Yield, ?Await, ?Return]
Catch[Yield, Await, Return]:
   catch ( CatchParameter[?Yield, ?Await] ) Block[?Yield, ?Await, ?Return]
   catch Block[?Yield, ?Await, ?Return]
Finally[Yield, Await, Return]:
   finally Block[?Yield, ?Await, ?Return]
CatchParameter[Yield, Await]:
   BindingIdentifier[?Yield, ?Await]
   BindingPattern[?Yield, ?Await]
*/
void* parse_try_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(try_statement);
   ensure_word(try);
   parse(block, block_statement);
   bool has_handler = false;
   if(exists_word(catch)) {
      params_t saved_params = params;
      params |= param_flag_conditional;
      has_handler = true;
      // we will create a scope for containing catch parameters
      // [TODO] annex allows var bindings to collide with catch parameters
      scope_list_node_t* scope_list_node = new_scope(state, scope_flag_catch | scope_flag_conditional, nullptr);
      make_child_node(catch_clause);
      ensure_word(catch);
      if(optional('(')) {
         if(exists_mask(mask_identifier)) {
            parse(param, binding_identifier, RET, NONE);
            /* in non-annex mode we will induce catch parameter as a symbol
               bound lexically in the scope, this will ensure lexical uniquess
               criterion without polluting the scope
               in annex mode we will save the identifier in scope->identifier to
               not pollute a scope and will check against it for lexical collisions
            */
            if(params & param_flag_annex) {
               state->current_scope_list_node->scope->identifier = node->param;
            } else {
               assert_lexical_uniqueness(node->param, NONE, NONE);
            }
            //assert_lexical_uniqueness(node->param, NONE, NONE);
            //assert_lexical_uniqueness(node->param, LOOSE, NONE);
         } else {
            parse(param, binding_pattern, RET, NONE);
         }
         expect(')');
      } else {
         assign(param, nullptr);
      }
      parse(body, block_statement, NONE, NOSCOPE);
      end_scope(state);
#ifdef COMPILER
      assign_to_parent(symbol_layout, scope_list_node->scope->symbol_layout);
#endif
      assign_to_parent(handler, completed_node());
      params = saved_params;
   } else {
      assign(handler, nullptr);
   }
   if(optional_word(finally)) {
      has_handler = true;
      parse(finalizer, block_statement);
   } else {
      assign(finalizer, nullptr);
   }
   if(!has_handler) { return_error(missing_try_handler, nullptr); }
   return_node();
}
/*
DebuggerStatement:
   debugger ;
*/
void* parse_debugger_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   make_node(debugger_statement);
   ensure_word(debugger);
   parse_semicolon();
   return_node();
}
// ====== STATEMENTS::Declaration ====== //
/*
Declaration[Yield, Await]:
   HoistableDeclaration[?Yield, ?Await, ~Default]
   ClassDeclaration[?Yield, ?Await, ~Default]
   LexicalDeclaration[+In, ?Yield, ?Await]
HoistableDeclaration[Yield, Await, Default]:
   FunctionDeclaration[?Yield, ?Await, ?Default]
   GeneratorDeclaration[?Yield, ?Await, ?Default]
   AsyncFunctionDeclaration[?Yield, ?Await, ?Default]
   AsyncGeneratorDeclaration[?Yield, ?Await, ?Default]
*/
void* parse_declaration(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   switch(current_token()->id) {
      case rw_async: // fallthrough
      case rw_function: passon_parsed(hoistable_declaration, DEF|COND|COND_BODY, NONE);
      case rw_class: passon_parsed(class_declaration, DEF|COND|COND_BODY, NONE);
      case rw_let: passon_parsed(let_variable_statement, DEF, IN);
      case rw_const: passon_parsed(const_variable_statement);
      default: passon(nullptr);
   }
}
// ====== STATEMENTS::Statement ======== //
/*
Statement[Yield, Await, Return]:
   BlockStatement[?Yield, ?Await, ?Return]
   VariableStatement[?Yield, ?Await]
   EmptyStatement
   ExpressionStatement[?Yield, ?Await]
   IfStatement[?Yield, ?Await, ?Return]
   BreakableStatement[?Yield, ?Await, ?Return]
   ContinueStatement[?Yield, ?Await]
   BreakStatement[?Yield, ?Await]
   [+Return] ReturnStatement[?Yield, ?Await]
   WithStatement[?Yield, ?Await, ?Return]
   LabelledStatement[?Yield, ?Await, ?Return]
   ThrowStatement[?Yield, ?Await]
   TryStatement[?Yield, ?Await, ?Return]
   DebuggerStatement
*/
void* parse_statement(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   switch(current_token()->id) {
      case '{': passon_parsed(block_statement);
      case rw_var: passon_parsed(var_variable_statement, RET, NONE);
      case ';': passon_parsed(empty_statement);
      case rw_if: passon_parsed(if_statement);
      case rw_do: passon_parsed(do_statement);
      case rw_while: passon_parsed(while_statement);
      case rw_for: passon_parsed(for_statement);
      case rw_switch: passon_parsed(switch_statement);
      case rw_continue: passon_parsed(continue_statement, RET, NONE);
      case rw_break: passon_parsed(break_statement, RET, NONE);
      case rw_return: {
         if(params & param_flag_return) { passon_parsed(return_statement); }
         else { return_token_error(unsyntatic_return, current_token(), nullptr); }
      }
      case rw_with: passon_parsed(with_statement);
      case rw_throw: passon_parsed(throw_statement, RET, NONE);
      case rw_try: passon_parsed(try_statement);
      case rw_debugger: passon_parsed(debugger_statement);
      default: {
         if(exists_mask(mask_identifier) && exists_ahead(':')) {
            passon_parsed(labeled_statement);
         } else if(exists_mask(mask_expression_exclusions)) {
            if(exists_word(async)) {
               if(exists_ahead_word(function) && !exists_newline_ahead()) {
                  passon(nullptr);
               }
            } else if(exists_unescaped_word(let)) {
               if(exists_ahead('[')) { passon(nullptr); }
            } else {
               passon(nullptr);
            }
         }
         passon_parsed(expression_statement, RET, NONE);
      }
   }
}

program_t* parse_script(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   scope_list_node_t* scope_list_node = state->top_level_scope_list_node = new_scope(
      state, scope_flag_script | scope_flag_hoisting, nullptr
   );
   make_node(program);
   assign(source_type, program_kind_script);
   list_parse(body, script_body);
   complete_node();
   end_scope(state);
#ifdef COMPILER
   node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   return node;
}

program_t* parse_module(parse_state_t* state, parse_tree_state_t* tree_state, params_t params)
{
   scope_list_node_t* scope_list_node = state->top_level_scope_list_node = new_scope(
      state, scope_flag_module | scope_flag_hoisting, nullptr
   );
   make_node(program);
   assign(source_type, program_kind_module);
   list_parse(body, module_body);
   if(state->export_reference_list) {
      symbol_list_node_t* symbol_list_node = state->export_reference_list->head;
      scope_t const* const scope = state->current_scope_list_node->scope;
      symbol_list_node_t* matched_symbol_list_node;
      while(symbol_list_node) {
         identifier_t const* const identifier = symbol_list_node->symbol->identifier;
         string_t const* const symbol_string = (
            identifier->compiled_string
               ? (string_t*)(identifier->compiled_string)
               : (string_t*)(identifier)
         );
         size_t const symbol_length = symbol_string->end - symbol_string->begin;
         uint16_t hash = (
            ((symbol_length & symbol_length_mask) << 5) |
            (*symbol_string->begin & symbol_first_letter_mask)
         );
         scope_list_node_t* scope_list_node = state->current_scope_list_node;
         uint8_t has_symbol = get_symbol_from_lexical_tree(
            &scope_list_node, symbol_string, symbol_length, hash, &matched_symbol_list_node
         );
         if(!has_symbol) {
            return_location_error(missing_export_reference, identifier->location, nullptr);
         }
         symbol_list_node = symbol_list_node->next;
      }
   }
   complete_node();
   end_scope(state);
#ifdef COMPILER
   node->symbol_layout = scope_list_node->scope->symbol_layout;
#endif
   return node;
}

#undef NONE
#undef AWT
#undef DEF
#undef IN
#undef RET
#undef YLD
#undef TAG
#undef INIT
#undef PARAM

#undef COND
#undef COND_BODY

#undef error
#undef word
#undef precedence
#undef make_node
#undef make_child_node
#undef complete_node
#undef return_node
#undef note

#undef raw_char
#undef exists
#undef exists_word
#undef exists_mask
#undef optional
#undef optional_word
#undef optional_mask
#undef next
#undef expect
#undef expect_word
#undef expect_mask
#undef ensure
#undef ensure_word

// define parse with optional arguments
#undef _parse1
#undef _parse2
#undef _get_3rd_arg
#undef _choose_parse
#undef parse

#undef try

#undef current_token_id
#undef shift
#undef assign

#undef lookahead
#undef offset_lookahead
#undef negative_lookahead
#undef offset_negative_lookahead

#undef is
#undef as

#undef start_list
#undef add_to_list
#undef list_head

wasm_export parse_result_t parse(char_t const* code_begin, char_t const* code_end, bool is_module, uint32_t params)
{
   if(params == flag_none) params |= param_flag_annex;
   if(is_module) {
      to_strict_mode();
      params |= param_flag_module;
   } else {
      params &= ~param_flag_module;
      if(params & (param_flag_loose_mode | param_flag_strict_mode)) {
         to_loose_mode();
      }
   }
   size_t code_length = code_end - code_begin;
   memory_state_t memory_state = {
      .head = nullptr, .current = nullptr, .page_count = 0
   };
   memory_state_t* memory = &memory_state;
#if defined(MEMOPT)
   params |= param_flag_streaming;
   token_t* token_begin = (token_t *) parser_malloc_impl(memory, token_capacity * sizeof(token_t));
   token_t* token_end = token_begin + token_capacity;
   #ifdef DBGMEM
      memory_metric[mm_tokens] = token_capacity * sizeof(token_t);
   #endif
#else
   size_t predicted_tokens = ((code_end - code_begin) / 1) + 3 + 128;
   token_t* token_begin = (token_t*) parser_malloc_impl(memory, predicted_tokens * sizeof(token_t));
   token_t* token_end = token_begin + predicted_tokens;
#endif
   params |= param_flag_inconsistent_lines;
   parse_state_t _state = {
      .memory = &memory_state,
      // code buffer
      .code_begin = code_begin,
      .code_end = code_end,
      .code = code_begin,
      // token buffer
      .token_begin = token_begin,
      .token_end = token_end,
      .scan_token = token_begin,
      .token_count = 0,
      .tokens_consumed = 0,
      // scanner flags
      .line_number = 1,
      .line_begin = code_begin,
      .token_flags = token_flag_begin,
      .current_token_flags = token_flag_none,
      .in_template_expression = 0,
      .in_regexp_context = 1,
      .is_continuer = 0,
      .was_continuer = 1,
      .was_contextual = 0,
      .template_level = 0,
      .parenthesis_level = 0,
      .curly_parenthesis_level = 0,
      .expect_statement_after_level = 0,
      .template_parenthesis_offset = 0,
      // parser
      .parse_token = token_begin,
      .cover_node_list = {.head = nullptr, .tail = nullptr, .count = 0},
      .depth = 0,
      .semantic_flags = flag_none,
      // scope
      .scope_count = 0,
      .scope_depth = 0,
      .scope_list_node = nullptr,
      .top_level_scope_list_node = nullptr,
      .current_scope_list_node = nullptr,
      .hoisting_scope_list_node = nullptr,
      .closure_scope_list = {.head = nullptr, .tail = nullptr},
#ifdef EXTENSIONS
      .type_list = {.head = nullptr, .tail = nullptr},
#endif
      // module
      .export_symbol_table = nullptr,
      .export_reference_list = nullptr,
      .has_default_export = 0,
      // error state
      .tokenization_status = status_flag_incomplete,
      .parsing_status = status_flag_incomplete,
      .parse_error = nullptr,
      .error_position = {.line = 0, .column = 0},
      .expected_token_id = 0,
      .expected_mask = 0,
   };
   parse_state_t* state = &_state;
#ifdef EXTENSIONS
   // add predefined types
   insert_type(state, &std_data_type[vt_any]);
   insert_type(state, &std_data_type[vt_int64]);
   insert_type(state, &std_data_type[vt_float64]);
   insert_type(state, &std_data_type[vt_vector]);
   insert_type(state, &std_data_type[vt_matrix]);
#endif
   if(is_module) { state->export_symbol_table = new_symbol_table(state); }
   //new_scope(state, (is_module ? scope_flag_module : scope_flag_script) | scope_flag_hoisting, nullptr);
   if(params & param_flag_streaming) {
      scan_next_token(state, params);
      scan_next_token(state, params);
   } else {
      tokenize(state, params);
   }
   if_debug(print_string("parsing begins\n");)
   parse_tree_state_t tree_state = {.flags = 0};
   //init_named_list(state.aggregator.array.spread);
   //init_named_list(state.aggregator.array.assignment);
   //init_named_list(state.aggregator.array.pattern)
   //printf("%p begin: %zu end: %zu\n", state.token_begin, (state.token_begin + 1)->begin, (state.token_begin + 1)->end);
   program_t* program = nullptr;
   if(is_module) {
      program = parse_module(state, &tree_state, params);
   } else {
      program = parse_script(state, &tree_state, params);
   }
   if(state->cover_node_list.count == 0 && program != nullptr && state->parse_token->id == tkn_eot) {
      state->parsing_status = status_flag_complete;
   } else {
      if(state->cover_node_list.count != 0) {
         location_t const* location = state->cover_node_list.head->cover_node->location;
         if(location != nullptr) {
            if(!state->parse_error /*||
               (state->error_position.line > location->begin.line ||
                (state->error_position.line == location->begin.line &&
                 state->error_position.column >= location->begin.column)
              )*/
            ){
               state->error_position = location->begin;
               set_error(invalid_cover_grammar);
            }
         }
      }
      state->parsing_status = status_flag_failed;
   }
   //printf("%p begin: %zu end: %zu\n", state.token_begin, (state.token_begin + 1)->begin, (state.token_begin + 1)->end);
   //printf("length = %d\n", program->end - program->begin);
   if(program != nullptr) {
      program->begin = state->code_begin;
      program->end = state->code_end;
      program->location->begin = (position_t){.line = 1, .column = 0};
      program->location->end = make_position(state);
   }
   /*
   #ifdef debug
   if(program == nullptr) {
      char_t const* begin = state.parse_token->begin;
      int length = state.parse_token->end - begin;
      printf("\nparsing failed at character index %zu %.*s\n", begin, length, state.buffer + begin);
      if(state.parse_error != nullptr) {
         printf("%s\n", state.parse_error->message);
      }
      printf("token found: %x %x %c\n", state.parse_token->id, state.parse_token->group, state.parse_token->id);
      printf("token expected: %x %c\n", state.expected_token_id, state.expected_token_id);
   } else {
      printf("parsing successful: page_count = %zu\n", state.memory.page_count);
   }
   #endif
   //*/
#ifdef DBGMEM
   for(int i = 0; i < memory_metric_count; ++i) {
      printf("%24s: %d\n", memory_metric_names[i], memory_metric[i]);
   }
   printf("scopes %d*%lu %d*%lu\n", scope_count, sizeof(scope_t), symbol_count, sizeof(symbol_t));
   printf("%24s: %lu\n", "total memory", state->memory->page_count * page_size);
#endif
   return (parse_result_t){
      .program = program,
      .state = *state
   };
}

#endif //_PARSER_H_
