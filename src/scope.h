#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <stdint.h>
#include <stdbool.h>
#include "constants.h"

#ifdef DBGMEM
   uint32_t scope_count = 0;
   uint32_t symbol_count = 0;
#endif
uint16_t const symbol_first_letter_bits = 5;
uint16_t const symbol_length_bits = 5;
uint16_t const hash_bits = symbol_first_letter_bits + symbol_length_bits;
uint16_t const symbol_first_letter_mask = (1 << symbol_first_letter_bits) - 1;
uint16_t const symbol_length_mask = (1 << symbol_length_bits) - 1;
uint16_t const symbol_hash_table_size = 1 << hash_bits;

uint16_t symbol_hash(parse_state_t const* state, identifier_t const* identifier)
{
   string_t const* const symbol_string = (
      identifier->compiled_string
         ? (string_t*)(identifier->compiled_string)
         : (string_t*)(identifier)
   );
   size_t const symbol_length = symbol_string->end - symbol_string->begin;
   symbol_hash_t hash = (
      ((symbol_length & symbol_length_mask) << 5) |
      (*symbol_string->begin & symbol_first_letter_mask)
   );
   return hash;
}

uint8_t symbol_matches(
   identifier_t const* const compare_identifier,
   string_t const* const symbol_string,
   size_t const symbol_length
){
   string_t const* const compare_string = (
      compare_identifier->compiled_string
         ? (string_t*)(compare_identifier->compiled_string)
         : (string_t*)(compare_identifier)
   );
   size_t const compare_symbol_length = compare_string->end - compare_string->begin;
   return (
      symbol_length == compare_symbol_length &&
      strncmp_impl(symbol_string->begin, compare_string->begin, symbol_length) == 0
   );
}

uint8_t _get_symbol(
   string_t const* const symbol_string, size_t const symbol_length,
   uint16_t hash, symbol_list_node_t** symbol_list_node_ref
){
   symbol_list_node_t* symbol_list_node = *symbol_list_node_ref;
   while(symbol_list_node) {
      identifier_t const* const compare_identifier = symbol_list_node->symbol->identifier;
      if(symbol_matches(compare_identifier, symbol_string, symbol_length)) {
         *symbol_list_node_ref = symbol_list_node;
         return 1;
      }
      symbol_list_node = symbol_list_node->next;
   }
   return 0;
}

uint8_t get_symbol_from_child_var_tree(
   scope_list_node_t** scope_list_node_ref,
   string_t const* const symbol_string, size_t const symbol_length,
   uint16_t hash, symbol_list_node_t** symbol_list_node_ref
){
   uint8_t has_symbol = 0;
   scope_list_node_t* scope_list_node = *scope_list_node_ref;
   scope_child_list_node_t* scope_child_list_node = scope_list_node->child_list.head;
   while(!has_symbol && scope_child_list_node) {
      *scope_list_node_ref = scope_child_list_node->scope_list_node;
      // do not descend into child hoisting scopes
      if(!((*scope_list_node_ref)->scope->flags & scope_flag_hoisting)) {
         has_symbol = get_symbol_from_child_var_tree(
            scope_list_node_ref, symbol_string, symbol_length, hash, symbol_list_node_ref
         );
      }
      scope_child_list_node = scope_child_list_node->next;
   }
   if(!has_symbol) {
      *scope_list_node_ref = scope_list_node;
      symbol_list_t* symbol_list = scope_list_node->scope->var_symbol_table[hash];
      if(symbol_list) {
         *symbol_list_node_ref = symbol_list->head;
         has_symbol = _get_symbol(symbol_string, symbol_length, hash, symbol_list_node_ref);
      }
   }
   return has_symbol;
}

#ifdef COMPILER
uint8_t get_symbol_from_hoisting_var_tree(
   scope_list_node_t** scope_list_node_ref,
   string_t const* const symbol_string, size_t const symbol_length,
   uint16_t hash, symbol_list_node_t** symbol_list_node_ref
){
   uint8_t has_symbol = get_symbol_from_child_var_tree(
      scope_list_node_ref, symbol_string, symbol_length, hash, symbol_list_node_ref
   );
   if(!has_symbol) {
      symbol_list_t* symbol_list = (*scope_list_node_ref)->scope->var_symbol_table[hash];
      if(symbol_list) {
         *symbol_list_node_ref = symbol_list->head;
         has_symbol = _get_symbol(symbol_string, symbol_length, hash, symbol_list_node_ref);
      }
   }
   return has_symbol;
}
#endif

uint8_t get_symbol_from_lexical_tree(
   scope_list_node_t** scope_list_node_ref,
   string_t const* const symbol_string, size_t const symbol_length,
   uint16_t hash, symbol_list_node_t** symbol_list_node_ref
){
   uint8_t has_symbol = get_symbol_from_child_var_tree(
      scope_list_node_ref, symbol_string, symbol_length, hash, symbol_list_node_ref
   );
   if(!has_symbol) {
      symbol_list_t* symbol_list = (*scope_list_node_ref)->scope->lexical_symbol_table[hash];
      if(symbol_list) {
         *symbol_list_node_ref = symbol_list->head;
         has_symbol = _get_symbol(symbol_string, symbol_length, hash, symbol_list_node_ref);
      }
   }
   return has_symbol;
}

#ifdef COMPILER
// has an odd behavior that at hoisting scope it include all var symbols
symbol_t const* get_symbol_from_scope(
   scope_list_node_t** scope_list_node_ref, identifier_t const* identifier
){
   string_t const* const symbol_string = (
      identifier->compiled_string
         ? (string_t*)(identifier->compiled_string)
         : (string_t*)(identifier)
   );
   size_t const symbol_length = symbol_string->end - symbol_string->begin;
   symbol_hash_t hash = (
      ((symbol_length & symbol_length_mask) << 5) |
      (*symbol_string->begin & symbol_first_letter_mask)
   );

   scope_t const* scope = (*scope_list_node_ref)->scope;
   symbol_list_node_t* symbol_list_node;
   {
      bool has_symbol = false;
      if(scope->flags & scope_flag_hoisting) {
         has_symbol = get_symbol_from_hoisting_var_tree(
            scope_list_node_ref, symbol_string, symbol_length, hash, &symbol_list_node
         );
      } else {
         symbol_list_t* symbol_list = scope->var_symbol_table[hash];
         if(symbol_list) {
            symbol_list_node = symbol_list->head;
            has_symbol = _get_symbol(symbol_string, symbol_length, hash, &symbol_list_node);
         }
      }
      if(has_symbol) return symbol_list_node->symbol;
   }
   {
      symbol_list_t* symbol_list = scope->lexical_symbol_table[hash];
      if(symbol_list) {
         symbol_list_node = symbol_list->head;
         bool has_symbol = _get_symbol(symbol_string, symbol_length, hash, &symbol_list_node);
         if(has_symbol) return symbol_list_node->symbol;
      }
   }
   return nullptr;
}
void _insert_reference(parse_state_t* state, identifier_t* reference, symbol_t const* resolved_symbol)
{
   reference->flags |= identifier_flag_reference;
   location_t const* const location = reference->location;
   location_t const* const symbol_location = resolved_symbol->identifier->location;
   scope_t* current_scope = state->current_scope_list_node->scope;
   scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
   reference_list_node_t* reference_list_node =
      parser_malloc(mm_reference_list_nodes, sizeof(reference_list_node_t));
   *reference_list_node = (reference_list_node_t){
      .reference = reference, .resolved_symbol = resolved_symbol,
      .scope_list_node = state->current_scope_list_node,
      .prev = nullptr, .next = nullptr
   };
   reference_list_node_t* target_reference_list_node = nullptr;
   if(resolved_symbol) {
      if(resolved_symbol->binding_flag & binding_flag_hoisted) {
         target_reference_list_node = hoisting_scope->resolved_reference_list.tail;
         if(!target_reference_list_node) {
            hoisting_scope->resolved_reference_list.head = reference_list_node;
         }
         hoisting_scope->resolved_reference_list.tail = reference_list_node;
      } else {
         target_reference_list_node = current_scope->resolved_reference_list.tail;
         if(!target_reference_list_node) {
            current_scope->resolved_reference_list.head = reference_list_node;
         }
         current_scope->resolved_reference_list.tail = reference_list_node;
      }
   } else {
      target_reference_list_node = hoisting_scope->unresolved_reference_list.tail;
      if(!target_reference_list_node) {
         hoisting_scope->unresolved_reference_list.head = reference_list_node;
      }
      hoisting_scope->unresolved_reference_list.tail = reference_list_node;
      if(!current_scope->unresolved_reference_list.head) {
         current_scope->unresolved_reference_list.head = reference_list_node;
      }
      // tail will be left as nullptr for non-hoisting scopes
      // all scopes have a unique tail which can be obtained from hoisting scope
   }
   if(!target_reference_list_node) return;
   target_reference_list_node->next = reference_list_node;
   reference_list_node->prev = target_reference_list_node;
}
void resolve_reference(parse_state_t* state, identifier_t* identifier) //bool
{
   scope_list_node_t* scope_list_node = state->current_scope_list_node;
   symbol_t const* symbol = get_symbol_from_scope(&scope_list_node, identifier);
   printf("%*s %10s reference %.*s(%d:%d)\n", scope_list_node->depth + 1, "", (symbol ? "resovled" : "unresolved"), (int)(identifier->end - identifier->begin), identifier->begin, identifier->location->begin.line, identifier->location->begin.column); fflush(stdout);
   _insert_reference(state, identifier, symbol);
}
bool re_resolve_reference(parse_state_t* state, reference_list_node_t* reference_list_node)
{
   identifier_t* reference = reference_list_node->reference;
   scope_list_node_t* resolved_scope_list_node = state->current_scope_list_node;
   scope_t* current_scope = resolved_scope_list_node->scope;
   scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
   symbol_t const* resolved_symbol = get_symbol_from_scope(&resolved_scope_list_node, reference);
   if(!resolved_symbol) return false;
   scope_t* target_scope = (
      resolved_symbol->binding_flag & binding_flag_hoisted
         ? hoisting_scope : current_scope
   );
   char const* re_resolution_type = "";
   if(reference->flags & identifier_flag_possible_closure) {
      reference->flags |= identifier_flag_closure;
      reference->flags ^= identifier_flag_possible_closure;
      if(!(resolved_symbol->identifier->flags & identifier_flag_closure)) {
         resolved_symbol->identifier->flags |= identifier_flag_closure;
         target_scope->symbol_layout->stack_size += sizeof(any_t*) - sizeof(any_t);
         target_scope->symbol_layout->closure_export_size += sizeof(any_t*);
         target_scope->symbol_layout->closure_offset -= sizeof(any_t);
         if(resolved_symbol->identifier->flags & identifier_flag_initialize) {
            target_scope->symbol_layout->init_size -= sizeof(any_t);
         }
         re_resolution_type = "closure";
      }
   } else if(!(resolved_symbol->identifier->flags & (identifier_flag_closure | identifier_flag_initialize))) {
      // determine if initialization required for the symbol
      bool needs_initialization = false;
      scope_list_node_t* scope_list_node = reference_list_node->scope_list_node;
      while(scope_list_node->depth < resolved_scope_list_node->depth) {
         if(resolved_scope_list_node->scope->flags & scope_flag_conditional) {
            needs_initialization = true; break;
         }
         resolved_scope_list_node = resolved_scope_list_node->parent;
      }
      while(resolved_scope_list_node->depth < scope_list_node->depth) {
         scope_list_node = scope_list_node->parent;
      }
      if(!needs_initialization) {
         position_t position = reference->location->begin;
         position_t resolved_position = resolved_symbol->identifier->location->begin;
         needs_initialization = (resolved_position.line > position.line) || (
            (resolved_position.line == position.line) &&
            (resolved_position.column > position.column)
         );
      }
      if(needs_initialization) {
         resolved_symbol->identifier->flags |= identifier_flag_initialize;
         target_scope->symbol_layout->init_size += sizeof(any_t);
         re_resolution_type = "init";
      }
   }
   printf("%*s reresolved reference %s %.*s(%d:%d)\n", state->current_scope_list_node->depth + 1, "", re_resolution_type, (int)(reference->end - reference->begin), reference->begin, reference->location->begin.line, reference->location->begin.column); fflush(stdout);
   // remove reference from unresolved reference list and
   // add it to resolved reference list
   reference_list_node->resolved_symbol = resolved_symbol;
   reference_list_node_t* prev = reference_list_node->prev;
   reference_list_node_t* next = reference_list_node->next;
   reference_list_node_t* tail = target_scope->resolved_reference_list.tail;
   //printf("%p %p %p %p\n", prev, (prev ? prev->next : nullptr), next, (next ? next->prev : nullptr));
   if(prev != nullptr) prev->next = next;
   if(next != nullptr) next->prev = prev;
   if(tail != nullptr) tail->next = reference_list_node;
   //printf("%p %p %p %p\n", prev, (prev ? prev->next : nullptr), next, (next ? next->prev : nullptr));
   reference_list_node->prev = tail;
   reference_list_node->next = nullptr;
   if(tail == nullptr) target_scope->resolved_reference_list.head = reference_list_node;
   target_scope->resolved_reference_list.tail = reference_list_node;
   if(current_scope != hoisting_scope) {
      if(current_scope->unresolved_reference_list.head == reference_list_node) {
         current_scope->unresolved_reference_list.head = next;
      }
   }
   if(hoisting_scope->unresolved_reference_list.head == reference_list_node) {
      hoisting_scope->unresolved_reference_list.head = next;
   }
   if(hoisting_scope->unresolved_reference_list.tail == reference_list_node) {
      hoisting_scope->unresolved_reference_list.tail = prev;
   }
   return true;
}
#endif

symbol_list_node_t* add_symbol_to_list(
   parse_state_t* state, symbol_list_t** symbol_list_ref, symbol_list_t* symbol_list,
   identifier_t* identifier, uint8_t binding_flag, uint8_t symbol_type
){
#ifdef DBGMEM
   ++symbol_count;
#endif
   symbol_t* new_symbol = parser_malloc(mm_symbols, sizeof(symbol_t));
   *new_symbol = (symbol_t){
      .type = symbol_type, .binding_flag = binding_flag,
      .identifier = identifier,
   };
   symbol_list_node_t* new_symbol_list_node = parser_malloc(mm_symbol_list_nodes, sizeof(symbol_list_node_t));
   *new_symbol_list_node = (symbol_list_node_t){
      .symbol = new_symbol, .next = nullptr, .sequence_next = nullptr,
#ifdef COMPILER
      .scope_next = nullptr
#endif
   };
   if(!symbol_list) {
      symbol_list = parser_malloc(mm_symbol_lists, sizeof(symbol_list_t));
      *symbol_list = (symbol_list_t){
         .head = new_symbol_list_node, .tail = new_symbol_list_node
      };
      *symbol_list_ref = symbol_list;
   } else {
      symbol_list->tail->next = new_symbol_list_node;
      symbol_list->tail = new_symbol_list_node;
   }
   return new_symbol_list_node;
}

uint8_t add_symbol_to_table(
   parse_state_t* state, symbol_list_t** symbol_table,
   identifier_t* identifier, uint8_t binding_flag, uint8_t symbol_type
){
   string_t const* const symbol_string = (
      identifier->compiled_string
         ? (string_t*)(identifier->compiled_string)
         : (string_t*)(identifier)
   );
   size_t const symbol_length = symbol_string->end - symbol_string->begin;
   symbol_hash_t hash = (
      ((symbol_length & symbol_length_mask) << 5) |
      (*symbol_string->begin & symbol_first_letter_mask)
   );
   symbol_list_t* symbol_list = symbol_table[hash];
   if(symbol_list) {
      symbol_list_node_t* symbol_list_node = symbol_list->head;
      uint8_t has_symbol = _get_symbol(symbol_string, symbol_length, hash, &symbol_list_node);
      if(has_symbol) return 0;
   }
   add_symbol_to_list(state, &symbol_table[hash], symbol_list, identifier, binding_flag, symbol_type);
   return 1;
}

symbol_list_node_t* add_symbol_to_scoped_list(
   parse_state_t* state, symbol_list_t** symbol_list_ref, symbol_list_t* symbol_list,
   identifier_t* identifier, uint8_t binding_flag, uint8_t symbol_type
){
   symbol_list_node_t* new_symbol_list_node = add_symbol_to_list(
      state, symbol_list_ref, symbol_list, identifier, binding_flag, symbol_type
   );
   scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
   if(hoisting_scope->last_symbol_list_node != nullptr) {
      hoisting_scope->last_symbol_list_node->sequence_next = new_symbol_list_node;
   }
   hoisting_scope->last_symbol_list_node = new_symbol_list_node;
   scope_t* current_scope = state->current_scope_list_node->scope;
   scope_list_node_t* target_scope_list_node = (
      binding_flag & binding_flag_hoisted ? state->hoisting_scope_list_node : state->current_scope_list_node
   );
   scope_t* target_scope = (
      binding_flag & binding_flag_hoisted ? hoisting_scope : current_scope
   );
#ifdef COMPILER
   // on a first symbol in a scope ensure all parents have a first symbol
   if(target_scope->full_symbol_list.head == nullptr) {
      target_scope->full_symbol_list.head = new_symbol_list_node;
      scope_list_node_t* scope_list_node = target_scope_list_node;
      while(scope_list_node->parent) {
         if(scope_list_node->scope->flags & scope_flag_hoisting) break;
         scope_t* parent_scope = target_scope_list_node->parent->scope;
         if(parent_scope->full_symbol_list.head) break;
         parent_scope->full_symbol_list.head = new_symbol_list_node;
         scope_list_node = scope_list_node->parent;
      }
   }
   target_scope->full_symbol_list.tail = new_symbol_list_node;
#endif
   if(target_scope->symbol_list.head == nullptr) {
      target_scope->symbol_list.head = new_symbol_list_node;
      target_scope->symbol_list.tail = new_symbol_list_node;
   } else {
#ifdef COMPILER
      target_scope->symbol_list.tail->scope_next = new_symbol_list_node;
#endif
      target_scope->symbol_list.tail = new_symbol_list_node;
   }
   return new_symbol_list_node;
}

bool insert_symbol(
   parse_state_t* state, identifier_t* identifier,
   uint8_t binding_flag, uint8_t symbol_type, params_t params
){
   string_t const* const symbol_string = (
      identifier->compiled_string
         ? (string_t*)(identifier->compiled_string)
         : (string_t*)(identifier)
   );
   size_t const symbol_length = symbol_string->end - symbol_string->begin;
   //printf("inserting symbol %.*s %x %x\n", (int)(symbol_length), symbol_string->begin, binding_flag, params & UNIQUE);
   symbol_hash_t hash = (
      ((symbol_length & symbol_length_mask) << 5) |
      (*symbol_string->begin & symbol_first_letter_mask)
   );
   uint8_t has_symbol = 0;
   symbol_list_node_t* symbol_list_node;
   symbol_list_t* symbol_list;
   symbol_list_t** symbol_table;
   scope_list_node_t* scope_list_node = state->current_scope_list_node;
   scope_t* const scope = scope_list_node->scope;
   if(binding_flag & binding_flag_loose) {
      scope_list_node_t const* lookup_scope_list_node = state->current_scope_list_node;
      while(!has_symbol) {
         symbol_list = lookup_scope_list_node->scope->lexical_symbol_table[hash];
         if(symbol_list) {
            symbol_list_node = symbol_list->head;
            has_symbol = _get_symbol(symbol_string, symbol_length, hash, &symbol_list_node);
         }
         if(lookup_scope_list_node == state->hoisting_scope_list_node) break;
         lookup_scope_list_node = lookup_scope_list_node->parent;
      }
      if(!has_symbol) {
         symbol_table = scope->var_symbol_table;
         symbol_list = symbol_table[hash];
         if(symbol_list) {
            symbol_list_node = symbol_list->head;
            has_symbol = _get_symbol(symbol_string, symbol_length, hash, &symbol_list_node);
         }
      }
   } else {
      has_symbol = get_symbol_from_lexical_tree(
         &scope_list_node, symbol_string, symbol_length, hash, &symbol_list_node
      );
      if((scope->flags & scope_flag_catch) && (params & param_flag_annex)) {
         if(symbol_matches(scope->identifier, symbol_string, symbol_length)) {
            return 0;
         }
      }
      if(!has_symbol) {
         symbol_table = scope->lexical_symbol_table;
         symbol_list = symbol_table[hash];
      }
   }
   if(has_symbol) {
      if(!scope->first_duplicate) {
         repeated_symbol_t* t = parser_malloc(mm_repeated_symbols, sizeof(repeated_symbol_t));
         *t = (repeated_symbol_t){
            .original = symbol_list_node->symbol->identifier,
            .duplicate = identifier
         };
         scope->first_duplicate = t;
      }
      bool allowed_duplicate = (
         !(params & param_flag_unique_params) &&
         (symbol_list_node->symbol->binding_flag & binding_flag)
      );
#ifdef COMPILER
      if(allowed_duplicate) {
         _insert_reference(state, identifier, symbol_list_node->symbol);
      }
#endif
      return allowed_duplicate;
   }
#ifdef COMPILER
   {
      // convert duplicate var declarations at hoisting scope level into references
      if(binding_flag & binding_flag_hoisted) {
         scope_t* target_scope = state->hoisting_scope_list_node->scope;
         symbol_list_node_t* symbol_list_node;
         scope_list_node = state->hoisting_scope_list_node;
         bool has_symbol = get_symbol_from_hoisting_var_tree(
            &scope_list_node, symbol_string, symbol_length, hash, &symbol_list_node
         );
         if(has_symbol) {
            _insert_reference(state, identifier, symbol_list_node->symbol);
         } else {
            target_scope->symbol_layout->stack_size += sizeof(any_t);
            target_scope->symbol_layout->closure_offset += sizeof(any_t);
         }
      } else {
         scope_t* target_scope = state->current_scope_list_node->scope;
         target_scope->symbol_layout->stack_size += sizeof(any_t);
         target_scope->symbol_layout->closure_offset += sizeof(any_t);
      }
   }
#endif
   symbol_list_node_t* new_symbol_list_node = add_symbol_to_scoped_list(
      state, &symbol_table[hash], symbol_list, identifier, binding_flag, symbol_type
   );
   return true;
}

uint8_t has_label(
   parse_state_t* state, identifier_t const* identifier, params_t params
){
   string_t const* const symbol_string = (
      identifier->compiled_string
         ? (string_t*)(identifier->compiled_string)
         : (string_t*)(identifier)
   );
   size_t const symbol_length = symbol_string->end - symbol_string->begin;
   //printf("inserting label %.*s\n", (int)(symbol_length), symbol_string->begin); fflush(stdout);
   label_list_node_t* label_list_node = state->hoisting_scope_list_node->scope->label_list_node;
   while(label_list_node) {
      identifier_t const* const compare_id = label_list_node->identifier;
      if(symbol_matches(compare_id, symbol_string, symbol_length)) {
         //[TODO] set error location
         return 1;
      }
      label_list_node = label_list_node->parent;
   }
   return 0;
}
uint8_t insert_label(
   parse_state_t* state, identifier_t const* identifier, params_t params
){
   if(has_label(state, identifier, params)) return 0;
   label_list_node_t* new_label_list_node = parser_malloc(mm_label_list_nodes, sizeof(label_list_node_t));
   scope_t* const hoisting_scope = state->hoisting_scope_list_node->scope;
   *new_label_list_node = (label_list_node_t){
      .identifier = identifier, .parent = hoisting_scope->label_list_node
   };
   hoisting_scope->label_list_node = new_label_list_node;
   return 1;
}
void ascend_label_chain(parse_state_t* state)
{
   //printf("ascending label chain\n");
   scope_t* const hoisting_scope = state->hoisting_scope_list_node->scope;
   hoisting_scope->label_list_node = hoisting_scope->label_list_node->parent;
}

symbol_list_t** new_symbol_table(parse_state_t* state)
{
   size_t const size = symbol_hash_table_size * sizeof(symbol_list_t*);
   symbol_list_t** symbol_table = parser_malloc(mm_symbol_tables, size);
   memset(symbol_table, 0, size);
   return symbol_table;
}
void add_child_scope(parse_state_t* state, scope_list_node_t* parent_scope_list_node, scope_list_node_t* child_scope_list_node)
{
   child_scope_list_node->parent = parent_scope_list_node;
   if(!parent_scope_list_node) return;
   scope_child_list_node_t* child_list_node = parser_malloc(mm_scope_child_list_nodes, sizeof(scope_child_list_node_t));
   *child_list_node = (scope_child_list_node_t){
      .scope_list_node = child_scope_list_node, .prev = nullptr, .next = nullptr
   };
   scope_child_list_t* child_list = &(parent_scope_list_node->child_list);
   if(!child_list->head) {
      child_list->head = child_list->tail = child_list_node;
   } else {
      child_list_node->prev = child_list->tail;
      child_list->tail->next = child_list_node;
      child_list->tail = child_list_node;
   }
}
scope_list_node_t* new_scope(parse_state_t* state, uint8_t scope_flags, identifier_t* identifier)
{
   bool is_hoisting = scope_flags & scope_flag_hoisting;
#ifdef COMPILER
   printf("%*s begin %sscope %d:%d\n", state->scope_depth, "", (is_hoisting ? "hoisting::" : ""), state->scope_depth, state->scope_count);
#endif
   size_t const size = symbol_hash_table_size * sizeof(symbol_list_t*);
   scope_list_node_t* scope_list_node = state->scope_list_node;
   scope_list_node_t* next_scope_list_node;
   scope_list_node_t* next_next_scope_list_node;
#ifdef COMPILER
   symbol_layout_t* symbol_layout;
#endif
   scope_t* child_scope;
   symbol_list_t **lexical_symbol_table, **var_symbol_table;
   if(scope_list_node == nullptr || scope_list_node->next == nullptr) {
#ifdef DBGMEM
      ++scope_count;
#endif
      // create a new scope
      child_scope = parser_malloc(mm_scopes, sizeof(scope_t));
      lexical_symbol_table = parser_malloc(mm_symbol_tables, size);
      var_symbol_table = parser_malloc(mm_symbol_tables, size);
      next_scope_list_node = parser_malloc(mm_scope_list_nodes, sizeof(scope_list_node_t));
#ifdef COMPILER
      symbol_layout = parser_malloc(mm_symbol_layouts, sizeof(symbol_layout_t));
#endif
      next_next_scope_list_node = nullptr;
      if(scope_list_node) scope_list_node->next = next_scope_list_node;
   } else {
      // reuse existing scope that was allocated earlier and is not being used
      next_scope_list_node = scope_list_node->next;
      next_next_scope_list_node = next_scope_list_node->next;
      child_scope = next_scope_list_node->scope;
      lexical_symbol_table = child_scope->lexical_symbol_table;
      var_symbol_table = child_scope->var_symbol_table;
#ifdef COMPILER
      symbol_layout = child_scope->symbol_layout;
#endif
   }
   *child_scope = (scope_t){
      .flags = scope_flags, .identifier = identifier,
      .first_duplicate = nullptr,
      .first_yield_or_await = nullptr,
      .lexical_symbol_table = lexical_symbol_table,
      .var_symbol_table = var_symbol_table,
      .label_list_node = nullptr,
      .last_symbol_list_node = nullptr,
      .symbol_list = {.head = nullptr, .tail = nullptr},
#ifdef COMPILER
      .id = state->scope_count++,
      .full_symbol_list = {.head = nullptr, .tail = nullptr},
      .resolved_reference_list = {.head = nullptr, .tail = nullptr},
      .unresolved_reference_list = {.head = nullptr, .tail = nullptr},
      .symbol_layout = symbol_layout,
      .stack_size = 0, .heap_size = 0
#endif
   };
   *next_scope_list_node = (scope_list_node_t){
      .scope = child_scope,
      .depth = state->scope_depth++,
      .prev = scope_list_node, .next = next_next_scope_list_node,
      .parent = nullptr, .hoisting_parent = nullptr,
      .child_list = {.head = nullptr, .tail = nullptr},
   };
   add_child_scope(state, state->current_scope_list_node, next_scope_list_node);
   state->scope_list_node = next_scope_list_node;
   state->current_scope_list_node = next_scope_list_node;
   if(is_hoisting) state->hoisting_scope_list_node = next_scope_list_node;
   next_scope_list_node->hoisting_parent = state->hoisting_scope_list_node;
   memset(lexical_symbol_table, 0, size);
   memset(var_symbol_table, 0, size);
#ifdef COMPILER
   //[TODO] free up existing buffers
   *symbol_layout = (symbol_layout_t){
      .init_offset = 0, .init_size = 0, .init_buffer = nullptr,
      .closure_offset = 0, .closure_export_size = 0,
      .closure_export_buffer = nullptr, .closure_import_size = 0
   };
#endif
   return next_scope_list_node;
}
void end_scope(parse_state_t* state)
{
   uint32_t scope_depth = state->current_scope_list_node->depth;
   bool is_hoisting = state->current_scope_list_node->scope->flags & scope_flag_hoisting;
   scope_list_node_t* parent = state->current_scope_list_node->parent;
   scope_t* scope = state->current_scope_list_node->scope;
#ifdef COMPILER
   // note the last symbol on the parent scope
   if(!is_hoisting && parent){
      symbol_list_node_t* tail = scope->full_symbol_list.tail;
      if(tail) parent->scope->full_symbol_list.tail = tail;
   }
   // try to re-resolve unresolved references
   reference_list_node_t* reference_list_node = scope->unresolved_reference_list.head;
   while(reference_list_node) {
      // on successful re-resolution the reference list node will be evicted
      // from unresolved reference list hence we the next item in the list
      reference_list_node_t* next = reference_list_node->next;
      if(!re_resolve_reference(state, reference_list_node)) {
         if(is_hoisting) {
            // collpase all child scopes to hoisting scope
            reference_list_node->scope_list_node = state->current_scope_list_node;
            reference_list_node->reference->flags |= identifier_flag_possible_closure;
         }
      }
      reference_list_node = next;
   }
   // fix the memory layout for symbols and references
   {
      size_t const closure_factor = sizeof(any_t) / sizeof(any_t*);
      symbol_layout_t* symbol_layout = scope->symbol_layout;
      uint32_t init_size = symbol_layout->init_size;
      uint32_t closure_export_size = symbol_layout->closure_export_size;
      if(init_size) {
         symbol_layout->init_buffer = parser_malloc(mm_symbol_buffer, init_size);
      }
      if(closure_export_size) {
         symbol_layout->closure_export_buffer = parser_malloc(mm_symbol_buffer, closure_export_size * closure_factor);
      }
      //printf("init = %d, closure = %d\n", init_size, closure_export_size);
      scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
      uint32_t init_offset = hoisting_scope->stack_size;
      uint32_t non_init_offset = init_offset + init_size;
      uint32_t closure_offset = init_offset + symbol_layout->closure_offset;
      init_size = closure_export_size = 0; uint32_t non_init_size = 0;
      symbol_list_node_t* symbol_list_node = scope->symbol_list.head;
      while(symbol_list_node) {
         symbol_t const* symbol = symbol_list_node->symbol;
         bool do_process = (
            (symbol->binding_flag & binding_flag_hoisted) ? is_hoisting : true
         );
         if(do_process) {
            if(symbol->identifier->flags & identifier_flag_closure) {
               if(closure_export_size + sizeof(any_t*) > symbol_layout->closure_export_size) {
                  printf("incorrect closure size\n"); fflush(stdout);
               }
               *(symbol_layout->closure_export_buffer + closure_export_size/sizeof(any_t*)) =
                  (symbol->binding_flag & binding_flag_hoisted ? any_undefined : any_void);
               symbol->identifier->offset = closure_offset + closure_export_size;
               closure_export_size += sizeof(any_t*);
            } else {
               if(symbol->identifier->flags & identifier_flag_initialize) {
                  if(init_size + sizeof(any_t) > symbol_layout->init_size) {
                     printf("incorrect initialization size\n"); fflush(stdout);
                  }
                  *(symbol_layout->init_buffer + init_size/sizeof(any_t)) =
                     (symbol->binding_flag & binding_flag_hoisted ? any_undefined : any_void);
                  symbol->identifier->offset = init_offset + init_size;
                  init_size += sizeof(any_t);
               } else {
                  symbol->identifier->offset = non_init_offset + non_init_size;
                  non_init_size += sizeof(any_t);
               }
            }
         }
         symbol_list_node = symbol_list_node->scope_next;
      }
      if(init_size != symbol_layout->init_size ||
         closure_export_size != symbol_layout->closure_export_size ||
         init_size + non_init_size != symbol_layout->closure_offset ||
         init_size + non_init_size + closure_export_size != symbol_layout->stack_size
      ){
         printf("mismatch in symbol binding sizes ");
         printf("%d-%d %d-%d %d-%d %d-%d\n",
            init_size, symbol_layout->init_size,
            closure_export_size, symbol_layout->closure_export_size,
            init_size + non_init_size, symbol_layout->closure_offset,
            init_size + non_init_size + closure_export_size, symbol_layout->stack_size
         );
         fflush(stdout);
      }
      symbol_layout->init_offset = hoisting_scope->stack_size;
      symbol_layout->closure_offset += hoisting_scope->stack_size;
      hoisting_scope->stack_size += init_size + non_init_size + closure_export_size;
      reference_list_node_t* reference_list_node = scope->resolved_reference_list.head;
      while(reference_list_node) {
         reference_list_node->reference->offset =
            reference_list_node->resolved_symbol->identifier->offset;
         identifier_t* i = reference_list_node->reference;
         printf("%*s reference offset %.*s(%d:%d) %d\n", scope_depth + 1, "", (int)(i->end - i->begin), i->begin, i->location->begin.line, i->location->begin.column, i->offset);
         reference_list_node = reference_list_node->next;
      }
      //if(init_size != 0 || closure_export_size != 0) {
         printf("%*s init=%d+%d non_init=%d+%d closure=%d+%d\n",
            scope_depth + 1, "", init_offset, init_size,
            non_init_offset, non_init_size, closure_offset, closure_export_size
         );
      //}
   }
   // append unresolved reference list to parent
   if(parent) {
      scope_t* parent_scope = parent->scope;
      if(is_hoisting) {
         scope_t* hoisting_scope = parent->hoisting_parent->scope;
         reference_list_node_t* tail = hoisting_scope->unresolved_reference_list.tail;
         if(tail == nullptr) {
            hoisting_scope->unresolved_reference_list = scope->unresolved_reference_list;
         } else {
            tail->next = scope->unresolved_reference_list.head;
            if(tail->next) {
               scope->unresolved_reference_list.head->prev = tail;
               hoisting_scope->unresolved_reference_list.tail = scope->unresolved_reference_list.tail;
            }
         }
      }
      if(parent_scope->unresolved_reference_list.head == nullptr) {
         parent_scope->unresolved_reference_list.head = scope->unresolved_reference_list.head;
      }
   }
   {
   if(state->current_scope_list_node == state->top_level_scope_list_node) {
      printf("%3d unresolved references\n", state->current_scope_list_node->depth); fflush(stdout);
      reference_list_node_t* reference_list_node = state->hoisting_scope_list_node->scope->unresolved_reference_list.head;
      while(reference_list_node) {
         identifier_t* identifier = reference_list_node->reference;
         printf("\t%5d:%-2d %.*s", identifier->location->begin.line, identifier->location->begin.column, (int)(identifier->end - identifier->begin), identifier->begin); fflush(stdout);
         reference_list_node = reference_list_node->next;
      }
      printf("\n"); fflush(stdout);
   }
   }
   /*
   if(is_hoisting && parent){
      printf("%3d parent unresolved references\n", parent->hoisting_parent->depth); fflush(stdout);
      reference_list_node_t* reference_list_node = parent->hoisting_parent->scope->unresolved_reference_list.head;
      while(reference_list_node) {
         identifier_t* identifier = reference_list_node->reference;
         printf("\t%5d:%-2d %.*s", identifier->location->begin.line, identifier->location->begin.column, (int)(identifier->end - identifier->begin), identifier->begin); fflush(stdout);
         reference_list_node = reference_list_node->next;
      }
      printf("\n"); fflush(stdout);
   }
   */
#endif
#ifndef COMPILER
   if(is_hoisting) {
      state->scope_list_node = state->current_scope_list_node->prev;
      if(parent) {
         scope_child_list_t* child_list = &(parent->child_list);
         if(child_list->head == child_list->tail) {
            child_list->head = child_list->tail = nullptr; //[TODO] free
         } else {
            child_list->tail->prev->next = nullptr;
            child_list->tail = child_list->tail->prev; //[TODO] free
         }
      }
   }
#else
   if(is_hoisting) {
      if(scope->unresolved_reference_list.head) {
         state->scope_list_node = state->current_scope_list_node;
      } else {
         state->scope_list_node = state->current_scope_list_node->prev;
      }
      state->current_scope_list_node->child_list = (scope_child_list_t){
         .head = nullptr, .tail = nullptr //[TODO] free
      };
   }
   printf("%*s end %sscope %d:%d => (%d) +%d = %d\n", scope_depth, "", (is_hoisting ? "hoisting::" : ""), scope_depth, state->current_scope_list_node->scope->id, state->hoisting_scope_list_node->scope->id, scope->symbol_layout->stack_size, state->hoisting_scope_list_node->scope->stack_size);
#endif
   state->current_scope_list_node = parent;
   state->hoisting_scope_list_node = (parent ? parent->hoisting_parent : nullptr);
   --state->scope_depth;
}
uint8_t is_scope_unique(parse_state_t const* const state)
{
   if(state->current_scope_list_node->scope->first_duplicate) {
      //[TODO] set error
      return 0;
   }
   return 1;
}

#endif //_SCOPE_H_
