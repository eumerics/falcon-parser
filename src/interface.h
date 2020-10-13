#ifndef _INTERFACE_H_
#define _INTERFACE_H_

typedef struct {
   char_t const* begin;
   char_t const* end;
} string_t;
typedef struct {
   char_t const* begin;
   char_t const* end;
   size_t offending_index;
   uint8_t compile_flags;
} compiled_string_t;

typedef struct _parse_list_node_t {
   void* parse_node;
   struct _parse_list_node_t* next;
} parse_list_node_t;
typedef struct {
   parse_list_node_t* head;
   parse_list_node_t* current;
   int node_count;
} parse_node_list_state_t;

typedef struct _cover_list_node_t {
   void* cover_node;
   struct _cover_list_node_t* prev;
   struct _cover_list_node_t* next;
} cover_list_node_t;
typedef struct {
   cover_list_node_t* head;
   cover_list_node_t* tail;
   size_t count;
} cover_node_list_t;

typedef string_t symbol_t;
typedef struct _symbol_list_node_t {
   symbol_t const* symbol;
   uint8_t binding_type;
   struct _symbol_list_node_t* next;
} symbol_list_node_t;
typedef struct _scope_t {
   struct _scope_t* parent;
   symbol_list_node_t** symbol_table;
} scope_t;
typedef struct _scope_list_node_t {
   scope_t* scope;
   struct _scope_list_node_t* prev;
   struct _scope_list_node_t* next;
} scope_list_node_t;

typedef uint8_t token_id_t;
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
} token_t;

typedef struct {
   char const* source;
} location_t;

/*
#define embed_parse_node() \
   location_t loc; \
   size_t begin; \
   size_t end; \
   uint8_t type;
*/
typedef uint8_t node_type_t;
typedef uint32_t params_t;

#define embed_parse_node() \
   char_t const* begin; \
   char_t const* end; \
   node_type_t type; \
   uint8_t group;
#define embed_compiled_parse_node() \
   embed_parse_node() \
   uint8_t flags; \
   compiled_string_t* compiled_string;

typedef struct {
   embed_parse_node();
} parse_node_t;

typedef struct {
   embed_compiled_parse_node();
} compiled_parse_node_t;

// every covered parse node must have the following binary compatibility
typedef struct {
   embed_parse_node();
   token_t const* first_cover;
} covered_parse_node_t;

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

// expressions
typedef struct {
   embed_parse_node();
} this_expression_t;

typedef struct {
   embed_parse_node();
   uint8_t has_trailing_comma;
   token_t const* first_cover;
   void* elements;
} array_expression_t;
// keep array_expression_t and array_pattern_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef array_expression_t array_pattern_t;

typedef struct {
   embed_parse_node();
   void* left;
   void* right;
} binding_assignment_t;
typedef struct {
   embed_parse_node();
   uint8_t has_trailing_comma;
   token_t const* first_cover;
   void* properties;
} object_expression_t;
// keep object_expression_t and object_pattern_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef object_expression_t object_pattern_t;

typedef struct {
   embed_parse_node();
   //void* elements;
   void* quasis;
   void* expressions;
} template_literal_t;
typedef struct {
   embed_compiled_parse_node();
} template_element_t;

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
   token_t const* first_cover;
   void* expression;
} parenthesized_expression_t;

typedef struct {
   embed_parse_node();
   void* argument;
} spread_element_t;
// keep spread_element_t and rest_element_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef spread_element_t rest_element_t;

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
} function_declaration_t;
typedef function_declaration_t function_expression_t;
// we will keep the redundant id for convenience and for compatibility with
// estree specification
typedef function_declaration_t arrow_function_expression_t;

typedef struct {
   embed_parse_node();
   void* body;
} class_body_t;
typedef struct {
   embed_parse_node();
   void* id;
   void* super_class;
   void* body;
} class_declaration_t;
typedef class_declaration_t class_expression_t;

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
   uint8_t flags;
   void* argument;
} yield_expression_t;

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
   void* source;
} import_expression_t;

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
   void* argument;
} await_expression_t;

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

/*
typedef struct {
   embed_parse_node();
   void* left;
   void* right;
} assignment_pattern_t;
*/
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
   void* left;
   void* right;
   cover_list_node_t* cover_node;
} initialized_name_t;

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
} super_t;

typedef struct {
   embed_parse_node();
   void* meta;
   void* property;
} meta_property_t;

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
   uint8_t source_type;
   void* body;
} program_t;

#endif //_INTERFACE_H_
