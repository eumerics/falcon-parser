#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define show_token printf
#define log_token(__VA_ARGS__)

typedef struct {
   uint64_t punctuator;
   uint64_t identifier;
   uint64_t reserved_word;
   uint64_t string_compares;
   uint64_t whitespace;
   uint64_t terminator;
   uint64_t comment;
   uint64_t numeric_literal;
   uint64_t string_literal;
   uint64_t regexp_literal;
} elements_t;
elements_t counts1 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
elements_t counts2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
elements_t timings1 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
elements_t timings2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
elements_t characters1 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
elements_t characters2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};

#define print_string(x) printf(x)
#define print_number(x) printf("%x", x)
#ifdef verbose
   #define profile
#endif

#include "common.h"
#include "nodes.h"
#ifdef verbose
   void assert(int value, char const* file_name, size_t line_number)
   {
      if(!value) {
         printf(color_bold_red("assertion failed at %s:%zu") "\n", file_name, line_number);
         fflush(stdout);
         abort();
      }
   }
   #define _print_parse_descent(type, remove_filter, add_filter) { \
      uint32_t new_params = make_params(remove_filter, add_filter); \
      printf( \
         "%*s=> %s " color_bold_bright_black("(%s%s%s%s%s%s%s%s%s%s )") " [%d]\n", \
         (state->depth % 60), "", #type, \
         (new_params & param_flag_await ? " await" : ""), \
         (new_params & param_flag_default ? " default" : ""), \
         (new_params & param_flag_in ? " in" : ""), \
         (new_params & param_flag_return ? " return" : ""), \
         (new_params & param_flag_yield ? " yield" : ""), \
         (new_params & cover_flag_initializer ? " cover-init" : ""), \
         (new_params & cover_flag_parameters ? " cover-params" : ""), \
         (new_params & param_flag_for_binding ? " for-binding" : ""), \
         (new_params & param_flag_annex ? " annex" : ""), \
         (new_params & param_flag_strict_mode ? " strict" : ""), \
         state->depth \
      ); \
      fflush(stdout); \
      ++state->depth; \
   }
   #define _print_parse_ascent(node) { \
      --state->depth; \
      printf("%*s<= [%d]", (state->depth % 60), "", state->depth); \
      if(node == nullptr) printf(" nullptr"); \
      printf("\n"); \
      fflush(stdout); \
   }
   #define print_make_node(node_type) { \
      printf( \
         color_bold_magenta("%*s-- making node %s") "\n", \
         state->depth % 60, "", #node_type \
      ); \
      fflush(stdout); \
   }
   #define print_token(token, length) printf("%.*s\n", (int)(length), token)
   #if !defined(UTF16)
      #define print_token_consumption() ( \
         printf( \
            color_bold_cyan("%*s-- consumed token '%.*s'") "\n", \
            state->depth % 60, "", \
            (int)(state->token->end - state->token->begin), \
            state->buffer + state->token->begin \
         ), \
         fflush(stdout) \
      )
   #else
      #define print_token_consumption() ( \
         printf( \
            color_bold_cyan("%*s-- consumed token '%.*s'") "\n", \
            state->depth % 60, "", \
            2 * (int)(state->token->end - state->token->begin), \
            (char const*)(state->buffer + state->token->begin) \
         ), \
         fflush(stdout) \
      )
   #endif
#else
   #define _print_parse_descent(type, remove_filter, add_filter)
   #define _print_parse_ascent(depth)
   #define print_make_node(node_type)
   #define print_token_consumption()
   #define print_token(token, length)
#endif
#define begin_group(name)
#define end_group()

#include "scanner.h"
#if defined(SIMD)
   #include "simd/literals.h"
   #include "simd/identifier.h"
   #include "simd/punctuator.h"
   #include "simd/comment.h"
   #include "simd/scanner.h"
#endif
#include "parser.h"

int main(int argc, char* argv[])
{
   if(argc > 1) {
      FILE* fp = fopen(argv[1], "r");
      bool is_module = true;
      if(fp != NULL) {
         fseek(fp, 0L, SEEK_END);
         size_t file_size = ftell(fp);
         size_t buffer_size = (file_size | 0x1f) + 0x01 + 0x20;
         fseek(fp, 0L, SEEK_SET);
         char* source = (char *) aligned_alloc(32, buffer_size);
         //char* source = (char *) malloc(file_size + 1);
         fread(source, 1, file_size, fp);
         fclose(fp);
         source[file_size] = 0;
         #if defined(verbose) || defined(profile)
            int iterations = 1;
         #else
            int iterations = (argc > 2 ? atoi(argv[2]) : 1000);
         #endif
         ///*
         {
            //scan_result_t result;
            parser_result_t result;
            clock_t cbegin = clock();
            uint64_t begin = __rdtsc();
            uint32_t params = param_flag_annex;
            for(int it = 0; it < iterations; ++it) {
               //result = tokenize(source, source + file_size);
               //free(result.tokens);
               result = parse(source, source + file_size, is_module, params);
               if(it != iterations - 1) parser_free(&result.state);
            }
            uint64_t end = __rdtsc();
            clock_t cend = clock();
            if(result.token_result.return_value == 1) {
               if(result.return_value == 1) {
                  printf(color_bold_green("parsing successful") "\n");
               } else {
                  printf(color_bold_red("parsing failed") "\n");
                  if(result.state.error_message != nullptr) {
                     printf(color_bold_red("%s") "\n", result.state.error_message);
                  }
                  size_t begin = result.state.token->begin;
                  int length = result.state.token->end - begin;
                  printf("\nparsing failed at character index %zu %.*s\n", begin, length, result.state.buffer + begin);
                  printf("token found: %x %x %c\n", result.state.token->id, result.state.token->group, result.state.token->id);
                  printf("token expected: %x %c\n", result.state.expected_token_id, result.state.expected_token_id);
                  //printf("token found: %x %x %c\n", result.state.token->id, result.state.token->group, result.state.token->id);
                  //printf("token expected: %x %c\n", result.state.expected_token_id, result.state.expected_token_id);
               }
            } else {
               printf(color_bold_red("tokenization failed") "\n");
            }
            //printf("%lu\n", (end - begin) / iterations);
            printf("%lu %.3f\n", (end - begin) / iterations, 1000 * ((double)(cend - cbegin)) / CLOCKS_PER_SEC / iterations);
         }
         //*/
         #if 0
         defined(SIMD)
         {
            int result;
            clock_t cbegin = clock();
            uint64_t begin = __rdtsc();
            for(int it = 0; it < iterations; ++it) {
               result = tokenize_vectorized3(source, source + file_size);
            }
            uint64_t end = __rdtsc();
            clock_t cend = clock();
            if(result == 1) {
               printf(color_bold_green("tokenization successful") "\n");
            } else {
               printf(color_bold_red("tokenization failed") "\n");
            }
            //printf("%lu\n", (end - begin) / iterations);
            printf("%lu %ld\n", (end - begin) / iterations, 1000 * (cend - cbegin) / CLOCKS_PER_SEC);
         }
         #endif
         //*/
         #if defined(profile)
            #define print_element(name) printf( \
               "%16s: %9ld %9ld %9ld %9ld %10ld %10ld\n", #name, \
               counts1.name / iterations, counts2.name / iterations, \
               characters1.name / iterations, characters2.name / iterations, \
               timings1.name / iterations, timings2.name / iterations \
            )
         #else
            #define print_element(name)
         #endif
         print_element(identifier);
         print_element(reserved_word);
         print_element(string_compares);
         print_element(punctuator);
         print_element(whitespace);
         print_element(terminator);
         print_element(comment);
         print_element(numeric_literal);
         print_element(string_literal);
         print_element(regexp_literal);
      }
   }

   return 0;
}
