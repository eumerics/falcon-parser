#ifndef _INTERFACE_H_
#define _INTERFACE_H_

typedef uint16_t symbol_hash_t;

typedef struct {
   uint32_t line;
   uint32_t column;
} position_t;
typedef struct {
   position_t begin;
   position_t end;
   char const* source;
} location_t;

typedef uint16_t error_id_t;
typedef struct {
   uint16_t id;
   char const* message;
} parse_error_t;

#ifdef COMPILER
typedef uint32_t value_type_t;
struct _data_type_t;
typedef struct {
   value_type_t value_type;
   union {
      union {
         union {
            int32_t i32;
            uint32_t u32;
            float f32;
         };
         int32_t _redundant_b32;
      };
      int64_t i64;
      uint64_t u64;
      double f64;
      void* p64;
   };
} any_t;
typedef struct {
   uint32_t stack_size;
   uint32_t init_offset;
   uint32_t init_size;
   any_t* init_buffer;
   uint32_t closure_offset;
   uint32_t closure_export_size;
   any_t* closure_export_buffer;
   uint32_t closure_import_size;
   uint32_t* closure_import_buffer;
   uint32_t frame_size; // only meaningful for hoisting scopes
} symbol_layout_t;
value_type_t const vt_unimplemnted = -1;
value_type_t const vt_any = 1;
value_type_t const vt_void = 2;
value_type_t const vt_null = 3;
value_type_t const vt_undefined = 4;
value_type_t const vt_reference = 5;
value_type_t const vt_function = 6;
value_type_t const vt_boolean = 7;
value_type_t const rvt_normal = 0xff00 + 0;
value_type_t const rvt_return = 0xff00 + 1;
value_type_t const rvt_continue = 0xff00 + 2;
value_type_t const rvt_break = 0xff00 + 3;
any_t any_void = {.value_type = vt_void, .u64 = 0};
any_t any_null = {.value_type = vt_null, .u64 = 0};
any_t any_undefined = {.value_type = vt_undefined, .u64 = 0};
any_t any_unimplemented = {.value_type = vt_unimplemnted, .u64 = 0};
any_t any_true = {.value_type = vt_boolean, .u64 = 1};
any_t any_false = {.value_type = vt_boolean, .u64 = 0};
#endif

typedef struct {
   char_t const* begin;
   char_t const* end;
} string_t;
typedef struct {
   char_t const* begin;
   char_t const* end;
   uint8_t compile_flags;
   position_t offending_position;
   parse_error_t const* offending_error;
} compiled_string_t;
// incomplete
typedef struct {
   double value;
   uint8_t compile_flags;
   //position_t offending_position;
} compiled_number_t;

typedef uint8_t token_id_t;
typedef uint16_t token_group_t;
typedef union {
   struct {
      union {
         uint8_t flags;
         uint8_t precedence;
         uint8_t flags_length;
      };
      uint8_t id;
      uint16_t group;
   };
   uint32_t aggregated_id;
} aggregate_id_t;
typedef struct {
   char_t const* begin;
   char_t const* end;
   union {
      struct {
         union {
            uint8_t flags;
            uint8_t precedence;
            uint8_t flags_length;
         };
         uint8_t id;
         uint16_t group;
      };
      uint32_t aggregated_id;
   };
   void* detail;
   location_t location;
} token_t;

typedef uint8_t node_type_t;
typedef uint32_t params_t;

#ifdef EXTENSIONS
   #define if_extensions(x) x
   struct _data_type_t;
#else
   #define if_extensions(x)
#endif
#define embed_parse_node() \
   char_t const* begin; \
   char_t const* end; \
   location_t* location; \
   if_extensions(struct _data_type_t const* data_type;) \
   node_type_t type; \
   uint8_t group;
//[WATCHOUT] flags below is placed for compacting layout
// ensure that derived parse nodes do not use ovarlapping flags
#define embed_compiled_parse_node() \
   embed_parse_node() \
   uint8_t flags; \
   uint8_t token_id; \
   uint16_t token_group; \
   compiled_string_t* compiled_string;
#define embed_compiled_numeric_node() \
   embed_parse_node() \
   uint8_t flags; \
   uint8_t token_id; \
   uint16_t token_group; \
   compiled_number_t* compiled_number;

typedef struct {
   embed_parse_node();
} parse_node_t;

typedef struct {
   embed_compiled_parse_node();
} compiled_parse_node_t;

typedef struct _parse_list_node_t {
   parse_node_t* parse_node;
   struct _parse_list_node_t* next;
} parse_list_node_t;
typedef struct {
   parse_list_node_t* head;
   parse_list_node_t* current;
   int node_count;
} parse_node_list_state_t;

typedef struct _cover_list_node_t {
   parse_node_t* cover_node;
   struct _cover_list_node_t* prev;
   struct _cover_list_node_t* next;
} cover_list_node_t;
typedef struct {
   cover_list_node_t* head;
   cover_list_node_t* tail;
   size_t count;
} cover_node_list_t;

// parser node
struct _scope_t;
#ifdef EXTENSIONS
struct _type_identifier_t;
typedef struct _identifier_t identifier_t;
struct _type_list_node_t;
struct _data_type_t;
typedef struct _data_type_t {
   uint32_t id;
   uint32_t size;
   uint8_t flags;
   string_t const* name;
   uint32_t parameter_count;
   struct _data_type_t const** parameters;
   struct _type_list_node_t* instances;
} data_type_t;
typedef struct _type_list_node_t {
   data_type_t* data_type;
   struct _type_list_node_t* next;
} type_list_node_t;
typedef struct {
   type_list_node_t* head;
   type_list_node_t* tail;
} type_list_t;
typedef struct _type_identifier_t {
   embed_parse_node();
   parse_list_node_t* namespace;
   identifier_t* type_name;
   parse_list_node_t* parameters;
} type_identifier_t;
struct _function_list_node_t;
struct _function_t;
typedef struct {
   int32_t parameter_count;
   data_type_t const** parameters;
   data_type_t const* return_type;
   struct _function_t* ast;
} function_overload_t;
typedef struct _function_list_node_t {
   function_overload_t* function_overload;
   struct _function_list_node_t* next;
} function_list_node_t;
typedef struct {
   function_list_node_t* head;
   function_list_node_t* tail;
} function_list_t;
#endif
typedef struct _identifier_t {
   embed_compiled_parse_node();
#ifdef COMPILER
   int32_t offset; // offset into stack or closure variable array
#endif
#ifdef EXTENSIONS
   type_identifier_t* type_identifier;
#endif
} identifier_t;
typedef struct {
   embed_parse_node();
   uint8_t token_id;
#ifdef EXTENSIONS
   type_identifier_t* type_identifier;
#endif
} literal_t;
typedef struct {
   embed_compiled_numeric_node();
} numeric_literal_t;
typedef struct {
   embed_compiled_parse_node();
} string_literal_t;
typedef struct {
   embed_parse_node();
   uint8_t flags_length;
} regexp_literal_t;

typedef struct {
   embed_parse_node();
   //void* elements;
   void* quasis;
   void* expressions;
} template_literal_t;
typedef struct {
   embed_compiled_parse_node();
} template_element_t;

// expressions
typedef struct {
   embed_parse_node();
} this_expression_t;

typedef struct {
   embed_parse_node();
   void* argument;
   cover_list_node_t* cover_node;
} spread_element_t;
// keep spread_element_t and rest_element_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef spread_element_t rest_element_t;

typedef struct {
   embed_parse_node();
   uint8_t has_trailing_comma;
   void* elements;
#ifdef EXTENSIONS
   uint64_t operators;
#endif
} array_expression_t;
// keep array_expression_t and array_pattern_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef array_expression_t array_pattern_t;

typedef struct {
   embed_parse_node();
   uint8_t kind;
   uint8_t flags;
   void* key;
   void* value;
} property_t;
typedef property_t assignment_property_t;
typedef property_t method_definition_t;

typedef struct {
   embed_parse_node();
   void* left;
   void* right;
} binding_assignment_t;
typedef struct {
   embed_parse_node();
   void* left;
   void* right;
   cover_list_node_t* cover_node;
} initialized_name_t;
typedef struct {
   embed_parse_node();
   uint8_t has_trailing_comma;
   void* properties;
} object_expression_t;
// keep object_expression_t and object_pattern_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef object_expression_t object_pattern_t;

typedef struct {
   embed_parse_node();
   void* expression;
} parenthesized_expression_t;

typedef struct {
   embed_parse_node();
} super_t;

typedef struct {
   embed_parse_node();
   void* meta;
   void* property;
} meta_property_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   void* object;
   void* property;
} member_expression_t;

typedef struct {
   embed_parse_node();
   void* tag;
   void* quasi;
} tagged_template_expression_t;

typedef struct {
   embed_parse_node();
   void* callee;
   void* arguments;
} new_expression_t;

typedef struct {
   embed_parse_node();
   void* source;
} import_call_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   void* callee;
   void* arguments;
} call_expression_t;
typedef call_expression_t covered_call_expression_t;

typedef struct {
   embed_parse_node();
   void* expression;
} chain_expression_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   aggregate_id_t operator;
   void* argument;
} update_expression_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   aggregate_id_t operator;
   void* argument;
} unary_expression_t;

typedef struct {
   embed_parse_node();
   aggregate_id_t operator;
   void* left;
   void* right;
} binary_expression_t;
typedef binary_expression_t logical_expression_t;

typedef struct {
   embed_parse_node();
   void* test;
   void* consequent;
   void* alternate;
} conditional_expression_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   void* argument;
} yield_expression_t;

typedef struct {
   embed_parse_node();
   void* argument;
} await_expression_t;

typedef struct {
   embed_parse_node();
   void* left;
   void* right;
   aggregate_id_t operator;
} assignment_expression_t;
// keep assignment_expression_t and assignment_pattern_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef struct {
   embed_parse_node();
   void* left;
   void* right;
} assignment_pattern_t;

typedef struct {
   embed_parse_node();
   void* expressions;
} expression_t;

/*
typedef struct {
   embed_parse_node();

} _expression_t;
*/

// declarations
typedef struct {
   embed_parse_node();
   uint8_t kind;
   void* declarations;
} variable_declaration_t;

typedef struct {
   embed_parse_node();
   void* id;
   void* init;
} variable_declarator_t;

typedef struct {
   embed_parse_node();
   void* body;
} function_body_t;
typedef struct _function_t {
   embed_parse_node();
   uint8_t flags;
   void* id;
   void* params;
   void* body;
#ifdef COMPILER
   symbol_layout_t* symbol_layout;
#endif
#ifdef EXTENSIONS
   uint8_t operator_id;
   data_type_t const* return_type;
   type_identifier_t* return_type_identifier;
#endif
} function_t;
typedef function_t function_declaration_t;
typedef function_t function_expression_t;
// we will keep the redundant id for convenience and for compatibility with
// estree specification
typedef function_t arrow_function_expression_t;

typedef struct {
   embed_parse_node();
   void* body;
} class_body_t;
typedef struct {
   embed_parse_node();
   void* id;
   void* super_class;
   void* body;
} class_t;
typedef class_t class_declaration_t;
typedef class_t class_expression_t;

/*
typedef struct {
   embed_parse_node();

} _declaration_t;
*/

// statements
typedef struct {
   embed_parse_node();
   void* body;
#ifdef COMPILER
   symbol_layout_t* symbol_layout;
#endif
} block_statement_t;

typedef struct {
   embed_parse_node();
} empty_statement_t;

typedef struct {
   embed_parse_node();
   void* expression;
} expression_statement_t;
typedef expression_statement_t directive_t;

typedef struct {
   embed_parse_node();
   void* test;
   void* consequent;
   void* alternate;
} if_statement_t;

typedef struct {
   embed_parse_node();
   void* body;
   void* test;
} do_statement_t;

typedef struct {
   embed_parse_node();
   void* test;
   void* body;
} while_statement_t;

typedef struct {
   embed_parse_node();
   void* body;
   void* init;
   void* test;
   void* update;
#ifdef COMPILER
   symbol_layout_t* symbol_layout;
#endif
} for_statement_t;

typedef struct {
   embed_parse_node();
   void* body;
   void* left;
   void* right;
} for_in_statement_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   void* body;
   void* left;
   void* right;
} for_of_statement_t;

typedef struct {
   embed_parse_node();
   void* test;
   void* consequent;
} case_clause_t;

typedef struct {
   embed_parse_node();
   void* discriminant;
   void* cases;
#ifdef COMPILER
   symbol_layout_t* symbol_layout;
#endif
} switch_statement_t;

typedef struct {
   embed_parse_node();
   void* label;
} continue_statement_t;

typedef struct {
   embed_parse_node();
   void* label;
} break_statement_t;

typedef struct {
   embed_parse_node();
   void* argument;
} return_statement_t;

typedef struct {
   embed_parse_node();
   void* object;
   void* body;
} with_statement_t;

typedef struct {
   embed_parse_node();
   void* label;
   void* body;
} labeled_statement_t;

typedef struct {
   embed_parse_node();
   void* argument;
} throw_statement_t;

typedef struct {
   embed_parse_node();
   void* block;
   void* handler;
   void* finalizer;
#ifdef COMPILER
   symbol_layout_t* symbol_layout;
#endif
} try_statement_t;

typedef struct {
   embed_parse_node();
   void* param;
   void* body;
} catch_clause_t;

typedef struct {
   embed_parse_node();
} debugger_statement_t;

/*
typedef struct {
   embed_parse_node();

} _statement_t;
*/

typedef struct {
   embed_parse_node();
   parse_list_node_t* specifiers;
   literal_t* source;
} import_declaration_t;
typedef struct {
   embed_parse_node();
   identifier_t* local;
} module_specifier_t;
typedef module_specifier_t import_default_specifier_t;
typedef module_specifier_t import_namespace_specifier_t;
typedef struct {
   embed_parse_node();
   identifier_t* local;
   identifier_t* imported;
} import_specifier_t;

typedef struct {
   embed_parse_node();
   identifier_t* exported;
   literal_t* source;
} export_all_declaration_t;
typedef struct {
   embed_parse_node();
   parse_list_node_t* specifiers;
   literal_t* source;
   void* declaration;
} export_named_declaration_t;
typedef struct {
   embed_parse_node();
   void* declaration;
} export_default_declaration_t;
typedef struct {
   embed_parse_node();
   identifier_t* local;
   identifier_t* exported;
} export_specifier_t;

typedef struct {
   embed_parse_node();
   uint8_t source_type;
   void* body;
#ifdef COMPILER
   symbol_layout_t* symbol_layout;
#endif
} program_t;

typedef struct {
   uint8_t type;
   uint8_t binding_flag;
   int32_t offset;
   int32_t import_offset;
   identifier_t* identifier;
} symbol_t;
typedef struct _symbol_list_node_t {
   symbol_t* symbol;
   // next symbol in the list
   struct _symbol_list_node_t* next;
#ifdef COMPILER
   // forms a list of symbols in a given scope not including child scopes
   struct _symbol_list_node_t* scope_next;
#endif
   // forms a list of symbols in a given scope including child scopes
   struct _symbol_list_node_t* sequence_next;
} symbol_list_node_t;
typedef struct {
   symbol_list_node_t* head;
   symbol_list_node_t* tail;
} symbol_list_t;
typedef struct {
   identifier_t const* original;
   identifier_t const* duplicate;
} repeated_symbol_t;
typedef struct _scope_child_list_node_t scope_child_list_node_t;
typedef struct _scope_child_list_t {
   scope_child_list_node_t* head;
   scope_child_list_node_t* tail;
} scope_child_list_t;
typedef struct _label_list_node_t {
   identifier_t const* identifier;
   struct _label_list_node_t* parent;
} label_list_node_t;
#ifdef COMPILER
   struct _scope_t;
   typedef struct _scope_list_node_t scope_list_node_t;
   typedef struct _reference_list_node_t {
      identifier_t* reference;
      symbol_t const* resolved_symbol;
      scope_list_node_t* scope_list_node;
#ifdef DBG_LAYOUT
      scope_list_node_t* original_scope_list_node;
#endif
      struct _reference_list_node_t* prev;
      struct _reference_list_node_t* next;
   } reference_list_node_t;
   typedef struct {
      reference_list_node_t* head;
      reference_list_node_t* tail;
   } reference_list_t;
#endif
typedef struct _scope_t {
   uint8_t flags;
   identifier_t* identifier;
   repeated_symbol_t* first_duplicate;
   void* first_yield_or_await;
   symbol_list_t** lexical_symbol_table;
   symbol_list_t** var_symbol_table;
   label_list_node_t* label_list_node;
   symbol_list_node_t* last_symbol_list_node; // for tracking the last symbol at hositing scope level
   symbol_list_t symbol_list; // list of symbols at the scope level
#ifdef COMPILER
   uint32_t id;
   uint32_t depth;
   symbol_list_t full_symbol_list; // list af all symbols including child scopes
   reference_list_t resolved_reference_list;
   reference_list_t unresolved_reference_list;
   symbol_list_t closure_import_symbol_list;
   symbol_layout_t* symbol_layout; // layout of scope level variables
#endif
} scope_t;
typedef struct _simple_scope_list_node_t simple_scope_list_node_t;
typedef struct _simple_scope_list_node_t {
   scope_t* scope;
   simple_scope_list_node_t* next;
} simple_scope_list_node_t;
typedef struct {
   simple_scope_list_node_t* head;
   simple_scope_list_node_t* tail;
} simple_scope_list_t;
typedef struct _scope_list_node_t scope_list_node_t;
typedef struct _scope_list_node_t {
   scope_t* scope;
   scope_list_node_t* prev;
   scope_list_node_t* next;
   scope_list_node_t* parent;
   scope_list_node_t* hoisting_parent;
   scope_child_list_t child_list;
} scope_list_node_t;
typedef struct _scope_child_list_node_t {
   scope_list_node_t* scope_list_node;
   struct _scope_child_list_node_t* prev;
   struct _scope_child_list_node_t* next;
} scope_child_list_node_t;

struct empty_list_t {} empty_list;
struct error_node_t {} error_node;
void* errptr = &error_node;

typedef struct {
   // error state
   uint8_t tokenization_status;
   uint8_t parsing_status;
   parse_error_t const* parse_error;
   position_t error_position;
   //token_t const* error_token;
   uint8_t expected_token_id;
   uint16_t expected_mask;
   // [20]
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
   size_t tokens_consumed;
   // scanner flags [56]
   uint32_t line_number;
   char_t const* line_begin;
   uint8_t token_flags;
   uint8_t current_token_flags;
   uint8_t in_template_expression; // bool
   uint8_t in_regexp_context; // bool
   uint8_t is_continuer; // bool
   uint8_t was_continuer; // bool
   uint8_t was_contextual; // bool
   uint32_t template_level;
   uint32_t parenthesis_level;
   uint32_t curly_parenthesis_level;
   uint32_t expect_statement_after_level;
   uint32_t template_parenthesis_offset;
   // parser [92]
   token_t* parse_token;
   cover_node_list_t cover_node_list;
   uint32_t depth; // parse depth
   uint32_t semantic_flags;
   // scope
   uint32_t scope_count;
   uint32_t scope_depth;
   scope_list_node_t* scope_list_node;
   scope_list_node_t* top_level_scope_list_node;
   scope_list_node_t* current_scope_list_node;
   scope_list_node_t* hoisting_scope_list_node;
   simple_scope_list_t closure_scope_list;
#ifdef EXTENSIONS
   type_list_t type_list;
   function_list_t operator_table[256];
#endif
   // module
   symbol_list_t** export_symbol_table;
   symbol_list_t* export_reference_list;
   uint8_t has_default_export;
} parse_state_t;

typedef struct {
   program_t* program;
   parse_state_t state;
} parse_result_t;

typedef struct {
   uint32_t flags;
} parse_tree_state_t;

void* malloc(size_t t);

void parser_free(parse_state_t* state)
{
   //free((void *)(state->token_begin));
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

inline_spec position_t make_position(parse_state_t const* const state)
{
   return (position_t){
      .line = state->line_number,
      .column = state->code - state->line_begin
   };
}
inline_spec position_t make_given_position(parse_state_t const* const state, char_t const* code)
{
   return (position_t){
      .line = state->line_number,
      .column = code - state->line_begin
   };
}

#endif //_INTERFACE_H_
