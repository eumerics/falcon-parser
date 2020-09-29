#ifndef _NODES_H_
#define _NODES_H_

typedef struct _memory_page_t {
   uint8_t* buffer;
   size_t available;
   size_t allocated;
   struct _memory_page_t* next;
} memory_page_t;

typedef struct {
   memory_page_t* head;
   memory_page_t* current;
   size_t page_count;
} memory_state_t;

typedef struct _parse_list_node_t {
   void* parse_node;
   struct _parse_list_node_t* next;
} parse_list_node_t;
typedef struct {
   parse_list_node_t* head;
   parse_list_node_t* current;
   int node_count;
} parse_node_list_state_t;

#include "interface.h"

struct empty_list_t {} empty_list;
struct error_node_t {} error_node;
void* errptr = &error_node;

typedef struct {
   memory_state_t* memory;
   // code buffer
   char_t const* const code_begin;
   char_t const* const code_end;
   char_t const* code;
   // token buffer
   token_t const* const token_begin;
   token_t const* const token_end;
   token_t* scan_token;
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
   token_t const* parse_token;
   uint32_t depth;
   // error state
   uint8_t tokenization_status;
   uint8_t parsing_status;
   char const* error_message;
   uint8_t expected_token_id;
   uint16_t expected_mask;
} parse_state_t;

typedef struct {
   program_t* program;
   parse_state_t state;
} parse_result_t;

typedef struct {
   uint32_t flags;
} parse_tree_state_t;

#define max(a, b) ((a) > (b) ? (a) : (b))
void* parser_malloc_impl(memory_state_t* const memory, size_t size)
{
   size_t const page_size = 1 << 12; // 4kB
   size_t const remainder = (size % 4); // align to 4-bytes
   size += (remainder == 0 ? 0 : 4 - remainder);
   memory_page_t* current = memory->current;
   if(current == nullptr || current->available < size) {
      current = (memory_page_t*) malloc(sizeof(memory_page_t));
      current->buffer = (uint8_t*) malloc(max(size, page_size));
      current->available = current->allocated = max(size, page_size);
      current->next = nullptr;
      ++memory->page_count;
      if(memory->head == nullptr) {
         memory->head = current;
      } else {
         memory->current->next = current;
      }
      memory->current = current;
   }
   size_t offset = (current->allocated - current->available);
   current->available -= size;
   return current->buffer + offset;
}
#define parser_malloc(size) parser_malloc_impl(state->memory, size)

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

#endif //_NODES_H_
