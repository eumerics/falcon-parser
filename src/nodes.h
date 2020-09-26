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
   char_t const* code_begin;
   char_t const* code_end;
   char_t const* code;
   token_t* token_begin;
   token_t* token_end;
   token_t* token;
   uint8_t token_flags;
   uint8_t current_token_flags;
   uint8_t in_template_expression; // bool
   uint8_t in_regexp_context; // bool
   uint32_t template_level;
   uint32_t parenthesis_level;
   uint32_t curly_parenthesis_level;
   uint32_t expect_statement_after_level;
   uint32_t template_parenthesis_offset;
   uint32_t params;
   memory_state_t* memory;
   char const* error_message;
} scan_state_t;

typedef struct {
   token_t* tokens;
   size_t token_count;
   int return_value;
} scan_result_t;

typedef struct {
   parse_node_list_state_t spread;
   parse_node_list_state_t assignment;
   parse_node_list_state_t pattern;
} aggregator_cover_array_assignment_t;

typedef struct {
   aggregator_cover_array_assignment_t array;
} parse_aggregator_t;

typedef struct {
   char_t const* buffer;
   token_t* tokens;
   token_t* token;
   uint32_t depth;
   uint8_t expected_token_id;
   uint16_t expected_mask;
   char const* error_message;
   memory_state_t* memory;
   parse_aggregator_t aggregator;
} parser_state_t;

typedef struct {
   uint32_t flags;
} parser_tree_state_t;

typedef struct {
   program_t* program;
   parser_state_t state;
   scan_result_t token_result;
   int return_value;
} parser_result_t;

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

#endif //_NODES_H_
