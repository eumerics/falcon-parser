#ifndef _INTERFACE_H_
#define _INTERFACE_H_

typedef struct {
   size_t line;
   size_t column;
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

#define embed_parse_node() \
   char_t const* begin; \
   char_t const* end; \
   location_t* location; \
   node_type_t type; \
   uint8_t group;
#define embed_compiled_parse_node() \
   embed_parse_node() \
   uint8_t flags; \
   uint8_t token_id; \
   uint16_t token_group; \
   compiled_string_t* compiled_string;

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
typedef struct {
   embed_compiled_parse_node();
} identifier_t;
typedef struct {
   embed_parse_node();
   uint8_t token_id;
} literal_t;
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
typedef struct {
   embed_parse_node();
   uint8_t flags;
   void* id;
   void* params;
   void* body;
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
} program_t;

typedef string_t symbol_t;
typedef struct _symbol_list_node_t {
   compiled_parse_node_t const* symbol_node;
   uint8_t binding_flag;
   uint8_t symbol_type;
   struct _symbol_list_node_t* next;
   struct _symbol_list_node_t* sequence_prev; // not used anywhere yet
   struct _symbol_list_node_t* sequence_next;
} symbol_list_node_t;
typedef struct {
   symbol_list_node_t* head;
   symbol_list_node_t* tail;
} symbol_list_t;
typedef struct {
   compiled_parse_node_t const* original;
   compiled_parse_node_t const* duplicate;
} repeated_symbol_t;
typedef struct _scope_child_list_node_t scope_child_list_node_t;
typedef struct _scope_child_list_t {
   scope_child_list_node_t* head;
   scope_child_list_node_t* tail;
} scope_child_list_t;
typedef struct _label_list_node_t {
   compiled_parse_node_t const* symbol_node;
   struct _label_list_node_t* parent;
} label_list_node_t;
typedef struct _scope_t {
   uint8_t type;
   compiled_parse_node_t* identifier;
   repeated_symbol_t* first_duplicate;
   void* first_yield_or_await;
   symbol_list_node_t* head;
   symbol_list_node_t* tail;
   symbol_list_t** lexical_symbol_table;
   symbol_list_t** var_symbol_table;
   label_list_node_t* label_list_node;
} scope_t;
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
   // [16]
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
   // scanner flags [52]
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
   // parser [88]
   token_t* parse_token;
   cover_node_list_t cover_node_list;
   uint32_t depth;
   uint32_t semantic_flags;
   // scope
   symbol_list_node_t* symbol_list_node;
   scope_list_node_t* current_scope_list_node;
   scope_list_node_t* scope_list_node;
   scope_list_node_t* hoisting_scope_list_node;
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
