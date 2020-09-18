#ifndef _INTERFACE_H_
#define _INTERFACE_H_

typedef uint8_t token_id_t;
typedef struct {
   size_t begin;
   size_t end;
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
   size_t begin; \
   size_t end; \
   node_type_t type; \
   uint8_t group;

typedef struct {
   embed_parse_node();
} parse_node_t;

// every covered parse node must have the following binary compatibility
typedef struct {
   embed_parse_node();
   token_t* first_cover;
} covered_parse_node_t;

// parser node
typedef struct {
   embed_parse_node();
   uint8_t token_id;
} identifier_t;
typedef identifier_t literal_t;
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
   token_t* first_cover;
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
   embed_parse_node();
   uint8_t flags;
   token_t* token;
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
   token_t* first_cover;
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
   uint8_t operator_id;
   token_t* operator;
   void* argument;
} update_expression_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   uint8_t operator_id;
   token_t* operator;
   void* argument;
} unary_expression_t;

typedef struct {
   embed_parse_node();
   void* argument;
} await_expression_t;

typedef struct {
   embed_parse_node();
   uint8_t operator_id;
   token_t* operator;
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
   uint8_t operator_id;
   void* left;
   void* right;
   token_t* operator;
} assignment_expression_t;
// keep assignment_expression_t and assignment_pattern_t binary compatible
// it makes life easier to convert their interpretations in cover expressions
typedef struct {
   embed_parse_node();
   uint8_t operator_id;
   void* left;
   void* right;
} assignment_pattern_t;
typedef struct {
   embed_parse_node();
   void* left;
   void* right;
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
   void* init;
   void* test;
   void* update;
   void* body;
} for_statement_t;

typedef struct {
   embed_parse_node();
   void* left;
   void* right;
   void* body;
} for_in_statement_t;

typedef struct {
   embed_parse_node();
   uint8_t flags;
   void* left;
   void* right;
   void* body;
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
