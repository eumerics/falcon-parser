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
#define INIT cover_flag_initializer
#define PARAM cover_flag_parameters

void* parser_malloc_impl(parser_state_t* state, size_t size)
{
   size_t const page_size = 1 << 12; // 4kB
   size_t const remainder = (size % 4); // align to 4-bytes
   size += (remainder == 0 ? 0 : 4 - remainder);
   if(state->memory.available < size) {
      memory_page_t* current = (memory_page_t*) malloc(sizeof(memory_page_t));
      current->buffer = (uint8_t*) malloc(page_size);
      current->next = nullptr;
      state->memory.available = page_size;
      state->memory.page_count++;
      if(state->memory.head == nullptr) {
         state->memory.head = current;
      } else {
         state->memory.current->next = current;
      }
      state->memory.current = current;
   }
   size_t offset = (page_size - state->memory.available);
   state->memory.available -= size;
   return state->memory.current->buffer + offset;
}

void parser_free(parser_state_t* state)
{
   free(state->tokens);
   memory_page_t* current = state->memory.head;
   while(current != nullptr) {
      free(current->buffer);
      memory_page_t* to_free = current;
      current = current->next;
      free(to_free);
   }
   state->memory.head = nullptr;
   state->memory.current = nullptr;
   state->memory.available = 0;
   state->memory.page_count = 0;
}

#define parser_malloc(size) parser_malloc_impl(state, size)

#define set_error(x) state->error_message = error_##x##_message;
#define return_error(x, value) { set_error(x); return value; }

#define word(name) rw_##name
#define token_matches(word) ( \
   strncmp_impl( \
      state->buffer + state->token->begin, \
      stringize(word), \
      strlen_impl(stringize(word)) \
   ) == 0 \
)
#define precedence(operator) (operator->precedence & 0xf8)
/*
#define print_token() { \
   size_t begin = state->token->begin; \
   int length = state->token->end - begin; \
   log_token("token: %.*s %x %x %d %d\n", length, state->buffer + begin, state->token->id, state->token->group, state->token->begin, state->token->end); \
}
*/

#define initialize_node(node_type) \
   print_make_node(node_type); \
   node->begin = state->token->begin; \
   node->type = pnt_##node_type; \
   node->group = png_##node_type;
#define make_node(node_type) \
   typedef node_type##_t parent_node_t; \
   node_type##_t* node = (node_type##_t*) parser_malloc(sizeof(node_type##_t)); \
   initialize_node(node_type);
#define make_child_node(node_type) \
   parent_node_t* parent = node; \
   typedef node_type##_t parent_node_t; \
   node_type##_t* node = (node_type##_t*) parser_malloc(sizeof(node_type##_t)); \
   initialize_node(node_type);
#define complete_node() (node->end = (state->token - 1)->end)
#define completed_node() (complete_node(), node)
#define passon(node) { _print_parse_ascent(node); return node; }
#define return_node() { complete_node(); passon(node); }
#define save_begin() size_t begin = state->token->begin;
#define save_end() size_t end = state->token->end;
#define assign_begin() node->begin = begin;
#define assign_end() node->end = end;
#define copy_begin(object) node->begin = ((parse_node_t*)(object))->begin;
#define assign_begin_to(object) ((parse_node_t*)(object))->begin = begin;
#define assign_end_to(object) ((parse_node_t*)(object))->end = end;
#define assign_operator() \
   node->operator_id = state->token->id; \
   node->operator = state->token;

#define allow_annex() ((params & param_flag_annex) & !(params & param_flag_strict_mode))

#define exists(token_id) (state->token->id == token_id)
#define exists_word(name) (state->token->id == word(name))
#define exists_mask(mask) (state->token->group & mask)
#define exists_newline() (state->token->flags & token_flag_newline)
#ifdef verbose
   #define optional(token_id) (\
      (state->token->id == token_id ? (print_token_consumption(), ++state->token, 1) : 0) \
   )
   #define optional_word(name) (state->token->id == word(name) ? (print_token_consumption(), ++state->token, 1) : 0)
   #define optional_mask(mask) (state->token->group & mask ? (print_token_consumption(), ++state->token, 1) : 0)
#else
   #define optional(token_id) (state->token->id == token_id ? (++state->token, 1) : 0)
   #define optional_word(name) (state->token->id == word(name) ? (++state->token, 1) : 0)
   #define optional_mask(mask) (state->token->group & mask ? (++state->token, 1) : 0)
#endif
#define next() print_token_consumption(); ++state->token;
#define expect(token_id) { \
   if(state->token->id != token_id) { \
      state->expected_token_id = token_id; \
      passon(nullptr); \
   } \
   print_token_consumption(); \
   ++state->token; \
}
#define expect_word(name) expect(word(name))
#define expect_mask(mask) { \
   if(!(state->token->group & mask)) { \
      state->expected_mask = mask; \
      passon(nullptr); \
   } \
   print_token_consumption(); \
   ++state->token; \
}
//#define ensure(token_id) if_else_debug(expect(token_id), next())
//#define ensure_word(name) if_else_debug(expect_word(name), next())
//#define ensure_mask(mask) if_else_debug(expect_mask(mask), next())
#define ensure(token_id) expect(token_id)
#define ensure_word(name) expect_word(name)
#define ensure_mask(mask) expect_mask(mask)

// define parse with optional arguments
#define make_params(remove_filter, add_filter) (params & ~(params_t)(remove_filter)) | ((params_t)(add_filter))
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
#define _continue_with3(type, object, begin) _continue_with5(type, object, begin, NONE, NONE)
#define _continue_with4(type, object, begin, arg) _continue_with6(type, object, begin, arg, NONE, NONE)
#define _continue_with5(type, object, begin, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = continue_with_##type(state, tree_state, object, begin, make_params(remove_filter, add_filter)); \
   if(type == nullptr) passon(nullptr);
#define _continue_with6(type, object, begin, arg, remove_filter, add_filter) \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = continue_with_##type(state, tree_state, object, begin, arg, make_params(remove_filter, add_filter)); \
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
   token_t* type##_start_token = state->token; \
   _print_parse_descent(type, remove_filter, add_filter); \
   void* type = parse_##type(state, tree_state, make_params(remove_filter, add_filter)); \
   if(type == nullptr && state->token != type##_start_token) { \
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
#define _get_3rd_arg(arg1, arg2, arg3, ...) arg3
#define _get_4th_arg(arg1, arg2, arg3, arg4, ...) arg4
#define _get_5th_arg(arg1, arg2, arg3, arg4, arg5, ...) arg5
#define _get_6th_arg(arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6
#define _get_7th_arg(arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...) arg7
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

// clear the exclusive group mask before assigning the desired flag
#define set_change_flag_to(type, flags) \
   ((flags & change_mask_group) | change_flag_##type)

#define current_token_id state->token->id
#define token_length() (state->token->end - state->token->begin)
#define raw_char(offset) (state->buffer[state->token->begin + offset])
#define token_is(name) ( \
   (state->token->end - state->token->begin == strlen(#name)) && \
   (strncmp_impl(state->buffer + state->token->begin, stringize(name), strlen(#name)) == 0) \
)
#define shift(property, value) node->property = value;
#define assign(property, value) node->property = value;
#define assign_to_parent(property, value) parent->property = value;

#define lookahead(token_id) ((state->token + 0)->id == token_id)
#define offset_lookahead(offset, token_id) ((state->token + offset)->id == token_id)
#define negative_lookahead(token_id) (state->token->id != token_id)
#define offset_negative_lookahead(offset, token_id) ((state->token + offset)->id != token_id)
#define negative_lookahead2(token_id1, token_id2) \
   !(state->token->id == token_id1 && (state->token + 1)->id == token_id2)

#define is(node, target) (((parse_node_t*)(node))->type ==  pnt_##target)
#define type_equal(source, target) (((parse_node_t*)(source))->type ==  ((parse_node_t*)(target))->type)
//#define reduces_to(node, target) (((parse_node_t*)(node))->type <=  pnt_##target)
//#define reduces_from(node, target) (((parse_node_t*)(node))->type >=  pnt_##target)
#define as(node, var_name, target) target##_t* var_name = (target##_t*)(node);

#define _init_list(list) \
   list.node_count = 0; \
   list.head = nullptr; \
   list.current = nullptr;
#define _start_list(list_name) \
   parse_node_list_state_t list_name = {0, nullptr, nullptr};
#define start_list() _start_list(list_state)
#define start_named_list(list) _start_list(list)
#define init_named_list(list) _init_list(list)

parse_list_node_t* make_list_node(parser_state_t* state, void* parse_node) {
   parse_list_node_t* list_node =
      (parse_list_node_t*) parser_malloc(sizeof(parse_list_node_t));
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

#define _list_head(list) (list.head == nullptr ? (void*)(&empty_list) : (void*)(list.head))
#define list_head() _list_head(list_state)
#define named_list_head(list) _list_head(list)

#define _raw_list_head(list) list.head
#define raw_list_head() _raw_list_head(list_state)
#define raw_named_list_head(list) _raw_list_head(list)

void* parse_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* parse_assignment_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* parse_lhs_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);

#define is_let_a_keyword() ( \
   (params & param_flag_strict_mode) || \
   ((state->token + 1)->group & (mask_let_inclusions | mask_identifier)) \
)
#define node_is_an(type, node) (((parse_node_t*)(node))->group & node_group_##type)
#define node_is_a(type, node) node_is_an(type, node)
#define node_has(type, node) node_is_an(type, node)
#define node_type_is(node_type, node) (((parse_node_t*)(node))->type == pnt_##node_type)
#define _node_as2(target, node) ((target##_t*)(node))
#define _node_as3(target, node, var_name) \
   if_verbose( if(pnt_##target != 0) assert(node_type_is(target, node), __FILE__, __LINE__); ) \
   target##_t* var_name = (target##_t*)(node);
#define _choose_node_as(...) _get_4th_arg(__VA_ARGS__, _node_as3, _node_as2, undefined, )
#define node_as(...) _choose_node_as(__VA_ARGS__)(__VA_ARGS__)
#define set_node_type_of(node, target_type) (((parse_node_t*)(node))->type = pnt_##target_type)

inline_spec uint8_t node_type(void* node)
{
   return ((parse_node_t*)(node))->type;
}

inline_spec bool is_an_assignment_target(void* node)
{
   //[TODO] strict mode exclusions of 'eval' and 'arguments'
   if(node_type_is(parenthesized_expression, node)) {
      node_as(parenthesized_expression, node, pe);
      if(node_type_is(expression, pe->expression)) {
         node_as(expression, pe->expression, expression);
         node_as(parse_list_node, expression->expressions, list_node);
         if(list_node->next != nullptr) return false;
         return is_an_assignment_target(list_node->parse_node);
      } else {
         return is_an_assignment_target(pe->expression);
      }
   }
   return node_is_an(assignment_target, node);
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
inline_spec identifier_t* parse_identifier(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(identifier); ensure_mask(mask_identifier); return_node();
}
inline_spec identifier_t* parse_identifier_reference(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(identifier); ensure_mask(mask_identifier); return_node();
}
inline_spec identifier_t* parse_binding_identifier(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(identifier); ensure_mask(mask_identifier); return_node();
}
inline_spec identifier_t* parse_label_identifier(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(identifier); ensure_mask(mask_identifier); return_node();
}
inline_spec identifier_t* parse_identifier_name(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(identifier); ensure_mask(mask_idname); return_node();
}
inline_spec literal_t* parse_literal(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(literal);
   assign(token_id, current_token_id);
   ensure_mask(mask_literal);
   return_node();
}
inline_spec regexp_literal_t* parse_regexp_literal(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(regexp_literal);
   assign(flags_length, state->token->flags_length);
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
inline_spec void* parse_computed_property_name(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   expect('['); parse(assignment_expression, NONE, IN); expect(']');
   passon(assignment_expression);
}
inline_spec void* parse_property_name(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   if(exists_mask(mask_idname)) {
      passon_parsed(identifier_name);
   } else if(exists(tkn_string_literal) || exists(tkn_numeric_literal)) {
      passon_parsed(literal);
   } else {
      passon_parsed(computed_property_name);
   }
}

// ====== STATEMENT LISTS ====== //
void* parse_declaration(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* parse_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
/*
StatementList[Yield, Await, Return]:
   StatementListItem[?Yield, ?Await, ?Return]
   StatementList[?Yield, ?Await, ?Return] StatementListItem[?Yield, ?Await, ?Return]
StatementListItem[Yield, Await, Return]:
   Statement[?Yield, ?Await, ?Return]
   Declaration[?Yield, ?Await]
*/
void* parse_statement_list_with_end_token(parser_state_t* state, parser_tree_state_t* tree_state, uint8_t end_token, params_t params)
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
   parser_state_t* state, parser_tree_state_t* tree_state, uint8_t end_token, params_t params
){
   bool look_for_directive = true;
   token_t* token = state->token;
   start_list();
   while(!exists(end_token)) {
      optional_parse(declaration, RET, NONE);
      if(declaration) {
         add_to_list(declaration);
      } else {
         parse(statement);
         add_to_list(statement);
         if(look_for_directive && token->id == tkn_string_literal &&
            (++token == state->token || (token->id == ';' && ++token == state->token)))
         {
            set_node_type_of(statement, directive);
         } else {
            look_for_directive = false;
         }
      }
   }
   passon(list_head());
}
void* parse_case_clause_statement_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
void* parse_block_statement_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   parse_with_arg('}', statement_list_with_end_token);
   passon(statement_list_with_end_token);
}
/*
ScriptBody:
   StatementList[~Yield, ~Await, ~Return]
*/
inline_spec void* parse_script_body(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   parse_with_arg(tkn_eot, directive_statement_list_with_end_token, YLD|AWT|RET, NONE);
   passon(directive_statement_list_with_end_token);
}

// ====== BINDING PATTERNS ====== //
/*
BindingElement[Yield, Await]:
   SingleNameBinding[?Yield, ?Await]
   BindingPattern[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
SingleNameBinding[Yield, Await]:
   BindingIdentifier[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
*/
void* parse_binding_pattern(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* parse_binding_element(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
      parse(binding_identifier);
      if(optional('=')) {
         make_node(binding_assignment);
         assign_begin();
         assign(left, binding_identifier);
         parse(right, assignment_expression, NONE, IN);
         return_node();
      } else {
         passon(binding_identifier);
      }
   } else {
      // BindingPattern[?Yield, ?Await] Initializer[+In, ?Yield, ?Await]opt
      save_begin();
      parse(binding_pattern);
      if(optional('=')) {
         make_node(binding_assignment);
         assign_begin();
         assign(left, binding_pattern);
         parse(right, assignment_expression, NONE, IN);
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
void* parse_object_binding_pattern(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(object_pattern);
   start_list();
   ensure('{');
   while(!exists('}')) {
      if(exists(pnct_spread)) {
         // BindingRestProperty
         make_node(rest_element);
         ensure(pnct_spread);
         parse(argument, binding_identifier);
         add_to_list(completed_node());
         break;
      } else {
         // BindingProperty
         make_node(assignment_property);
         assign(kind, property_kind_init);
         if(exists_mask(mask_identifier) && offset_negative_lookahead(1, ':')) {
            // SingleNameBinding: BindingIdentifier Initializer_opt
            save_begin();
            parse(binding_identifier);
            assign(key, binding_identifier);
            assign(flags, property_flag_shorthand);
            if(optional('=')) {
               make_child_node(binding_assignment);
               assign_begin();
               assign(left, binding_identifier);
               parse(right, assignment_expression, NONE, IN);
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
void* parse_binding_rest_element(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(rest_element);
   ensure(pnct_spread);
   if(exists_mask(mask_identifier)) {
      // BindingIdentifier
      parse(argument, binding_identifier);
   } else {
      // BindingPattern
      parse(argument, binding_pattern);
   }
   return_node();
}
void* parse_array_binding_pattern(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
   assign(elements, raw_list_head());
   expect(']');
   return_node();
}
/*
BindingPattern[Yield, Await]:
   ObjectBindingPattern[?Yield, ?Await]
   ArrayBindingPattern[?Yield, ?Await]
*/
void* parse_binding_pattern(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
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
void* parse_formal_parameter(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   passon_parsed(binding_element);
}
void* parse_formal_parameter_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   start_list();
   while(!exists(')')) {
      if(exists(pnct_spread)) {
         parse(binding_rest_element);
         add_to_list(binding_rest_element);
         //[TODO] error check rest element must follow ')'
         break;
      }
      parse(formal_parameter);
      add_to_list(formal_parameter);
      if(!optional(',')) break;
   }
   passon(list_head());
}
void* parse_formal_parameters(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   passon_parsed(formal_parameter_list);
}
void* parse_unique_formal_parameters(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   passon_parsed(formal_parameters);
}
/*
FunctionStatementList[Yield, Await]:
   StatementList[?Yield, ?Await, +Return]opt
*/
inline_spec void* parse_function_statement_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   parse_with_arg('}', directive_statement_list_with_end_token, NONE, RET);
   passon(directive_statement_list_with_end_token);
}
/*
FunctionBody[Yield, Await]:
   FunctionStatementList[?Yield, ?Await]
*/
inline_spec void* parse_function_body(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(function_body);
   list_parse(body, function_statement_list);
   return_node();
}
inline_spec void* parse_function_body_container(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(block_statement);
   expect('{'); list_parse(body, function_statement_list); expect('}');
   return_node();
}
/*
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
void* parse_function_declaration(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(function_declaration);
   params_t add_params = 0;
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
   parse(id, binding_identifier);
   expect('('); list_parse(params, formal_parameters, YLD|AWT, add_params); expect(')');
   //expect('{'); parse(body, function_body, YLD|AWT, flags); expect('}');
   parse(body, function_body_container, YLD|AWT, add_params);
   assign(flags, function_flags);
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
void* parse_function_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
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
      parse(id, binding_identifier);
   } else {
      assign(id, nullptr);
   }
   expect('('); list_parse(params, formal_parameters, YLD|AWT, add_params); expect(')');
   //expect('{'); list_parse(body, function_body); expect('}');
   //list_parse(body, function_body_container);
   parse(body, function_body_container, YLD|AWT, add_params);
   assign(flags, function_flags);
   return_node();
}
// ====== FUNCTIONS::MethodDefinition ====== //
/*
PropertySetParameterList:
   FormalParameter[~Yield, ~Await]
*/
inline_spec void* parse_property_set_parameter_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
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
inline_spec void* parse_method_function(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(function_expression);
   assign(id, nullptr);
   ensure('('); list_parse(params, unique_formal_parameters); expect(')');
   //expect('{'); list_parse(body, function_body); expect('}');
   //list_parse(body, function_body_container);
   parse(body, function_body_container);
   assign(flags, flag_none);
   return_node();
}
/*
inline_spec void* parse_method_function(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   if(exists('(')) passon_enparsed(method_function);
   passon(nullptr);
}
*/
method_definition_t* parse_method_only_definition(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   bool is_get_set = false, is_get = false, is_set = false;
   uint8_t property_kind = property_kind_method;
   uint8_t property_flags = property_flag_method;
   uint8_t function_flags = flag_none;
   params_t param_flags = 0;
   make_node(method_definition);
   if(optional_word(async)) {
      function_flags |= function_flag_async;
      param_flags |= param_flag_await;
      if(optional('*')) function_flags |= function_flag_generator;
   } else if(optional('*')) {
      function_flags |= function_flag_generator;
      param_flags |= param_flag_yield;
   } /*else if(token_length() == 3 && raw_char(2) == 't' && raw_char(1) == 'e'){
      if(raw_char(0) == 'g') {
         is_get_set = is_get = true;
         property_kind = property_kind_get;
         property_flags &= ~property_flag_method;
         property_flags |= method_flag_special; next();
      } else if(raw_char(0) == 's') {
         is_get_set = is_set = true;
         property_kind = property_kind_set;
         property_flags &= ~property_flag_method;
         property_flags |= method_flag_special; next();
      }
   }*/ else {
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
   {
      make_child_node(function_expression);
      assign(id, nullptr);
      expect('(');
      if(!is_get_set) {
         list_parse(params, unique_formal_parameters, YLD|AWT, param_flags);
      } else {
         if(is_set) { list_parse(params, property_set_parameter_list); }
      }
      expect(')');
      //expect('{'); list_parse(body, function_body, YLD|AWT, flags); expect('}');
      //list_parse(body, function_body_container, YLD|AWT, param_flags);
      parse(body, function_body_container, YLD|AWT, param_flags);
      assign(flags, function_flags);
      assign_to_parent(value, completed_node());
   }
   assign(kind, property_kind);
   assign(flags, property_flags);
   return_node();
}
method_definition_t* parse_method_definition(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   bool computed = false;
   //[NOTE] this criterion must be subject to review with grammar changes
   //    this criterion is valid as of ECMA2020
   if(offset_lookahead(1, '(') || (computed = exists('[')))
   {
      // MethodDefinition[Yield, Await]:
      //    PropertyName[?Yield, ?Await]
      //       ( UniqueFormalParameters[~Yield, ~Await] )
      //       { FunctionBody[~Yield, ~Await] }
      make_node(method_definition);
      uint8_t flags = (computed ? property_flag_computed: flag_none);
      uint8_t kind = (token_is(constructor) ? property_kind_constructor : property_kind_method);
      parse(key, property_name);
      if(exists('(')) {
         parse(value, method_function, YLD|AWT, NONE);
         flags |= property_flag_method;
      } else {
         passon(nullptr);
      }
      assign(kind, kind);
      assign(flags, flags);
      return_node();
   }
   passon_parsed(method_only_definition);
}
// ====== FUNCTIONS::YieldExpression ====== //
/*
YieldExpression[In, Await]:
   yield
   yield [no LineTerminator here] AssignmentExpression[?In, +Yield, ?Await]
   yield [no LineTerminator here] * AssignmentExpression[?In, +Yield, ?Await]
*/
void* parse_yield_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   uint8_t yield_flags = flag_none;
   make_node(yield_expression)
   expect_word(yield);
   if(!exists_newline()) {
      if(optional('*')) {
         yield_flags |= yield_flag_delegate;
         parse(argument, assignment_expression, NONE, YLD);
      } else {
         optional_parse(assignment_expression, NONE, YLD);
         if(assignment_expression) {
            assign(argument, assignment_expression);
         }
      }
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
void* parse_class_element_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   start_list();
   while(!exists('}')) {
      if(optional(';')) continue;
      uint8_t method_flags = 0;
      save_begin();
      // static is a valid method name in non-strict mode
      if(exists_word(static) && (
         (params & param_flag_strict_mode) ||
         offset_negative_lookahead(1, '(')
      )){
         ensure_word(static);
         method_flags = method_flag_static;
      }
      parse(method_definition);
      node_as(method_definition, method_definition, md);
      md->begin = begin;
      md->flags |= method_flags;
      add_to_list(method_definition);
   }
   passon(list_head());
}
void* parse_class_body(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(class_body);
   list_parse(body, class_element_list);
   return_node();
}
void* parse_class_body_container(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(class_body);
   expect('{'); list_parse(body, class_element_list); expect('}');
   return_node();
}
void* parse_class_declaration(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(class_declaration);
   expect_word(class);
   parse(id, binding_identifier);
   if(optional_word(extends)) {
      parse(super_class, lhs_expression);
   }
   //expect('{'); parse(body, class_body); expect('}');
   parse(body, class_body_container);
   return_node();
}
void* parse_class_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(class_expression);
   expect_word(class);
   if(exists_mask(mask_identifier)) {
      parse(id, binding_identifier);
   } else {
      assign(id, nullptr);
   }
   if(optional_word(extends)) {
      parse(super_class, lhs_expression);
   }
   //expect('{'); parse(body, class_body); expect('}');
   parse(body, class_body_container);
   return_node();
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
void* parse_spread_element(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(spread_element);
   ensure(pnct_spread);
   parse(argument, assignment_expression, NONE, IN);
   return_node();
}
void* parse_array_literal(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(array_expression);
   start_list();
   ensure('[');
   while(!exists(']')) {
      if(!exists(',')) {
         if(exists(pnct_spread)) {
            parse(spread_element);
            add_to_list(spread_element);
         } else {
            parse(assignment_expression, NONE, IN);
            add_to_list(assignment_expression);
         }
      } else {
         add_to_list(nullptr);
      }
      if(!optional(',')) break;
   };
   expect(']');
   //assign(elements, list_head());
   assign(elements, raw_list_head());
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
void* parse_object_literal(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   void* first_cover = nullptr;
   make_node(object_expression);
   start_list();
   ensure('{');
   while(!exists('}')) {
      // first resolve all productions that start with Identifier or IdentifierName
      //[NOTE] this criterion must be subject to review with grammar changes
      //    this criterion is valid as of ECMA2020
      if(offset_lookahead(1, ':') || offset_lookahead(1, '(') || exists('['))
      {
         // PropertyDefinitionList[Yield, Await]:
         //    PropertyName[?Yield, ?Await]
         //       : AssignmentExpression[+In, ?Yield, ?Await]
         // MethodDefinition[Yield, Await]:
         //    PropertyName[?Yield, ?Await]
         //       ( UniqueFormalParameters[~Yield, ~Await] )
         //       { FunctionBody[~Yield, ~Await] }
         make_node(property);
         uint8_t flags = (exists('[') ? property_flag_computed: flag_none);
         parse(key, property_name);
         if(optional(':')) {
            parse(value, assignment_expression, NONE, IN);
            if(node_has(offending_cover_grammar, node->value)){
               if(first_cover != nullptr) {
                  node_as(covered_parse_node, node->value, node_value);
                  first_cover = node_value->first_cover;
               }
            }
         } else if(exists('(')) {
            parse(value, method_function, YLD|AWT, NULL);
            flags |= property_flag_method;
         } else {
            passon(nullptr);
         }
         assign(kind, property_kind_init);
         assign(flags, flags);
         add_to_list(completed_node());
      } else if(exists(pnct_spread)) {
         // ... AssignmentExpression[+In, ?Yield, ?Await]
         make_node(spread_element);
         ensure(pnct_spread);
         parse(argument, assignment_expression, NONE, IN);
         add_to_list(completed_node());
      } else if(offset_lookahead(1, ',') || offset_lookahead(1, '}')) {
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
      //} else if(offset_lookahead(1, '=') && (params & cover_flag_initializer)) {
      } else if(offset_lookahead(1, '=')) {
         save_begin();
         make_node(property);
         assign(kind, property_kind_init);
         parse(identifier_reference);
         assign(key, identifier_reference);
         assign(flags, property_flag_shorthand);
         {
            //set_tree_flags(cover_flag_initializer);
            make_child_node(initialized_name);
            assign_begin();
            assign(left, identifier_reference);
            if(first_cover != nullptr) {
               first_cover = state->token;
            }
            ensure('=');
            //mask_tree_flags(cover_flag_initializer);
            parse(right, assignment_expression, NONE, IN);
            //set_tree_flags(cover_flag_initializer);
            assign_to_parent(value, completed_node());
         }
         add_to_list(completed_node());
      } else {
         parse(method_only_definition);
         set_node_type_of(method_only_definition, property);
         node_as(property, method_only_definition, property);
         if(!(property->flags & method_flag_special)) {
            property->kind = property_kind_init;
         }
         add_to_list(method_only_definition);
      }
      if(!optional(',')) break;
   };
   expect('}');
   assign(first_cover, first_cover);
   //assign(properties, list_head());
   assign(properties, raw_list_head());
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
void* parse_template_literal(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(template_literal);
   //start_list();
   start_named_list(quasis);
   start_named_list(expressions);
   ensure('`');
   while(true) {
      save_begin();
      token_t* token = nullptr;
      bool has_element = exists(tkn_template_string);
      if(has_element) {
         token = state->token;
         ensure(tkn_template_string);
      }
      bool is_tail = exists('`');
      make_node(template_element);
      assign_begin();
      assign(token, token);
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
/*
bool change_array_node_types(parse_list_node_t* list_node, bool for_assignment);
bool change_object_node_types(parse_list_node_t* list_node, bool for_assignment);
bool change_node_type(parse_node_t* node, bool for_assignment)
{
   if(node == nullptr) return false;
   switch(node_type(node)) {
      case pnt_assignment_pattern: break;
      case pnt_assignment_expression: {
         node_as(assignment_expression, node, ae);
         if(ae->operator_id != '=') return false;
         ae->type = pnt_assignment_pattern;
         break;
      }
      case pnt_array_expression: {
         node_as(array_expression, node, ae);
         ae->type = pnt_array_assignment_pattern;
         bool success = change_array_node_types(ae->elements, for_assignment);
         if(!success) return false;
         break;
      }
      case pnt_object_expression: {
         node_as(object_expression, node, oe);
         oe->type = pnt_object_assignment_pattern;
         bool success = change_object_node_types(oe->properties, for_assignment);
         if(!success) return false;
         break;
      }
      default: {
         if(!is_an_assignment_target(node)) return false;
      }
   }
   return true;
}
*/
bool change_node_types(parser_state_t* state, parse_list_node_t* list_node, uint8_t flags);
bool change_lhs_node_type(parser_state_t* state, void* node, uint8_t flags)
{
   switch(node_type(node)) {
      case pnt_array_expression:
      case pnt_array_assignment_pattern: {
         node_as(array_pattern, node, ap);
         ap->type = (flags & change_flag_binding ? pnt_array_pattern : pnt_array_assignment_pattern);
         uint8_t change_flags = set_change_flag_to(array, flags);
         return change_node_types(state, ap->elements, change_flags);
      }
      case pnt_object_expression:
      case pnt_object_assignment_pattern: {
         node_as(object_pattern, node, op);
         op->type = (flags & change_flag_binding ? pnt_object_pattern : pnt_object_assignment_pattern);
         uint8_t change_flags = set_change_flag_to(object, flags);
         return change_node_types(state, op->properties, change_flags);
      }
      default: return is_an_assignment_target(node);
   }
}
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
bool change_node_types(parser_state_t* state, parse_list_node_t* list_node, uint8_t flags)
{
   while(list_node != nullptr) {
      parse_node_t* parse_node = (parse_node_t*)(list_node->parse_node);
      if(parse_node != nullptr) {
         // get the RestElement argument
         bool is_rest = false;
         if(parse_node->type == pnt_spread_element) {
            is_rest = true;
            parse_node->type = pnt_rest_element;
            void* argument = node_as(spread_element, parse_node)->argument;
            if(!is_an_assignment_target(argument)) return_error(rest_argument, false);
            if(list_node->next != nullptr) return_error(middle_rest, false);
            if(flags & change_flag_object) {
               if(flags & change_flag_assignment) {
                  // 12.15.7.1: Static Semantics: Early Errors
                  //    AssignmentRestProperty: ... DestructuringAssignmentTarget
                  // It is a Syntax Error if DestructuringAssignmentTarget is an
                  // ArrayLiteral or an ObjectLiteral
                  uint8_t argument_type = node_type(argument);
                  if(argument_type == pnt_array_expression ||
                     argument_type == pnt_object_expression
                  ) return_error(object_assignment_rest, false);
                  break;
               }
               //return_error(missing_assignment_or_binding_flag, false);
            }
            parse_node = argument;
         }
         if(!is_rest && (flags & change_flag_object)) {
            if(!node_type_is(property, parse_node)) {
               return_error(is_not_a_property_node, false);
            }
            parse_node = node_as(property, parse_node)->value;
         }
         if(parse_node == nullptr) return_error(null_node_in_change_types, false);
         switch(node_type(parse_node)) {
            case pnt_initialized_name: break;
            case pnt_assignment_expression: {
               node_as(assignment_expression, parse_node, ae);
               if(ae->operator_id != '=') return_error(non_assignment, false);
               ae->type = pnt_assignment_pattern;
               if(flags & change_flag_binding) {
                  if(!change_lhs_node_type(state, ae->left, flags)) return false;
               }
               break;
            }
            case pnt_array_expression: {
               node_as(array_expression, parse_node, ae);
               ae->type = select_array_pattern_for(flags);
               //uint8_t change_flags = (flags & change_mask_cover) | change_flag_array;
               uint8_t change_flags = set_change_flag_to(array, flags);
               if(!change_node_types(state, ae->elements, change_flags)) return false;
               break;
            }
            case pnt_object_expression: {
               node_as(object_expression, parse_node, oe);
               oe->type = select_object_pattern_for(flags);
               //uint8_t change_flags = (flags & change_mask_cover) | change_flag_object;
               uint8_t change_flags = set_change_flag_to(object, flags);
               if(!change_node_types(state, oe->properties, change_flags)) return false;
               break;
            }
            default: {
               if(flags & change_flag_assignment) {
                  if(!is_an_assignment_target(parse_node)) {
                     return_error(lvalue, false);
                  }
               } else if(flags & change_flag_binding) {
                  //[TODO] check for binding-identifier not just identifier
                  if(node_type_is(rest_element, parse_node)) return true;
                  if(!node_type_is(identifier, parse_node)) {
                     return_error(binding_identifier, false);
                  }
               }
            }
         }
      } else {
         if(!(flags & change_flag_array)) return false;
      }
      //list_node = (parse_list_node_t*)(list_node->next);
      list_node = list_node->next;
   }
   return true;
}
/*
bool change_array_node_types(parse_list_node_t* list_node, bool for_assignment)
{
   bool has_rest = false;
   while(list_node != nullptr) {
      parse_node_t* parse_node = (parse_node_t*)(list_node->parse_node);
      if(parse_node != nullptr) {
         // get the RestElement argument
         if(parse_node->type == pnt_spread_element) {
            if(has_rest) return false;
            parse_node->type = pnt_rest_element;
            as(parse_node, se, spread_element);
            has_rest = true;
            if(list_node->next != nullptr) return false;
            parse_node = (parse_node_t*)(se->argument);
         }
         if(!change_node_type(parse_node, for_assignment)) return false;
      }
      list_node = (parse_list_node_t*)(list_node->next);
   }
   return true;
}
*/
void* parse_cover_array_assignment(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   parse(array_literal);
   if(exists('=')) {
      // reinterpret ArrayExpression as ArrayPattern
      node_as(array_expression, array_literal, ae);
      ae->type = pnt_array_assignment_pattern;
      //if(!change_array_node_types(ae->elements, true)) passon(nullptr);
      uint8_t change_flags = change_flag_array_assignment;
      if(!change_node_types(state, ae->elements, change_flags)) passon(nullptr);
   }
   passon(array_literal);
}
/*
bool change_object_node_types(parse_list_node_t* list_node, bool for_assignment)
{
   bool has_rest = false;
   while(list_node != nullptr) {
      parse_node_t* parse_node = (parse_node_t*)(list_node->parse_node);
      switch(parse_node->type) {
         case pnt_spread_element: {
            if(has_rest) return false;
            parse_node->type = pnt_rest_element;
            as(parse_node, se, spread_element);
            if(!is_an_assignment_target(se->argument)) return false;
            // 12.15.7.1: Static Semantics: Early Errors
            //    AssignmentRestProperty: ... DestructuringAssignmentTarget
            // It is a Syntax Error if DestructuringAssignmentTarget is an
            // ArrayLiteral or an ObjectLiteral
            uint8_t argument_type = node_type(se->argument);
            if(argument_type == pnt_array_expression ||
               argument_type == pnt_object_expression
            ) return false;
            if(list_node->next != nullptr) return false;
            has_rest = true;
            break;
         }
         default: {
            if(!node_type_is(property, parse_node)) return false;
            as(parse_node, property, property);
            if(!change_node_type(property->value, for_assignment)) return false;
         }
      }
      list_node = (parse_list_node_t*)(list_node->next);
   }
   return true;
}
*/
void* parse_cover_object_assignment(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   //save_and_mask_tree_flags(cover_flag_initializer);
   parse(object_literal, NONE, INIT);
   node_as(object_expression, object_literal, oe);
   if(exists('=')) {
      oe->type = pnt_object_assignment_pattern;
      //if(!change_object_node_types(oe->properties, true)) passon(nullptr);
      uint8_t change_flags = change_flag_object_assignment;
      if(!change_node_types(state, oe->properties, change_flags)) passon(nullptr);
   } else if(!(params & cover_flag_parameters)) {
       if(oe->first_cover != nullptr) {
         //[TODO] locate the offending CoverInitializedName
         passon(nullptr);
      }
   }
   //restore_tree_flags(cover_flag_initializer);
   passon(object_literal);
}
void* parse_this_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(this_expression); ensure_word(this); return_node();
}

/*
Expression[In, Yield, Await]:
   AssignmentExpression[?In, ?Yield, ?Await]
   Expression[?In, ?Yield, ?Await] , AssignmentExpression[?In, ?Yield, ?Await]
*/
void* parse_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
/*
bool change_binding_node_types(parse_list_node_t* list_node, bool for_assignment)
{
   bool has_rest = false;
   while(list_node != nullptr) {
      parse_node_t* parse_node = (parse_node_t*)(list_node->parse_node);
      if(parse_node != nullptr) {
         // get the RestElement argument
         if(parse_node->type == pnt_spread_element) {
            if(has_rest) return false;
            parse_node->type = pnt_rest_element;
            as(parse_node, se, spread_element);
            has_rest = true;
            if(list_node->next != nullptr) return false;
            parse_node = (parse_node_t*)(se->argument);
         }
         if(!change_node_type(parse_node, for_assignment)) return false;
      }
      list_node = (parse_list_node_t*)(list_node->next);
   }
   return true;
}
*/
void* parse_covered_parenthesized_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   size_t count = 0;
   token_t* trailing_comma = nullptr;
   void* first_cover = nullptr;
   save_begin();
   ensure('(');
   make_node(expression);
   start_list();
   while(!exists(')')) {
      ++count;
      trailing_comma = nullptr;
      if(exists(pnct_spread)) {
         if(first_cover != nullptr) {
            first_cover = state->token;
         }
         parse(binding_rest_element);
         add_to_list(binding_rest_element);
         break;
      }
      parse(assignment_expression, NONE, IN|PARAM);
      if(node_has(offending_cover_grammar, assignment_expression)) {
         if(first_cover != nullptr) {
            node_as(covered_parse_node, assignment_expression, expression);
            first_cover = expression->first_cover;
         }
      }
      add_to_list(assignment_expression);
      if(exists(',')) {
         trailing_comma = state->token;
         ensure(',');
      } else break;
   }
   assign(expressions, raw_list_head());
   expression_t* expression = completed_node();
   expect(')');
   if(!exists(pnct_arrow)) {
      //[TODO] generate error message
      if(count == 0 || trailing_comma != nullptr || first_cover != nullptr) {
         passon(nullptr);
      }
      make_node(parenthesized_expression);
      assign_begin();
      // reduce expression list to a single expression
      // [TODO] reuse memory used for expression list
      if(count == 1) expression = raw_list_head()->parse_node;
      assign(expression, expression);
      return_node();
   } else {
      // [TODO] reuse memory used for expression list
      if(count == 0) passon(&empty_list);
      uint8_t change_flags = change_flag_array_binding;
      if(!change_node_types(state, expression->expressions, change_flags)) {
         passon(nullptr);
      }
      passon(expression->expressions);
   }
}
/*
ParenthesizedExpression[Yield, Await]:
   ( Expression[+In, ?Yield, ?Await] )
*/
void* parse_parenthesized_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
void* parse_primary_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   switch(state->token->id) {
      case rw_this: passon_parsed(this_expression);
      case tkn_identifier: passon_parsed(identifier_reference);
      case rw_null: case rw_true: case rw_false:
      case tkn_numeric_literal:
      case tkn_string_literal: passon_parsed(literal);
      case tkn_regexp_literal: passon_parsed(regexp_literal);
      //case '[': passon_parsed(array_literal);
      case '[': passon_parsed(cover_array_assignment);
      //case '{': passon_parsed(object_literal);
      case '{': passon_parsed(cover_object_assignment);
      case rw_class: passon_parsed(class_expression);
      case '`': passon_parsed(template_literal, TAG, NONE);
      //case '(': passon_parsed(parenthesized_expression);
      case '(': passon_parsed(covered_parenthesized_expression);
      case rw_function: passon_parsed(function_expression, YLD|AWT, NONE);
      case rw_async: if(offset_lookahead(1, word(function))) {
         passon_parsed(function_expression, YLD|AWT, NONE);
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
void* parse_arguments_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   expect('(');
   start_list();
   while(!exists(')')) {
      if(exists(pnct_spread)) {
         make_node(spread_element);
         ensure(pnct_spread);
         parse(argument, assignment_expression, NONE, IN);
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
void* parse_member_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* continue_with_member_expression(parser_state_t* state, parser_tree_state_t* tree_state, void* object, size_t begin, uint8_t flag, params_t params);
void* parse_member_only_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   void* object = nullptr;
   switch(state->token->id) {
      case rw_super: {
         save_begin();
         make_node(super);
         ensure_word(super);
         object = completed_node();
         break;
      }
      case rw_new: {
         if(offset_lookahead(1, '.')) {
            make_node(meta_property);
            parse(meta, identifier_name);
            ensure('.');
            if(!token_matches(target)) passon(nullptr);
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
         expect('.');
         if(!token_matches(meta)) passon(nullptr);
         parse(property, identifier_name);
         object = completed_node();
         break;
      }
      default: passon(nullptr);
   }
   continue_with(member_expression, object, begin, flag_none);
   passon(member_expression);
}
void* continue_with_member_expression(parser_state_t* state, parser_tree_state_t* tree_state, void* object, size_t begin, uint8_t flag, params_t params)
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
void* parse_member_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   try(member_only_expression);
   parse(primary_expression);
   continue_with(member_expression, primary_expression, begin, flag_none);
   passon(member_expression);
}

/*
 * CallExpression[Yield, Await]:
 *    CoverCallExpressionAndAsyncArrowHead[?Yield, ?Await]
 *    SuperCall[?Yield, ?Await]
 *    ImportCall[?Yield, ?Await]
 *    CallExpression[?Yield, ?Await] Arguments[?Yield, ?Await]
 *    CallExpression[?Yield, ?Await] [ Expression[+In, ?Yield, ?Await] ]
 *    CallExpression[?Yield, ?Await] . IdentifierName
 *    CallExpression[?Yield, ?Await] TemplateLiteral[?Yield, ?Await, +Tagged]
 * SuperCall[Yield, Await]:
 *    super Arguments[?Yield, ?Await]
 * ImportCall[Yield, Await]:
 *    import ( AssignmentExpression[+In, ?Yield, ?Await] )
 * Arguments[Yield, Await]:
 *    ( )
 *    ( ArgumentList[?Yield, ?Await] )
 *    ( ArgumentList[?Yield, ?Await] , )
 * ArgumentList[Yield, Await]:
 *    AssignmentExpression[+In, ?Yield, ?Await]
 *    ... AssignmentExpression[+In, ?Yield, ?Await]
 *    ArgumentList[?Yield, ?Await] , AssignmentExpression[+In, ?Yield, ?Await]
 *    ArgumentList[?Yield, ?Await] , ... AssignmentExpression[+In, ?Yield, ?Await]
 * CoverCallExpressionAndAsyncArrowHead:
 * CallMemberExpression[Yield, Await]:
 *    MemberExpression[?Yield, ?Await] Arguments[?Yield, ?Await]
 */
void* parse_call_only_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   if(exists_word(super)) {
      if(offset_negative_lookahead(1, '(')) passon(nullptr);
      make_node(call_expression);
      {
         make_child_node(super);
         ensure_word(super);
         assign_to_parent(callee, completed_node());
      }
      list_parse(arguments, arguments_list);
      return_node();
   } else if(exists_word(import)) {
      if(offset_negative_lookahead(1, '.')) passon(nullptr);
      make_node(import_expression);
      ensure_word(import); expect('(');
         parse(source, assignment_expression, NONE, IN);
      expect(')');
      return_node();
   } else {
      passon(nullptr);
   }
}
void* continue_with_call_expression(parser_state_t* state, parser_tree_state_t* tree_state, void* callee, size_t begin, uint8_t flag, params_t params)
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
         continue_with(call_expression, result_node, begin, flag_none);
         result_node = call_expression;
      } else if(exists('[') || exists('.') || exists('`')) {
         continue_with(member_expression, result_node, begin, flag_none);
         result_node = member_expression;
      } else {
         passon(result_node);
      }
   }
   passon(nullptr);
}
void* parse_call_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   try(call_only_expression);
   parse(member_expression);
   continue_with(call_expression, member_expression, begin, flag_none);
   passon(call_expression);
}

/*
 * NewExpression[Yield, Await]:
 *    MemberExpression[?Yield, ?Await]
 *    new NewExpression[?Yield, ?Await]
 */
/* looks redundant given MemberExpression
void* parse_new_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* parse_new_only_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   if(!exists_word(new) || offset_lookahead(1, '.')) passon(nullptr);
   make_node(new_expression);
   next();
   parse(expression, new_expression);
   return_node();
}
void* parse_new_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
void* continue_with_optional_expression(parser_state_t* state, parser_tree_state_t* tree_state, void* left, size_t begin, params_t params)
{
   make_node(chain_expression);
   assign_begin();
   while(left != nullptr && optional(pnct_optional)) {
      uint8_t flag = optional_flag_optional;
      if(!exists('(')) {
         continue_with(member_expression, left, begin, flag);
         left = member_expression;
         flag = flag_none;
      }
      if(exists('(')) {
         continue_with(call_expression, left, begin, flag);
         left = call_expression;
      }
   }
   assign(expression, left);
   return_node();
}

/*
 * LeftHandSideExpression[Yield, Await]:
 *    NewExpression[?Yield, ?Await]
 *    CallExpression[?Yield, ?Await]
 *    OptionalExpression[?Yield, ?Await]
 */
void* parse_lhs_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   //try(new_only_expression);
   try(call_only_expression);
   parse(member_expression);
   if(exists('(')) {
      continue_with(call_expression, member_expression, begin, flag_none);
      passon(call_expression);
   } else if(exists(pnct_optional)) {
      continue_with(optional_expression, member_expression, begin);
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
void* parse_unary_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* parse_update_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   if(exists_mask(mask_update_ops)) {
      make_node(update_expression);
      assign_operator();
      ensure_mask(mask_update_ops);
      parse(argument, unary_expression);
      assign(flags, operator_flag_prefix);
      return_node();
   } else {
      save_begin();
      parse(lhs_expression);
      if(exists_newline() || !exists_mask(mask_update_ops)) {
         passon(lhs_expression);
      }
      make_node(update_expression);
      assign_begin();
      shift(argument, lhs_expression);
      assign_operator();
      ensure_mask(mask_update_ops);
      assign(flags, flag_none);
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
void* parse_unary_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* parse_await_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(await_expression);
   ensure_word(await);
   parse(argument, unary_expression, NONE, AWT);
   return_node();
}
void* parse_unary_only_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   if(exists_mask(mask_unary_ops)) {
      make_node(unary_expression);
      assign_operator();
      assign(flags, operator_flag_prefix);
      ensure_mask(mask_unary_ops);
      parse(argument, unary_expression);
      return_node();
   } else if(exists_word(await) && (params & param_flag_await)) {
      passon_parsed(await_expression, AWT, NONE);
   }
   passon(nullptr);
}
void* parse_unary_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
   as(node->right, right, binary_expression);
   //if(!reduces_to(node->right, logical_expression)) return node;
   // adjust justification and precedence operators
   int sign = precedence(node->operator) - precedence(right->operator);
   if((sign > 0) || (sign == 0 && is_right)) return node;
   //printf("swapping\n");
   as(right->left, right_left, parse_node);
   node->end = right_left->end;
   right->begin = node->begin;
   node->right = right->left;
   right->left = precedence_adjusted(node, is_right);
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
void* parse_exponentiation_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   try(unary_only_expression);
   parse(update_expression);
   if(!exists(pnct_exponentitation)) {
      passon(update_expression);
   }
   make_node(binary_expression);
   assign_begin();
   shift(left, update_expression);
   assign_operator();
   ensure(pnct_exponentitation);
   parse(right, exponentiation_expression);
   complete_node();
   passon(precedence_adjusted(node, true));
}

void* parse_binary_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
   shift(left, exponentiation_expression);
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
void* parse_logical_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* continue_with_logical_expression(parser_state_t* state, parser_tree_state_t* tree_state, void* binary_expression, size_t begin, params_t params)
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
void* parse_logical_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(binary_expression);
   if(!exists_mask(mask_logical_ops)) passon(binary_expression);
   continue_with(logical_expression, binary_expression, begin);
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
void* parse_coalesce_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params);
void* continue_with_coalesce_expression(parser_state_t* state, parser_tree_state_t* tree_state, void* binary_expression, size_t begin, params_t params)
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
void* parse_coalesce_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(binary_expression);
   if(!exists_mask(pnct_logical_coalesce)) passon(binary_expression);
   continue_with(coalesce_expression, binary_expression, begin);
   passon(coalesce_expression);
}

/*
ShortCircuitExpression[In, Yield, Await]:
   LogicalORExpression[?In, ?Yield, ?Await]
   CoalesceExpression[?In, ?Yield, ?Await]
*/
void* parse_short_circuit_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(binary_expression);
   if(exists_mask(mask_logical_ops)) {
      continue_with(logical_expression, binary_expression, begin);
      passon(logical_expression);
   } else if(exists(pnct_logical_coalesce)) {
      continue_with(coalesce_expression, binary_expression, begin);
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
void* parse_conditional_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   save_begin();
   parse(short_circuit_expression);
   if(!optional('?')) passon(short_circuit_expression);
   make_node(conditional_expression);
   assign_begin();
   shift(test, short_circuit_expression);
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
   parser_state_t* state, parser_tree_state_t* tree_state,
   arrow_function_expression_t* node, size_t begin, params_t add_params, params_t params
){
   ensure(pnct_arrow);
   if(exists('{')) {
      parse(body, function_body_container, YLD|AWT, add_params);
   } else {
      node->flags |= function_flag_expression;
      parse(body, assignment_expression, YLD|AWT, add_params);
   }
   return_node();
}
void* parse_arrow_function(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(arrow_function_expression);
   params_t add_params = flag_none;
   uint8_t function_flags = flag_none;
   if(optional_word(async)) {
      function_flags |= function_flag_async;
      add_params |= param_flag_await;
   }
   if(exists('(')) {
      ensure('('); list_parse(params, unique_formal_parameters); expect(')');
   } else {
      start_list();
      parse(binding_identifier);
      add_to_list(binding_identifier);
      assign(params, list_head());
   }
   /*
   if(exists('{')) {
      parse(body, function_body_container, YLD|AWT, add_params);
   } else {
      function_flags |= function_flag_expression;
      parse(body, expression, YLD|AWT, add_params);
   }
   assign(flags, function_flags);
   return_node();
   */
   assign(flags, function_flags);
   size_t begin = 0;
   continue_with(arrow_function, node, begin, add_params);
   passon(arrow_function);
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
void* parse_assignment_expression(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   void* expression = nullptr;
   save_begin();
   if((params & param_flag_yield) && exists_word(yield)) {
      passon_parsed(yield_expression, YLD, NONE);
   } else {
      size_t offset = (exists_word(async) ? 1 : 0);
      if((offset_lookahead(offset + 1, pnct_arrow) &&
          ((state->token + offset + 0)->group & mask_identifier)) ||
         (offset == 1 && offset_lookahead(offset, '('))
      ){
         passon_parsed(arrow_function);
      } else {
         assign_parsed(conditional_expression, expression);
      }
   }
   if(exists(pnct_arrow)) {
      make_node(arrow_function_expression);
      assign_begin();
      assign(flags, flag_none);
      assign(params, (expression == &empty_list ? nullptr : expression));
      continue_with(arrow_function, node, begin, 0);
      passon(arrow_function);
   }
   if(!node_is_a(lhs_production, expression) || !exists_mask(mask_assign_ops)) {
      passon(expression);
   }
   make_node(assignment_expression);
   assign_begin();
   shift(left, expression);
   assign_operator();
   ensure_mask(mask_assign_ops);
   if(!is_an_assignment_target(expression)) {
      set_error(lvalue); passon(nullptr);
   }
   if((params & param_flags_to_reset_on_assign) && node->operator_id == '=') {
   //if((params & cover_flag_initializer) && node->operator_id == '=') {
      //save_and_mask_tree_flags(cover_flag_initializer);
      parse(right, assignment_expression, param_flags_to_reset_on_assign, flag_none);
      //restore_tree_flags(cover_flag_initializer);
   } else {
      parse(right, assignment_expression);
   }
   return_node();
}

// ============ STATEMENTS ============= //
#define parse_semicolon() { \
   if(exists(';')) { \
      ensure(';'); \
   } else { \
      if(!exists('}') && !exists(tkn_eot) && !exists_newline()) expect(';'); \
   } \
}

/*
BlockStatement[Yield, Await, Return]:
   Block[?Yield, ?Await, ?Return]
Block[Yield, Await, Return]:
   { StatementList[?Yield, ?Await, ?Return]opt }
*/
void* parse_block_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(block_statement);
   expect('{'); list_parse(body, block_statement_list); expect('}');
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
void* parse_lexical_binding_list(parser_state_t* state, parser_tree_state_t* tree_state, uint8_t token_id, params_t params)
{
   start_list();
   bool first_element = true;
   params_t optional_binding_init = params & param_flag_for_binding;
   params = make_params(param_flag_for_binding, NULL);
   do {
      make_node(variable_declarator);
      if(exists_mask(mask_identifier)) {
         parse(id, binding_identifier);
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
            parse(init, assignment_expression);
         } else {
            assign(init, nullptr);
         }
      } else {
         parse(id, binding_pattern);
         if(first_element && !exists('=') && optional_binding_init) {
            if(!exists_word(in) && !exists_word(of)) {
               return_error(missing_binding_initializer, nullptr);
            }
            assign(init, nullptr);
            add_to_list(completed_node());
            passon(list_head());
         } else {
            expect('='); // error: missing_binding_initializer
            parse(init, assignment_expression);
         }
      }
      add_to_list(completed_node());
      first_element = false;
   } while(optional(','));
   passon(list_head());
}
void* parse_variable_statement(parser_state_t* state, parser_tree_state_t* tree_state, uint8_t reserved_word, params_t params)
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
void* parse_var_variable_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   return parse_variable_statement(state, tree_state, word(var), make_params(NONE, IN));
}
void* parse_let_variable_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   if(!is_let_a_keyword()){ passon(nullptr); }
   return parse_variable_statement(state, tree_state, word(let), params);
}
void* parse_const_variable_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   return parse_variable_statement(state, tree_state, word(const), params);
}
/*
EmptyStatement:
   ;
*/
void* parse_empty_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
void* parse_expression_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
*/
void* parse_if_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(if_statement);
   ensure_word(if); expect('(');
      parse(test, expression, RET, IN);
   expect(')');
   parse(consequent, statement);
   if(optional_word(else)) {
      parse(alternate, statement);
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
void* parse_do_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(do_statement);
   ensure_word(do); parse(body, statement);
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
void* parse_while_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(while_statement);
   ensure_word(while); expect('(');
      parse(test, expression, RET, IN);
   expect(')');
   parse(body, statement);
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
void* parse_for_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   ///*
   void* production = nullptr;
   bool is_await = false;
   bool is_declarator = false;
   bool in_of_possible = true;
   save_begin();
   ensure_word(for);
   is_await = optional_word(await);
   expect('(');
   if(!is_await && exists(';')) {
      in_of_possible = false;
   } else {
      if(is_await && !(params & param_flag_await)) {
         return_error(unexpected_await, nullptr);
      }
      if(exists_mask(mask_variable_declarator) &&
         (!exists_word(let) || is_let_a_keyword())
      ){
         is_declarator = true;
         uint8_t declarator_id = current_token_id;
         make_node(variable_declaration);
         production = node;
         assign(kind, declarator_id);
         ensure_mask(mask_variable_declarator);
         parse_with_arg(declarator_id, declarations, lexical_binding_list, IN, param_flag_for_binding);
         complete_node();
         as(node->declarations, declarations, parse_list_node);
         as(declarations->parse_node, declarator, variable_declarator);
         if((declarations->next == nullptr) && // has only one declartion
            (declarator->init == nullptr || // has no initializer
             allow_annex() && declarator_id == word(var)) // legacy initialization
         ){
            in_of_possible = true;
         }
      } else if(is_await) {
         parse(lhs_expression, RET, NONE);
         production = lhs_expression;
      } else {
         parse(expression, IN, NONE);
         production = expression;
         in_of_possible = node_is_a(lhs_production, expression);
      }
   }
   if((is_await || in_of_possible) && exists_word(of)) {
      expect_word(of);
      make_node(for_of_statement);
      assign_begin();
      if(!is_declarator && !change_lhs_node_type(state, production, change_flag_assignment)) {
         passon(nullptr);
      }
      assign(left, production);
      parse(right, assignment_expression, RET, IN);
      assign(flags, (is_await ? for_flag_await : flag_none));
      expect(')');
      parse(body, statement);
      return_node();
   } else if(in_of_possible && optional_word(in)) {
      make_node(for_in_statement);
      assign_begin();
      if(!is_declarator && !change_lhs_node_type(state, production, change_flag_assignment)) {
         passon(nullptr);
      }
      assign(left, production);
      parse(right, expression, RET, IN);
      expect(')');
      parse(body, statement);
      return_node();
   } else {
      make_node(for_statement);
      assign_begin();
      assign(init, production);
      expect(';');
      if(!exists(';')) { parse(test, expression); } expect(';');
      if(!exists(')')) { parse(update, expression); } expect(')');
      parse(body, statement);
      return_node();
   }
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
            assign(kind, state->token->id);
            ensure_mask(mask_variable_declarator);
            parse_with_arg(state->token->id, declarations, lexical_binding_list);
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
void* parse_continue_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(continue_statement);
   ensure_word(continue);
   if(!exists('}')) {
      //if(!exists(';')) expect_mask(mask_idname);
      if(!exists(';') && !exists_newline()) {
         parse(label, label_identifier);
      }
      parse_semicolon();
      //expect(';');
      //if(!exists('}')) expect(';');
   }
   return_node();
}
/*
BreakStatement[Yield, Await]:
   break ;
   break [no LineTerminator here] LabelIdentifier[?Yield, ?Await] ;
*/
void* parse_break_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(break_statement);
   ensure_word(break);
   if(!exists('}')) {
      //if(!exists(';')) expect_mask(mask_idname);
      if(!exists(';') && !exists_newline()) {
         parse(label, label_identifier);
      }
      parse_semicolon();
      //expect(';');
      //if(!exists('}')) expect(';');
   }
   return_node();
}
/*
ReturnStatement[Yield, Await]:
   return ;
   return [no LineTerminator here] Expression[+In, ?Yield, ?Await] ;
*/
void* parse_return_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(return_statement);
   ensure_word(return);
   if(!exists('}')) {
      if(!exists(';') && !exists_newline()) {
         parse(argument, expression, NONE, IN);
      }
      parse_semicolon();
      //expect(';');
      //if(!exists('}')) expect(';');
   }
   return_node();
}
/*
WithStatement[Yield, Await, Return]:
   with ( Expression[+In, ?Yield, ?Await] ) Statement[?Yield, ?Await, ?Return]
*/
void* parse_with_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(with_statement);
   ensure_word(with); expect('(');
      parse(object, expression, RET, IN);
   expect(')'); parse(body, statement);
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
void* parse_case_clause_list(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   bool has_default = false;
   start_list();
   while(true) {
      if(exists_word(case)) {
         make_node(case_clause);
         ensure_word(case);
         parse(test, expression, RET, IN);
         expect(':');
         list_parse(consequent, case_clause_statement_list);
         add_to_list(completed_node());
      } else if(!has_default && exists_word(default)) {
         make_node(case_clause);
         ensure_word(default);
         assign(test, nullptr);
         expect(':');
         list_parse(consequent, case_clause_statement_list);
         add_to_list(completed_node());
      } else {
         passon(list_head());
      }
   }
}
void* parse_switch_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(switch_statement);
   ensure_word(switch); expect('(');
      parse(discriminant, expression, RET, IN);
   expect(')'); expect('{');
      list_parse(cases, case_clause_list);
   expect('}');
   return_node();
}
/*
LabelledStatement[Yield, Await, Return]:
   LabelIdentifier[?Yield, ?Await] : LabelledItem[?Yield, ?Await, ?Return]
LabelledItem[Yield, Await, Return]:
   Statement[?Yield, ?Await, ?Return]
   FunctionDeclaration[?Yield, ?Await, ~Default]
*/
void* parse_labeled_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(labeled_statement);
   parse(label, label_identifier, RET, NONE); expect(':');
   optional_parse(function_declaration, DEF|RET, NONE);
   if(function_declaration) {
      assign(body, function_declaration);
   } else {
      parse(body, statement);
   }
   return_node();
}
/*
ThrowStatement[Yield, Await]:
   throw [no LineTerminator here] Expression[+In, ?Yield, ?Await] ;
*/
void* parse_throw_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
void* parse_try_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(try_statement);
   ensure_word(try);
   parse(block, block_statement);
   if(exists_word(catch)) {
      make_child_node(catch_clause);
      ensure_word(catch);
      if(optional('(')) {
         if(exists_mask(mask_identifier)) {
            parse(param, binding_identifier, RET, NONE);
         } else {
            parse(param, binding_pattern, RET, NONE);
         }
         expect(')');
      }
      parse(body, block_statement);
      assign_to_parent(handler, completed_node());
   } else {
      assign(handler, nullptr);
   }
   if(optional_word(finally)) {
      parse(finalizer, block_statement);
   } else {
      assign(finalizer, nullptr);
   }
   return_node();
}
/*
DebuggerStatement:
   debugger ;
*/
void* parse_debugger_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
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
void* parse_declaration(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   switch(state->token->id) {
      case rw_function: passon_parsed(function_declaration, DEF, NONE);
      case rw_class: passon_parsed(class_declaration, DEF, NONE);
      case rw_let: passon_parsed(let_variable_statement, DEF, IN);
      case rw_const: passon_parsed(const_variable_statement);
      case rw_async: if(offset_lookahead(1, word(function))) {
         passon_parsed(function_declaration, DEF, NONE);
      } // fallthrough
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
void* parse_statement(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   switch(state->token->id) {
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
         else { passon(nullptr); }
      }
      case rw_with: passon_parsed(with_statement);
      case rw_throw: passon_parsed(throw_statement, RET, NONE);
      case rw_try: passon_parsed(try_statement);
      case rw_debugger: passon_parsed(debugger_statement);
      default: {
         if(exists_mask(mask_identifier) && offset_lookahead(1, ':')) {
            passon_parsed(labeled_statement);
         } else if(exists_mask(mask_expression_exclusions)) {
            if(exists_word(async)) {
               token_t* token = (state->token + 1);
               if(token->id == word(function) && (token->flags & token_flag_newline)) {
                  passon(nullptr);
               }
            } else if(exists_word(let)) {
               if(offset_lookahead(1, '[')) { passon(nullptr); }
            } else {
               passon(nullptr);
            }
         }
         passon_parsed(expression_statement, RET, NONE);
      }
   }
}

program_t* parse_code(parser_state_t* state, parser_tree_state_t* tree_state, params_t params)
{
   make_node(program);
   //print_token();
   assign(source_type, program_kind_script);
   list_parse(body, script_body);
   //print_token();
   complete_node();
   //log_node(node, node->begin, node->end, node->type, node->body);
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
#undef negative_lookahead2

#undef is
#undef as

#undef start_list
#undef add_to_list
#undef list_head

parser_result_t parse(char_t const* source_begin, char_t const* source_end)
{
   size_t source_length = source_end - source_begin;
   scan_result_t result = tokenize(source_begin, source_end);
   if_debug(if(result.return_value == 1) print_string("tokenization successful\n");)
   if_debug(print_string("parsing begins\n");)
   parser_state_t state = {
      .buffer = source_begin,
      .tokens = result.tokens,
      .token = result.tokens,
      .expected_token_id = 0,
      .expected_mask = 0,
      .error_message = nullptr,
      .depth = 0,
      .memory = {.head = nullptr, .current = nullptr, .available = 0, .page_count = 0}
   };
   parser_tree_state_t tree_state = {.flags = 0};
   //init_named_list(state.aggregator.array.spread);
   //init_named_list(state.aggregator.array.assignment);
   //init_named_list(state.aggregator.array.pattern)
   //printf("%p begin: %zu end: %zu\n", state.tokens, (state.tokens + 1)->begin, (state.tokens + 1)->end);
   program_t* program = parse_code(&state, &tree_state, 0);
   //printf("%p begin: %zu end: %zu\n", state.tokens, (state.tokens + 1)->begin, (state.tokens + 1)->end);
   //printf("length = %d\n", program->end - program->begin);
   if(program != nullptr) {
      program->begin = 0; program->end = source_length;
   }
   /*
   #ifdef debug
   if(program == nullptr) {
      size_t begin = state.token->begin;
      int length = state.token->end - begin;
      printf("\nparsing failed at character index %zu %.*s\n", begin, length, state.buffer + begin);
      if(state.error_message != nullptr) {
         printf("%s\n", state.error_message);
      }
      printf("token found: %x %x %c\n", state.token->id, state.token->group, state.token->id);
      printf("token expected: %x %c\n", state.expected_token_id, state.expected_token_id);
   } else {
      printf("parsing successful: page_count = %zu\n", state.memory.page_count);
   }
   #endif
   //*/
   return (parser_result_t){
      .program = program,
      .state = state,
      .token_result = result,
      .return_value = (program != nullptr)
   };
}

#endif //_PARSER_H_
