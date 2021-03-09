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

bool _get_symbol(
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
      .offset = 0, .import_offset = -1, .identifier = identifier,
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
   } else if(symbol_list->tail == nullptr) {
      *symbol_list = (symbol_list_t){
         .head = new_symbol_list_node, .tail = new_symbol_list_node
      };
   } else {
      symbol_list->tail->next = new_symbol_list_node;
      symbol_list->tail = new_symbol_list_node;
   }
   return new_symbol_list_node;
}

#ifdef COMPILER
bool get_symbol_from_list(
   symbol_list_node_t** symbol_list_node_ref, identifier_t const* identifier
){
   if(*symbol_list_node_ref == nullptr) return false;
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
   return _get_symbol(symbol_string, symbol_length, hash, symbol_list_node_ref);
}

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
      symbol_list_t* symbol_list = scope->lexical_symbol_table[hash];
      if(symbol_list) {
         symbol_list_node = symbol_list->head;
         bool has_symbol = _get_symbol(symbol_string, symbol_length, hash, &symbol_list_node);
         if(has_symbol) return symbol_list_node->symbol;
      }
   }
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
   return nullptr;
}
void append_to_reference_list(reference_list_t* list, reference_list_node_t* node)
{
   reference_list_node_t* tail = list->tail;
   if(tail != nullptr) tail->next = node;
   node->prev = tail;
   node->next = nullptr;
   if(tail == nullptr) list->head = node;
   list->tail = node;
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
#ifdef DBG_LAYOUT
      .original_scope_list_node = state->current_scope_list_node,
#endif
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
void resolve_reference(parse_state_t* state, identifier_t* identifier)
{
   scope_list_node_t* scope_list_node = state->current_scope_list_node;
   symbol_t const* symbol = get_symbol_from_scope(&scope_list_node, identifier);
   printf("%*s %10s reference %.*s(%d:%d)\n", scope_list_node->scope->depth + 1, "", (symbol ? "resovled" : "unresolved"), (int)(identifier->end - identifier->begin), identifier->begin, identifier->location->begin.line, identifier->location->begin.column); fflush(stdout);
   _insert_reference(state, identifier, symbol);
}
void append_to_closure_scope_list(
   parse_state_t* state, simple_scope_list_t* closure_scope_list, scope_t* scope
){
   simple_scope_list_node_t* closure_scope_list_node = parser_malloc(
      mm_closure_scope_lists, sizeof(simple_scope_list_node_t)
   );
   *closure_scope_list_node = (simple_scope_list_node_t){.scope = scope, .next = nullptr};
   if(closure_scope_list->tail == nullptr) {
      *closure_scope_list = (simple_scope_list_t){
         .head = closure_scope_list_node, .tail = closure_scope_list_node
      };
   } else {
      closure_scope_list->tail->next = closure_scope_list_node;
      closure_scope_list->tail = closure_scope_list_node;
   }
}
void remove_reference_list_node(reference_list_t* list, reference_list_node_t* node)
{
   // remove reference from unresolved reference list
   reference_list_node_t* prev = node->prev;
   reference_list_node_t* next = node->next;
   if(prev != nullptr) prev->next = next;
   if(next != nullptr) next->prev = prev;
   if(list->head == node) list->head = next;
   if(list->tail == node) list->tail = prev;
}
void delist_unresolved_reference_list_node(
   scope_t* current_scope, scope_t* hoisting_scope, reference_list_node_t* node
){
   if(current_scope != hoisting_scope) {
      if(current_scope->unresolved_reference_list.head == node) {
         current_scope->unresolved_reference_list.head = node->next;
      }
   }
   remove_reference_list_node(&hoisting_scope->unresolved_reference_list, node);
}
bool re_resolve_reference(parse_state_t* state, reference_list_node_t* reference_list_node)
{
   identifier_t* reference = reference_list_node->reference;
   scope_list_node_t* resolved_scope_list_node = state->current_scope_list_node;
   scope_t* current_scope = resolved_scope_list_node->scope;
   scope_t* hoisting_scope = state->hoisting_scope_list_node->scope;
   symbol_t const* resolved_symbol = get_symbol_from_scope(&resolved_scope_list_node, reference);
   if(!resolved_symbol) return false;

   // remove reference from unresolved reference list
   delist_unresolved_reference_list_node(current_scope, hoisting_scope, reference_list_node);
   /*
   reference_list_node_t* prev = reference_list_node->prev;
   reference_list_node_t* next = reference_list_node->next;
   if(prev != nullptr) prev->next = next;
   if(next != nullptr) next->prev = prev;
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
   */

   scope_list_node_t* target_scope_list_node = (
      resolved_symbol->binding_flag & binding_flag_hoisted
         ? state->hoisting_scope_list_node : state->current_scope_list_node
   );
   scope_t* target_scope = target_scope_list_node->scope;
   char const* re_resolution_type = "";
   if(reference->flags & identifier_flag_possible_closure) {
      reference->flags |= identifier_flag_closure;
      reference->flags ^= identifier_flag_possible_closure;
      if(!(resolved_symbol->identifier->flags & identifier_flag_closure)) {
         resolved_symbol->identifier->flags |= identifier_flag_closure;
         //target_scope->symbol_layout->stack_size += sizeof(any_t*) - sizeof(any_t);
         target_scope->symbol_layout->closure_export_size += sizeof(any_t);
         target_scope->symbol_layout->closure_offset -= sizeof(any_t);
         if(resolved_symbol->identifier->flags & identifier_flag_initialize) {
            target_scope->symbol_layout->init_size -= sizeof(any_t);
         }
         re_resolution_type = "closure";
      }
      // create a chain of cloure import symbols from the scope where the
      // symbol is defined to the scope where the symbol is referenced
      scope_list_node_t* scope_list_node = reference_list_node->scope_list_node;
      scope_t* previous_scope = nullptr;
      symbol_t* previous_symbol = nullptr;
      bool is_first = true;
      while(scope_list_node != state->hoisting_scope_list_node) {
         bool has_symbol = false;
         symbol_list_node_t* symbol_list_node = scope_list_node->scope->closure_import_symbol_list.head;
         symbol_layout_t* symbol_layout = scope_list_node->scope->symbol_layout;
         if(symbol_list_node == nullptr) {
            append_to_closure_scope_list(state, &state->closure_scope_list, scope_list_node->scope);
         } else {
            has_symbol = get_symbol_from_list(&symbol_list_node, reference);
         }
         if(!has_symbol) {
            symbol_list_t* symbol_list = &scope_list_node->scope->closure_import_symbol_list;
            uint8_t symbol_type = 0;
            symbol_list_node = add_symbol_to_list(
               state, &symbol_list, symbol_list, resolved_symbol->identifier, binding_flag_closure, symbol_type
            );
            uint32_t offset = scope_list_node->scope->symbol_layout->frame_size;
            symbol_list_node->symbol->offset = offset;
            symbol_layout->stack_size += sizeof(any_t);
            symbol_layout->closure_import_size += sizeof(any_t);
            scope_list_node->scope->symbol_layout->frame_size += sizeof(any_t);
            identifier_t* i = resolved_symbol->identifier;
            printf("%*s adding at offset %d to scope %d:%d the closure symbol %.*s(%d:%d)\n", state->current_scope_list_node->scope->depth + 1, "", offset, scope_list_node->scope->depth, scope_list_node->scope->id, (int)(i->end - i->begin), i->begin, i->location->begin.line, i->location->begin.column); fflush(stdout);
         }
         uint32_t offset = symbol_list_node->symbol->offset;
         scope_list_node_t* parent = scope_list_node->parent;
         //if(is_first && parent != state->hoisting_scope_list_node) {
         if(is_first) {
            reference_list_node->reference->offset = offset;
         }
         if(!is_first && parent == state->hoisting_scope_list_node) {
            /*
            reference_list_node_t* dummy_reference_list_node = parser_malloc(
               mm_reference_list_nodes, sizeof(reference_list_node_t)
            );
            *dummy_reference_list_node = *reference_list_node;
            reference_list_node->scope_list_node = scope_list_node;
            reference_list_node = dummy_reference_list_node;
            */
            // hijack reference list node
            reference_list_node->scope_list_node = scope_list_node;
         }
         if(previous_symbol) {
            previous_symbol->import_offset = offset;
            identifier_t* i = previous_symbol->identifier;
            printf("%*s noting closure offset as %d in scope %d for the closure symbol %.*s(%d:%d)\n", state->current_scope_list_node->scope->depth + 1, "", offset, previous_scope->id, (int)(i->end - i->begin), i->begin, i->location->begin.line, i->location->begin.column); fflush(stdout);
         }
         //reference_list_node->resolved_symbol = symbol_list_node->symbol;
         //append_to_reference_list(&scope_list_node->scope->reference_list, reference_list_node);
         previous_scope = scope_list_node->scope;
         previous_symbol = symbol_list_node->symbol;
         scope_list_node = scope_list_node->parent;
         if(scope_list_node == nullptr) {
            printf("execption:: parent scope list node cannot be null\n");
            fflush(stdout);
         }
         is_first = false;
      }
   } else if(!(resolved_symbol->identifier->flags & (identifier_flag_closure | identifier_flag_initialize))) {
      // determine if initialization required for the symbol
      bool needs_initialization = false;
      scope_list_node_t* scope_list_node = reference_list_node->scope_list_node;
      while(scope_list_node->scope->depth < resolved_scope_list_node->scope->depth) {
         if(resolved_scope_list_node->scope->flags & scope_flag_conditional) {
            needs_initialization = true; break;
         }
         resolved_scope_list_node = resolved_scope_list_node->parent;
      }
      while(resolved_scope_list_node->scope->depth < scope_list_node->scope->depth) {
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
   reference_list_node->resolved_symbol = resolved_symbol;
   printf("%*s reresolved reference %s %.*s(%d:%d)\n", state->current_scope_list_node->scope->depth + 1, "", re_resolution_type, (int)(reference->end - reference->begin), reference->begin, reference->location->begin.line, reference->location->begin.column); fflush(stdout);

   // append reference to resolved reference list
   append_to_reference_list(&target_scope->resolved_reference_list, reference_list_node);

   return true;
}
#endif

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
#ifdef COMPILER
void dump_frame_layout(scope_list_node_t* scope_list_node, bool do_recursive)
{
   scope_t* scope = scope_list_node->scope;
   if(scope->depth == 0) printf("SYMBOL LAYOUT\n");
   bool is_first = true;
   bool is_hoisting = (scope->flags & scope_flag_hoisting);
   int list_count = 2; //(is_hoisting ? 2 : 1);
   symbol_layout_t* sl = scope->symbol_layout;
   printf("%*s scope %d:%d %d+%d+%d+%d=%d %d:%d\n", scope->depth, "", scope->depth, scope->id, sl->init_size, sl->stack_size - sl->init_size - sl->closure_export_size - sl->closure_import_size, sl->closure_export_size, sl->closure_import_size, sl->stack_size, sl->init_offset, sl->closure_offset);
   for(int list_index = 0; list_index < list_count; ++list_index) {
      symbol_list_t* symbol_list = (
         list_index == 0 ? &scope->symbol_list : &scope->closure_import_symbol_list
      );
      symbol_list_node_t* symbol_list_node = symbol_list->head;
      while(symbol_list_node) {
         if(is_first) {
            printf("%*s symbols:\n", scope->depth + 1, "");
         }
         symbol_t* symbol = symbol_list_node->symbol;
         identifier_t* identifier = symbol->identifier;
         uint32_t offset = (symbol->binding_flag & binding_flag_closure ? symbol->offset : identifier->offset);
         printf("%*s   %5d => %.*s(%d:%d)", scope->depth + 1, "", offset, (int)(identifier->end - identifier->begin), identifier->begin, identifier->location->begin.line, identifier->location->begin.column);
         if(symbol->binding_flag & binding_flag_closure) {
            printf(" => %d", symbol->import_offset);
         }
         printf(" \n");
         symbol_list_node = (list_index == 0 ? symbol_list_node->scope_next : symbol_list_node->next);
         is_first = false;
      }
   }
   is_first = true;
   reference_list_node_t* reference_list_node = scope->resolved_reference_list.head;
   while(reference_list_node) {
      if(is_first) {
         printf("%*s references:\n", scope->depth + 1, "");
      }
      identifier_t* reference = reference_list_node->reference;
      uint32_t offset = reference->offset;
      printf("%*s   %.*s(%d:%d) => %d\n", scope->depth + 1, "", (int)(reference->end - reference->begin), reference->begin, reference->location->begin.line, reference->location->begin.column, offset);
      reference_list_node = reference_list_node->next;
      if(!reference_list_node) printf("\n");
      is_first = false;
   }
   if(do_recursive) {
      scope_child_list_node_t* child_list_node = scope_list_node->child_list.head;
      while(child_list_node) {
         dump_frame_layout(child_list_node->scope_list_node, true);
         child_list_node = child_list_node->next;
      }
   }
}
#endif
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
void init_scope(
   scope_t* scope, uint8_t scope_flags, identifier_t* identifier,
   symbol_list_t** lexical_symbol_table, symbol_list_t** var_symbol_table
#ifdef COMPILER
   , uint32_t id, uint32_t depth, symbol_layout_t* symbol_layout
#endif
){
   *scope = (scope_t){
      .flags = scope_flags, .identifier = identifier,
      .first_duplicate = nullptr,
      .first_yield_or_await = nullptr,
      .lexical_symbol_table = lexical_symbol_table,
      .var_symbol_table = var_symbol_table,
      .label_list_node = nullptr,
      .last_symbol_list_node = nullptr,
      .symbol_list = {.head = nullptr, .tail = nullptr},
#ifdef COMPILER
      .id = id, .depth = depth,
      .full_symbol_list = {.head = nullptr, .tail = nullptr},
      .resolved_reference_list = {.head = nullptr, .tail = nullptr},
      .unresolved_reference_list = {.head = nullptr, .tail = nullptr},
      .closure_import_symbol_list = {.head = nullptr, .tail = nullptr},
      .symbol_layout = symbol_layout
#endif
   };
}
void init_scope_list_node(
   scope_list_node_t* scope_list_node, scope_t* scope,
   scope_list_node_t* prev, scope_list_node_t* next,
   scope_list_node_t* parent, scope_list_node_t* hoisting_parent
){
   *scope_list_node = (scope_list_node_t){
      .scope = scope, .prev = prev, .next = next,
      .parent = parent, .hoisting_parent = hoisting_parent,
      .child_list = {.head = nullptr, .tail = nullptr},
   };
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
   init_scope(
      child_scope, scope_flags, identifier, lexical_symbol_table, var_symbol_table
#ifdef COMPILER
      , state->scope_count++, state->scope_depth++, symbol_layout
#endif
   );
   init_scope_list_node(
      next_scope_list_node, child_scope,
      scope_list_node, next_next_scope_list_node, nullptr, nullptr
   );
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
      .closure_export_buffer = nullptr, .closure_import_size = 0,
      .frame_size = 0
   };
#endif
   return next_scope_list_node;
}
scope_list_node_t* make_placeholder_scope_list_node(
   parse_state_t* state, scope_list_node_t* scope_list_node
){
#ifdef DBG_LAYOUT
   return scope_list_node;
#endif
   scope_t* scope = scope_list_node->scope;
   scope_list_node_t* parent = scope_list_node->parent;
   if(parent) parent = parent->hoisting_parent;
   scope_t* placeholder_scope;
   scope_list_node_t* placeholder_scope_list_node;
   placeholder_scope = parser_malloc(mm_scopes, sizeof(scope_t));
   placeholder_scope_list_node = parser_malloc(mm_scope_list_nodes, sizeof(scope_list_node_t));
#ifdef COMPILER
   symbol_layout_t* symbol_layout = parser_malloc(mm_symbol_layouts, sizeof(symbol_layout_t));
   *symbol_layout = *scope->symbol_layout;
#endif
   init_scope(
      placeholder_scope, scope->flags, scope->identifier, nullptr, nullptr
#ifdef COMPILER
      , scope->id, scope->depth, symbol_layout
#endif
   );
   init_scope_list_node(
      placeholder_scope_list_node, placeholder_scope,
      nullptr, nullptr, parent, placeholder_scope_list_node
   );
   return placeholder_scope_list_node;
}
void free_current_scope(parse_state_t* state)
{
#ifndef DBG_LAYOUT
   state->scope_list_node = state->current_scope_list_node->prev;
   scope_list_node_t* parent = state->current_scope_list_node->parent;
   if(parent) {
      scope_child_list_t* child_list = &(parent->child_list);
      if(child_list->head == child_list->tail) {
         child_list->head = child_list->tail = nullptr; //[TODO] free
      } else {
         child_list->tail->prev->next = nullptr;
         child_list->tail = child_list->tail->prev; //[TODO] free
      }
   }
#endif
}
#ifdef COMPILER
void append_reference_list(reference_list_t* target, reference_list_t* list){
   if(target->tail == nullptr) {
      *target = *list;
   } else if(list->head) {
      target->tail->next = list->head;
      list->head->prev = target->tail;
      target->tail = list->tail;
   }
}
#endif
// collpase a temporary scope and merge it into its parent scope
// temporary scope is assumed to not introduce any new symbols
void collapse_scope(parse_state_t* state)
{
   scope_list_node_t* scope_list_node = state->current_scope_list_node;
   scope_list_node_t* parent = scope_list_node->parent;
   scope_t* current_scope = scope_list_node->scope;
#ifdef COMPILER
   reference_list_t* unresolved_reference_list = &current_scope->unresolved_reference_list;
   reference_list_node_t* reference_list_node = unresolved_reference_list->head;
   while(reference_list_node) {
      symbol_t const* symbol = get_symbol_from_scope(&scope_list_node, reference_list_node->reference);
      identifier_t* i = reference_list_node->reference;
      printf("%*s %10s reference %.*s(%d:%d)\n", scope_list_node->scope->depth + 1, "", (symbol ? "resovled" : "unresolved"), (int)(i->end - i->begin), i->begin, i->location->begin.line, i->location->begin.column); fflush(stdout);
      reference_list_node_t* next = reference_list_node->next;
      if(symbol) {
         delist_unresolved_reference_list_node(
            state->current_scope_list_node->scope,
            state->hoisting_scope_list_node->scope,
            reference_list_node
         );
         append_to_reference_list(
            &parent->scope->resolved_reference_list, reference_list_node
         );
      }
      reference_list_node = next;
   }
   append_reference_list(
      &parent->hoisting_parent->scope->unresolved_reference_list,
      unresolved_reference_list
   );
   if(!(parent->scope->flags & scope_flag_hoisting)) {
      if(parent->scope->unresolved_reference_list.head == nullptr) {
         parent->scope->unresolved_reference_list.head = unresolved_reference_list->head;
      }
   }
   uint32_t scope_depth = state->current_scope_list_node->scope->depth;
   bool is_hoisting = state->current_scope_list_node->scope->flags & scope_flag_hoisting;
   printf("%*s collapse %sscope %d:%d => (%d) +%d = %d\n", scope_depth, "", (is_hoisting ? "hoisting::" : ""), scope_depth, state->current_scope_list_node->scope->id, state->hoisting_scope_list_node->scope->id, state->current_scope_list_node->scope->symbol_layout->stack_size, state->hoisting_scope_list_node->scope->symbol_layout->frame_size); fflush(stdout);
#endif
   free_current_scope(state);
   state->current_scope_list_node = parent;
   state->hoisting_scope_list_node = (parent ? parent->hoisting_parent : nullptr);
   --state->scope_depth;
}
void end_scope(parse_state_t* state)
{
   bool is_hoisting = state->current_scope_list_node->scope->flags & scope_flag_hoisting;
   scope_list_node_t* parent = state->current_scope_list_node->parent;
   scope_t* scope = state->current_scope_list_node->scope;
   scope_list_node_t* hoisting_scope_list_node = state->hoisting_scope_list_node;
#ifdef COMPILER
   // note the last symbol on the parent scope
   uint32_t scope_depth = state->current_scope_list_node->scope->depth;
   if(!is_hoisting && parent){
      symbol_list_node_t* tail = scope->full_symbol_list.tail;
      if(tail) parent->scope->full_symbol_list.tail = tail;
   }
   // try to re-resolve unresolved references
   reference_list_node_t* reference_list_node = scope->unresolved_reference_list.head;
   if(reference_list_node) {
      scope_list_node_t* placeholder_scope_list_node = nullptr;
      while(reference_list_node) {
         // on successful re-resolution the reference list node will be evicted
         // from unresolved reference list hence we the next item in the list
         reference_list_node_t* next = reference_list_node->next;
         if(!re_resolve_reference(state, reference_list_node)) {
            if(is_hoisting && reference_list_node->scope_list_node->hoisting_parent == hoisting_scope_list_node) {
               // collpase all child scopes to hoisting scope
               if(!placeholder_scope_list_node) {
                  placeholder_scope_list_node = make_placeholder_scope_list_node(
                     state, hoisting_scope_list_node
                  );
               }
               reference_list_node->scope_list_node = placeholder_scope_list_node;
               reference_list_node->reference->flags |= identifier_flag_possible_closure;
            }
         }
         reference_list_node = next;
      }
   }
   // fix the memory layout for symbols and references
   {
      size_t const closure_factor = 1; //sizeof(any_t) / sizeof(any_t*);
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
      uint32_t init_offset = hoisting_scope->symbol_layout->frame_size;
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
               if(closure_export_size + sizeof(any_t) > symbol_layout->closure_export_size) {
                  printf("::error incorrect closure size\n"); fflush(stdout);
               }
               *(symbol_layout->closure_export_buffer + closure_export_size/sizeof(any_t)) =
                  (symbol->binding_flag & binding_flag_hoisted ? any_undefined : any_void);
               symbol->identifier->offset = closure_offset + closure_export_size;
               closure_export_size += sizeof(any_t);
            } else {
               if(symbol->identifier->flags & identifier_flag_initialize) {
                  if(init_size + sizeof(any_t) > symbol_layout->init_size) {
                     printf("::error incorrect initialization size\n"); fflush(stdout);
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
         printf("::error mismatch in symbol binding sizes ");
         printf("%d-%d %d-%d %d-%d %d-%d\n",
            init_size, symbol_layout->init_size,
            closure_export_size, symbol_layout->closure_export_size,
            init_size + non_init_size, symbol_layout->closure_offset,
            init_size + non_init_size + closure_export_size, symbol_layout->stack_size
         );
         fflush(stdout);
      }
      symbol_layout->init_offset = hoisting_scope->symbol_layout->frame_size;
      symbol_layout->closure_offset += hoisting_scope->symbol_layout->frame_size;
      hoisting_scope->symbol_layout->frame_size += init_size + non_init_size + closure_export_size;
      reference_list_node_t* reference_list_node = scope->resolved_reference_list.head;
      while(reference_list_node) {
         uint32_t offset = reference_list_node->resolved_symbol->identifier->offset;
         if(reference_list_node->reference->flags & identifier_flag_closure) {
            scope_list_node_t* sln = reference_list_node->scope_list_node;
            symbol_list_node_t* symbol_list_node = sln->scope->closure_import_symbol_list.head;
            bool has_symbol = get_symbol_from_list(&symbol_list_node, reference_list_node->reference);
            if(!has_symbol) {
               printf("error:: missing closure symbol\n");
            } else {
               symbol_list_node->symbol->import_offset = offset;
               identifier_t* i = reference_list_node->resolved_symbol->identifier;
               printf("%*s noting closure offset as %d in scope %d:%d for the closure symbol %.*s(%d:%d)\n", state->current_scope_list_node->scope->depth + 1, "", offset, sln->scope->depth, sln->scope->id, (int)(i->end - i->begin), i->begin, i->location->begin.line, i->location->begin.column); fflush(stdout);
            }
         } else {
            reference_list_node->reference->offset = offset;
         }
         identifier_t* i = reference_list_node->reference;
         printf("%*s reference offset %.*s(%d:%d) %d\n", scope_depth + 1, "", (int)(i->end - i->begin), i->begin, i->location->begin.line, i->location->begin.column, offset);
         reference_list_node_t* next = reference_list_node->next;
#ifdef DBG_LAYOUT
         // put the reference back where it belongs
         if(reference_list_node->original_scope_list_node != state->current_scope_list_node) {
            remove_reference_list_node(&scope->resolved_reference_list, reference_list_node);
            append_to_reference_list(&reference_list_node->original_scope_list_node->scope->resolved_reference_list, reference_list_node);
         }
#endif
         reference_list_node = next;
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
   if(state->current_scope_list_node == state->top_level_scope_list_node) {
      // complete symbol layout of scopes with closure references
      simple_scope_list_node_t* scope_list_node = state->closure_scope_list.head;
      while(scope_list_node) {
         scope_t* scope = scope_list_node->scope;
         symbol_layout_t* symbol_layout = scope->symbol_layout;
         //printf("%d %d\n", scope->id, symbol_layout->closure_import_size);
         uint32_t total_offset_size = symbol_layout->closure_import_size * sizeof(uint32_t) / sizeof(any_t);
         uint32_t* buffer = symbol_layout->closure_import_buffer = parser_malloc(
            mm_symbol_buffer, total_offset_size
         );
         uint32_t offset_size = 0;
         symbol_list_node_t* symbol_list_node = scope->closure_import_symbol_list.head;
         while(symbol_list_node) {
            if(symbol_list_node->symbol->import_offset == -1) {
               printf("error:: uninitialized closure\n");
            }
            buffer[offset_size / sizeof(uint32_t)] = symbol_list_node->symbol->import_offset;
            offset_size += sizeof(uint32_t);
            symbol_list_node = symbol_list_node->next;
         }
         if(offset_size != total_offset_size) {
            printf("::error %d mismatch in offset sizes %d-%d\n", scope->id, offset_size, total_offset_size); fflush(stdout);
         }
         scope_list_node = scope_list_node->next;
      }
   }

   {
   if(state->current_scope_list_node == state->top_level_scope_list_node) {
      printf("%3d unresolved references\n", state->current_scope_list_node->scope->depth); fflush(stdout);
      reference_list_node_t* reference_list_node = state->hoisting_scope_list_node->scope->unresolved_reference_list.head;
      while(reference_list_node) {
         identifier_t* identifier = reference_list_node->reference;
         printf("\t%5d:%-2d %.*s", identifier->location->begin.line, identifier->location->begin.column, (int)(identifier->end - identifier->begin), identifier->begin); fflush(stdout);
         reference_list_node = reference_list_node->next;
      }
      printf("\n"); fflush(stdout);
#ifdef DBG_LAYOUT
      dump_frame_layout(state->top_level_scope_list_node, true);
#endif
   }
   }
   /*
   if(is_hoisting && parent){
      printf("%3d parent unresolved references\n", parent->hoisting_parent->scope->depth); fflush(stdout);
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
   if(is_hoisting) free_current_scope(state);
#ifdef COMPILER
   printf("%*s end %sscope %d:%d => (%d) +%d = %d\n", scope_depth, "", (is_hoisting ? "hoisting::" : ""), scope_depth, state->current_scope_list_node->scope->id, state->hoisting_scope_list_node->scope->id, scope->symbol_layout->stack_size, state->hoisting_scope_list_node->scope->symbol_layout->frame_size); fflush(stdout);
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
