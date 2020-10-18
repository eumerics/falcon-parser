#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <stdint.h>
#include "constants.h"

uint16_t const symbol_first_letter_bits = 5;
uint16_t const symbol_length_bits = 5;
uint16_t const hash_bits = symbol_first_letter_bits + symbol_length_bits;
uint16_t const symbol_first_letter_mask = (1 << symbol_first_letter_bits) - 1;
uint16_t const symbol_length_mask = (1 << symbol_length_bits) - 1;
uint16_t const symbol_hash_table_size = 1 << hash_bits;

void add_child(parse_state_t* state, scope_list_node_t* parent_scope_list_node, scope_list_node_t* child_scope_list_node)
{
   child_scope_list_node->parent = parent_scope_list_node;
   if(!parent_scope_list_node) return;
   scope_child_list_node_t* child_list_node = parser_malloc(sizeof(scope_child_list_node_t));
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

void new_scope(parse_state_t* state, uint8_t is_hoisting)
{
   size_t const size = symbol_hash_table_size * sizeof(symbol_list_node_t*);
   scope_list_node_t* scope_list_node = state->scope_list_node;
   scope_list_node_t* next_scope_list_node;
   scope_t* child_scope;
   if(scope_list_node == nullptr || scope_list_node->next == nullptr) {
      child_scope = parser_malloc(sizeof(scope_t));
      *child_scope = (scope_t){
         .first_duplicate = nullptr,
         .lexical_symbol_table = parser_malloc(size),
         .var_symbol_table = parser_malloc(size)
      };
      next_scope_list_node = parser_malloc(sizeof(scope_list_node_t));
      *next_scope_list_node = (scope_list_node_t){
         .scope = child_scope,
         .prev = scope_list_node, .next = nullptr,
         .parent = nullptr, .hoisting_parent = nullptr,
         .child_list = {.head = nullptr, .tail = nullptr},
      };
      if(scope_list_node) scope_list_node->next = next_scope_list_node;
   } else {
      next_scope_list_node = scope_list_node->next;
      child_scope = next_scope_list_node->scope;
      child_scope->first_duplicate = nullptr;
      next_scope_list_node->child_list =
         (scope_child_list_t){.head = nullptr, .tail = nullptr};
   }
   add_child(state, state->current_scope_list_node, next_scope_list_node);
   state->scope_list_node = next_scope_list_node;
   state->current_scope_list_node = next_scope_list_node;
   if(is_hoisting) state->hoisting_scope_list_node = next_scope_list_node;
   next_scope_list_node->hoisting_parent = state->hoisting_scope_list_node;
   memset(child_scope->var_symbol_table, 0, size);
   memset(child_scope->lexical_symbol_table, 0, size);
}

void end_scope(parse_state_t* state)
{
   if(state->current_scope_list_node == state->hoisting_scope_list_node) {
      state->scope_list_node = state->current_scope_list_node->prev;
      scope_list_node_t* parent = state->current_scope_list_node->parent;
      if(parent) {
         scope_child_list_t* child_list = &(parent->child_list);
         if(child_list->head == child_list->tail) {
            child_list->head = child_list->tail = nullptr;
         } else {
            child_list->tail->prev->next = nullptr;
            child_list->tail = child_list->tail->prev;
         }
      }
   }
   state->current_scope_list_node = state->current_scope_list_node->parent;
   state->hoisting_scope_list_node = state->current_scope_list_node->hoisting_parent;
}

uint8_t is_scope_unique(parse_state_t const* const state)
{
   if(state->current_scope_list_node->scope->first_duplicate) {
      //[TODO] set error
      return 0;
   }
   return 1;
}

uint8_t get_symbol(
   symbol_t const* const symbol, size_t const symbol_length,
   uint16_t hash, symbol_list_node_t** symbol_list_node_ref
){
   symbol_list_node_t* symbol_list_node = *symbol_list_node_ref;
   while(1) {
      compiled_parse_node_t const* compare_node = symbol_list_node->symbol_node;
      symbol_t const* compare_symbol = (
         compare_node->compiled_string ? (symbol_t*)(compare_node->compiled_string) : (symbol_t*)(compare_node)
      );
      size_t const compare_symbol_length = compare_symbol->end - compare_symbol->begin;
      if(symbol_length == compare_symbol_length &&
         strncmp_impl(symbol->begin, compare_symbol->begin, compare_symbol_length) == 0
      ){
         *symbol_list_node_ref = symbol_list_node;
         return 1;
      }
      // point to the last element if symbol lookup fails to make appending easy
      if(symbol_list_node->next == nullptr) {
         *symbol_list_node_ref = symbol_list_node;
         return 0;
      }
      symbol_list_node = symbol_list_node->next;
   }
}

uint8_t has_symbol_in_tree(
   symbol_t const* const symbol, size_t const symbol_length,
   uint16_t hash, scope_list_node_t* scope_list_node
){
   uint8_t has_symbol = 0;
   scope_child_list_node_t* scope_child_list_node = scope_list_node->child_list.head;
   while(!has_symbol && scope_child_list_node) {
      scope_list_node_t* t = scope_child_list_node->scope_list_node;
      if(t) {
         has_symbol = has_symbol_in_tree(symbol, symbol_length, hash, t);
      }
      scope_child_list_node = scope_child_list_node->next;
   }
   if(!has_symbol) {
      symbol_list_node_t* symbol_list_node = scope_list_node->scope->var_symbol_table[hash];
      if(symbol_list_node) {
         has_symbol = get_symbol(symbol, symbol_length, hash, &symbol_list_node);
      }
   }
   return has_symbol;
}

uint8_t insert_symbol(parse_state_t* state, compiled_parse_node_t const* node, uint8_t binding_flag, params_t params)
{
   symbol_t const* symbol = (node->compiled_string ? (symbol_t*)(node->compiled_string) : (symbol_t*)(node));
   size_t const symbol_length = symbol->end - symbol->begin;
   uint16_t hash = (
      ((symbol_length & symbol_length_mask) << 5) |
      (*symbol->begin & symbol_first_letter_mask)
   );
   uint8_t has_list = 0, has_symbol = 0;
   symbol_list_node_t* symbol_list_node;
   symbol_list_node_t** symbol_table;
   scope_t* const scope = state->current_scope_list_node->scope;
   if(binding_flag & param_flag_loose_binding) {
      scope_list_node_t const* lookup_scope_list_node = state->current_scope_list_node;
      while(!has_symbol) {
         symbol_list_node = lookup_scope_list_node->scope->lexical_symbol_table[hash];
         if(symbol_list_node) {
            has_symbol = get_symbol(symbol, symbol_length, hash, &symbol_list_node);
         }
         if(lookup_scope_list_node == state->hoisting_scope_list_node) break;
         lookup_scope_list_node = lookup_scope_list_node->parent;
      }
      if(!has_symbol) {
         symbol_table = scope->var_symbol_table;
         symbol_list_node = symbol_table[hash];
         if(symbol_list_node) {
            has_list = 1;
            has_symbol = get_symbol(symbol, symbol_length, hash, &symbol_list_node);
         }
      }
   } else {
      has_symbol = has_symbol_in_tree(symbol, symbol_length, hash, state->current_scope_list_node);
      if(!has_symbol) {
         symbol_table = scope->lexical_symbol_table;
         symbol_list_node = symbol_table[hash];
         if(symbol_list_node) {
            has_list = 1;
            has_symbol = get_symbol(symbol, symbol_length, hash, &symbol_list_node);
         }
      }
   }
   if(has_symbol) {
      if(!scope->first_duplicate) {
         compiled_parse_node_t const* compare_node = symbol_list_node->symbol_node;
         repeated_symbol_t* t = parser_malloc(sizeof(repeated_symbol_t));
         *t = (repeated_symbol_t){.original = compare_node, .duplicate = node};
         scope->first_duplicate = t;
      }
      if((params & param_flag_unique_params) || !(symbol_list_node->binding_flag & binding_flag)) {
         return 0;
      }
   }
   symbol_list_node_t* new_symbol_list_node = parser_malloc(sizeof(symbol_list_node_t));
   *new_symbol_list_node = (symbol_list_node_t){
      .symbol_node = node, .binding_flag = binding_flag, .next = nullptr
   };
   if(has_list) symbol_list_node->next = new_symbol_list_node;
   else symbol_table[hash] = new_symbol_list_node;
   return 1;
}

#endif //_SCOPE_H_
