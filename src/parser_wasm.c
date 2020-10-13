#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "nodes.h"

#define wasm_export __attribute__ ((visibility ("default")))
#define start_clock(x)
#define print_string(x) log_string(x, strlen(x))
#define print_number(x) log_number(x)

//#define printf(x) show_token_type(x)
//#define if_verbose(x) x
extern void show_token_type(char const*);
extern void show_token(char const*, int, char const*);
//extern void log_token(char const*, int, char const*, int, int, int, int);
extern void log_node(void*, int, int, int, void*);
extern void log_string(void const* string_pointer, size_t length);
extern void log_number(uint32_t number);
/*
extern void printf1(char const* const);
extern void printf2(char const* const, char const* const);
extern void printf3(char const* const, char const* const, char const* const);
extern void printf4(char const* const, char const* const, char const* const, char const* const);
extern void printf5(char const* const, char const* const, char const* const, char const* const, char const* const);
#define __get_6th_arg(arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6
//#define __get_5th_arg(arg1, arg2, arg3, arg4, arg5, ...) arg5
#define _choose_printf(...) __get_6th_arg(__VA_ARGS__, printf5, printf4, printf3, printf2, printf1, )
#define printf(...) _choose_printf(__VA_ARGS__)(__VA_ARGS__)
//*/
//#define fflush(x)
//#define printf print
//#define printf(__VA_ARGS__) print(__VA_ARGS__)
extern void print(char const*, ...);
extern void log_pointer(void*);

extern void log_parse_descent(
   char const* type_pointer, size_t type_length, uint32_t depth, uint32_t params
);
extern void log_parse_ascent(uint32_t depth, void* node);
extern void log_token_consumption(void const* buffer, size_t begin, size_t end, uint32_t depth);
extern void log_make_node(char const* type_pointer, size_t type_length, uint32_t depth);
extern void begin_group_impl(char const* type_pointer, size_t type_length);
extern void end_group();
extern void log_token(char_t const* token, size_t length);
extern void log_assertion(char const* file_name, size_t length, size_t line_number);
extern void log_params(params_t params);

#ifdef verbose
   void assert(int value, char const* file_name, size_t line_number)
   {
      if(!value) {
         log_assertion(file_name, strlen(file_name), line_number);
         abort();
      }
   }
   #define _print_parse_descent(type, remove_filter, add_filter) { \
      uint32_t new_params = make_params(remove_filter, add_filter); \
      log_parse_descent(#type, strlen(#type), state->depth, new_params); \
      ++state->depth; \
   }
   #define _print_parse_ascent(node) { --state->depth; log_parse_ascent(state->depth, node); }
   #define print_make_node(node_type) log_make_node(#node_type, strlen(#node_type), state->depth)
   #define print_token_consumption() \
      log_token_consumption(state->code_begin, state->parse_token->begin - state->code_begin, state->parse_token->end - state->code_begin, state->depth)
   #define begin_group(name) begin_group_impl(name, strlen(name))
   #define print_token(token, length) log_token(token, length)
   #define print_params(params) log_params(params);
#else
   #define _print_parse_descent(type, remove_filter, add_filter)
   #define _print_parse_ascent(node)
   #define print_make_node(node_type)
   #define print_token_consumption()
   #define begin_group(name)
   #define print_token(token, length)
   #define print_params(params)
#endif

#include "scanner.h"
#include "parser.h"
#include <stdlib.h>

void* wasm_malloc(int size) {
   return malloc(size);
}
void wasm_free(void* pointer) {
   return free(pointer);
}
void* get_empty_list() {
   return &empty_list;
}
