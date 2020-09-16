#ifndef _NODES_H_
#define _NODES_H_

#include "interface.h"

struct empty_list_t {} empty_list;
struct error_node_t {} error_node;
void* errptr = &error_node;

typedef struct {
   token_t* tokens;
   size_t token_count;
   int return_value;
} scan_result_t;

typedef struct _memory_page_t {
   uint8_t* buffer;
   struct _memory_page_t* next;
} memory_page_t;

typedef struct {
   memory_page_t* head;
   memory_page_t* current;
   size_t available;
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
   memory_state_t memory;
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

#endif //_NODES_H_
