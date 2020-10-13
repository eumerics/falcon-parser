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

void new_scope(parse_state_t* state)
{
   size_t const size = symbol_hash_table_size * sizeof(symbol_list_node_t*);
   scope_list_node_t* scope_list_node = state->scope_list_node;
   if(scope_list_node == nullptr || scope_list_node->next == nullptr) {
      scope_list_node_t* new_scope_list_node = parser_malloc(sizeof(scope_list_node_t));
      scope_t* new_scope = parser_malloc(sizeof(scope_t));
      *new_scope = (scope_t){
         .parent = (scope_list_node ? scope_list_node->scope : nullptr),
         .symbol_table = parser_malloc(size)
      };
      *new_scope_list_node = (scope_list_node_t){
         .scope = new_scope, .prev = scope_list_node, .next = nullptr
      };
      if(scope_list_node) scope_list_node->next = new_scope_list_node;
      state->scope = new_scope;
      state->scope_list_node = new_scope_list_node;
   } else {
      scope_list_node = scope_list_node->next;
      state->scope = scope_list_node->scope;
      state->scope_list_node = scope_list_node;
   }
   memset(state->scope->symbol_table, 0, size);
}

void end_scope(parse_state_t* state)
{
   state->scope = state->scope->parent;
   state->scope_list_node = state->scope_list_node->prev;
}

uint8_t insert_symbol(parse_state_t* state, compiled_parse_node_t const* node, uint8_t binding_type)
{
   symbol_t const* symbol = (node->compiled_string ? (symbol_t*)(node->compiled_string) : (symbol_t*)(node));
   scope_t* const scope = state->scope;
   size_t const symbol_length = symbol->end - symbol->begin;
   uint16_t hash = (
      ((symbol_length & symbol_length_mask) << 5) |
      (*symbol->begin & symbol_first_letter_mask)
   );
   symbol_list_node_t* symbol_node = scope->symbol_table[hash];
   if(symbol_node != nullptr) {
      while(1) {
         symbol_t const* compare_symbol = symbol_node->symbol;
         size_t const compare_symbol_length = compare_symbol->end - compare_symbol->begin;
         if(symbol_length == compare_symbol_length &&
            strncmp_impl(symbol->begin, compare_symbol->begin, compare_symbol_length) == 0 &&
            !(symbol_node->binding_type == rw_var && binding_type == rw_var)
         ){
            return 0;
         }
         if(symbol_node->next == nullptr) {
            symbol_list_node_t* new_symbol_node = parser_malloc(sizeof(symbol_list_node_t));
            *new_symbol_node = (symbol_list_node_t){
               .symbol = symbol, .binding_type = binding_type, .next = nullptr
            };
            symbol_node->next = new_symbol_node;
            return 1;
         }
         symbol_node = symbol_node->next;
      }
   } else {
      symbol_list_node_t* new_symbol_node = parser_malloc(sizeof(symbol_list_node_t));
      *new_symbol_node = (symbol_list_node_t){
         .symbol = symbol, .binding_type = binding_type, .next = nullptr
      };
      scope->symbol_table[hash] = new_symbol_node;
      return 1;
   }
}

#endif //_SCOPE_H_
