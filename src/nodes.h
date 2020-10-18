#ifndef _NODES_H_
#define _NODES_H_

#include "memory.h"
#include "interface.h"

struct empty_list_t {} empty_list;
struct error_node_t {} error_node;
void* errptr = &error_node;

typedef struct {
   // error state
   uint8_t tokenization_status;
   uint8_t parsing_status;
   char const* error_message;
   token_t const* error_token;
   uint8_t expected_token_id;
   uint16_t expected_mask;
   //
   memory_state_t* memory;
   // code buffer
   char_t const* const code_begin;
   char_t const* const code_end;
   char_t const* code;
   // token buffer
   token_t const* const token_begin;
   token_t const* const token_end;
   token_t* scan_token;
   size_t token_count;
   // scanner flags
   uint8_t token_flags;
   uint8_t current_token_flags;
   uint8_t in_template_expression; // bool
   uint8_t in_regexp_context; // bool
   uint8_t is_comment; // bool
   uint8_t was_comment; // bool
   uint32_t template_level;
   uint32_t parenthesis_level;
   uint32_t curly_parenthesis_level;
   uint32_t expect_statement_after_level;
   uint32_t template_parenthesis_offset;
   // parser
   token_t* parse_token;
   cover_node_list_t cover_node_list;
   uint32_t depth;
   uint32_t semantic_flags;
   scope_list_node_t* current_scope_list_node;
   scope_list_node_t* scope_list_node;
   scope_list_node_t* hoisting_scope_list_node;
} parse_state_t;

typedef struct {
   program_t* program;
   parse_state_t state;
} parse_result_t;

typedef struct {
   uint32_t flags;
} parse_tree_state_t;

void parser_free(parse_state_t* state)
{
   free((void *)(state->token_begin));
   memory_page_t* current = state->memory->head;
   while(current != nullptr) {
      free(current->buffer);
      memory_page_t* to_free = current;
      current = current->next;
      free(to_free);
   }
   state->memory->head = nullptr;
   state->memory->current = nullptr;
   state->memory->page_count = 0;
}

#include "scope.h"
#endif //_NODES_H_
