#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <stdint.h>

#if defined(UTF16)
   uint8_t const has_flag_utf16 = 0x01;
#else
   uint8_t const has_flag_utf16 = 0x00;
#endif

uint16_t const mask_none = 0x0000;
uint16_t const mask_strict_reserved_word = 0x0001;
uint16_t const mask_always_a_reserved_word = 0x0002;
uint16_t const mask_contextual_reserved_word = 0x0080;
uint16_t const mask_identifier = 0x0004;
uint16_t const mask_reserved_word = mask_always_a_reserved_word | mask_strict_reserved_word | mask_contextual_reserved_word;
uint16_t const mask_idname = mask_identifier | mask_reserved_word;
uint16_t const mask_update_ops = 0x0008;
uint16_t const mask_assign_ops = 0x0010;
uint16_t const mask_unary_ops = 0x0020;
uint16_t const mask_binary_ops = 0x0040;
uint16_t const mask_parentheses = 0x0000; //0x0080 unused
uint16_t const mask_arithmetic_ops = 0x0100;
uint16_t const mask_shift_ops = 0x0200;
uint16_t const mask_logical_ops = 0x0400;
uint16_t const mask_comparison_ops = 0x0800;
uint16_t const mask_variable_declarator = 0x1000;
uint16_t const mask_literal = 0x2000;
uint16_t const mask_expression_exclusions = 0x4000;
uint16_t const mask_let_inclusions = 0x8000;

uint8_t const token_flag_none = 0x00;
uint8_t const token_flag_newline = 0x01;
uint8_t const token_flag_escaped = 0x02;
uint8_t const token_flag_for = 0x04;
uint8_t const token_flag_loop = 0x08;

// token types
uint8_t const tkn_base = 0x80;
uint8_t const tkn_numeric_literal = tkn_base + 1;
uint8_t const tkn_string_literal = tkn_base + 2;
uint8_t const tkn_regexp_literal = tkn_base + 3;
uint8_t const tkn_template_string = tkn_base + 4;
uint8_t const tkn_identifier = tkn_base + 5;
uint8_t const tkn_punctuator = tkn_base + 6;
uint8_t const tkn_terminator = tkn_base + 7;
uint8_t const tkn_whitespace = tkn_base + 8;
uint8_t const tkn_comment = tkn_base + 9;
uint8_t const tkn_keyword = tkn_base + 10;

// punctuators
uint8_t const pnct_base = 0x90;
// comparison operators
uint8_t const pnct_equals = pnct_base + 0;
uint8_t const pnct_strict_equals = pnct_base + 1;
uint8_t const pnct_not_equals = pnct_base + 2;
uint8_t const pnct_strict_not_equals = pnct_base + 3;
uint8_t const pnct_lesser_or_equals = pnct_base + 4;
uint8_t const pnct_greater_or_equals = pnct_base + 5;
// logical operators
uint8_t const pnct_logical_and = pnct_base + 6;
uint8_t const pnct_logical_or = pnct_base + 7;
uint8_t const pnct_logical_coalesce = pnct_base + 8;
// bit manipulation operators
uint8_t const pnct_shift_left = pnct_base + 9;
uint8_t const pnct_shift_right = pnct_base + 10;
uint8_t const pnct_unsigned_shift_right = pnct_base + 11;
// update operators
uint8_t const pnct_increment = pnct_base + 12;
uint8_t const pnct_decrement = pnct_base + 13;
uint8_t const pnct_inplace_add = pnct_base + 14;
uint8_t const pnct_inplace_substract = pnct_base + 15;
uint8_t const pnct_inplace_mulitply = pnct_base + 16;
uint8_t const pnct_inplace_divide = pnct_base + 17;
uint8_t const pnct_inplace_remainder = pnct_base + 18;
uint8_t const pnct_inplace_exponentiation = pnct_base + 19;
uint8_t const pnct_inplace_logical_and = pnct_base + 20;
uint8_t const pnct_inplace_logical_or = pnct_base + 21;
uint8_t const pnct_inplace_logical_coalesce = pnct_base + 22;
uint8_t const pnct_inplace_binary_and = pnct_base + 23;
uint8_t const pnct_inplace_binary_or = pnct_base + 24;
uint8_t const pnct_inplace_binary_xor = pnct_base + 25;
uint8_t const pnct_inplace_shift_left = pnct_base + 26;
uint8_t const pnct_inplace_shift_right = pnct_base + 27;
uint8_t const pnct_inplace_unsigned_shift_right = pnct_base + 28;
// other operators
uint8_t const pnct_exponentitation = pnct_base + 29;
uint8_t const pnct_arrow = pnct_base + 30;
uint8_t const pnct_spread = pnct_base + 31;
uint8_t const pnct_optional = pnct_base + 32;
/*
uint8_t const pnct_ = pnct_base + 0;
*/
uint8_t const tkn_eot = 0xfe;
uint8_t const tkn_error = 0xff;

// [WATCHOUT] maximum number of precedence types is 32 (5-bits)
uint8_t const precedence_none = 0x00;
uint8_t const precedence_multiplicative = 0x01; // * / %
uint8_t const precedence_additive = 0x02; // + -
uint8_t const precedence_shift = 0x03; // << >> >>>
uint8_t const precedence_relational = 0x04; // < > <= >= instanceof in
uint8_t const precedence_equality = 0x05; // == != === !==
uint8_t const precedence_bitwise_and = 0x06; // &
uint8_t const precedence_bitwise_xor = 0x07; // ^
uint8_t const precedence_bitwise_or = 0x08; // |
uint8_t const precedence_logical_and = 0x09; // &&
uint8_t const precedence_logical_or = 0x0a; // ||
uint8_t const precedence_logical_coalesce = 0x0b; // ??

// reserved words
uint8_t const base = 0xc0;
uint8_t const rw_await = base + 0, rw_break = base + 1, rw_case = base + 2;
uint8_t const rw_catch = base + 3, rw_class = base + 4, rw_const = base + 5;
uint8_t const rw_continue = base + 6, rw_debugger = base + 7, rw_default = base + 8;
uint8_t const rw_delete = base + 9, rw_do = base + 10, rw_else = base + 11;
uint8_t const rw_enum = base + 12, rw_export = base + 13, rw_extends = base + 14;
uint8_t const rw_false = base + 15, rw_finally = base + 16, rw_for = base + 17;
uint8_t const rw_function = base + 18, rw_if = base + 19, rw_import = base + 20;
uint8_t const rw_in = base + 21, rw_instanceof = base + 22, rw_new = base + 23;
uint8_t const rw_null = base + 24, rw_return = base + 25, rw_super = base + 26;
uint8_t const rw_switch = base + 27, rw_this = base + 28, rw_throw = base + 29;
uint8_t const rw_true = base + 30, rw_try = base + 31, rw_typeof = base + 32;
uint8_t const rw_var = base + 33, rw_void = base + 34, rw_while = base + 35;
uint8_t const rw_with = base + 36, rw_yield = base + 37;
//
uint8_t const rw_let = base + 38, rw_static = base + 39;
uint8_t const rw_implements = base + 40, rw_interface = base + 41;
uint8_t const rw_package = base + 42, rw_private = base + 43;
uint8_t const rw_protected = base + 44, rw_public = base + 45;
//
uint8_t const rw_as = base + 46, rw_async = base + 47, rw_from = base + 48;
uint8_t const rw_get = base + 49, rw_of = base + 50, rw_set = base + 51;
uint8_t const rw_target = base + 52;
//
uint8_t const rw_constructor = base + 53;
uint8_t const rw_eval = base + 54, rw_arguments = base + 55;

// reserved word group
//[NOTE] yield and await are not marked as reserved words
#define SRW mask_strict_reserved_word
#define CRW mask_contextual_reserved_word
#define RW mask_reserved_word
#define ID mask_identifier
#define UN mask_unary_ops
#define BI mask_binary_ops
#define VAR mask_variable_declarator
#define LIT mask_literal
#define EXP mask_expression_exclusions
//
uint16_t const rwg_await = CRW|ID, rwg_break = RW, rwg_case = RW;
uint16_t const rwg_catch = RW, rwg_class = RW|EXP, rwg_const = RW|VAR;
uint16_t const rwg_continue = RW, rwg_debugger = RW, rwg_default = RW;
uint16_t const rwg_delete = RW|UN, rwg_do = RW, rwg_else = RW;
uint16_t const rwg_enum = RW, rwg_export = RW, rwg_extends = RW;
uint16_t const rwg_false = RW|LIT, rwg_finally = RW, rwg_for = RW;
uint16_t const rwg_function = RW|EXP, rwg_if = RW, rwg_import = RW;
uint16_t const rwg_in = RW|BI, rwg_instanceof = RW|BI, rwg_new = RW;
uint16_t const rwg_null = RW|LIT, rwg_return = RW, rwg_super = RW;
uint16_t const rwg_switch = RW, rwg_this = RW, rwg_throw = RW;
uint16_t const rwg_true = RW|LIT, rwg_try = RW, rwg_typeof = RW|UN;
uint16_t const rwg_var = RW|VAR, rwg_void = RW|UN, rwg_while = RW;
uint16_t const rwg_with = RW, rwg_yield = CRW|ID;
//
uint16_t const rwg_let = SRW|ID|VAR|EXP, rwg_static = SRW|ID;
uint16_t const rwg_implements = SRW|ID, rwg_interface = SRW|ID, rwg_package = SRW|ID;
uint16_t const rwg_private = SRW|ID, rwg_protected = SRW|ID, rwg_public = SRW|ID;
//
uint16_t const rwg_as = ID, rwg_async = ID|EXP, rwg_from = ID;
uint16_t const rwg_get = ID, rwg_of = ID, rwg_set = ID;
uint16_t const rwg_target = ID;
//
uint16_t const rwg_constructor = ID;
uint16_t const rwg_eval = ID, rwg_arguments = ID;
//
#undef SRW
#undef CRW
#undef RW
#undef ID
#undef UN
#undef BI
#undef VAR
#undef LIT
#undef EXP

// reserved word precedence
uint8_t const rwp_await = 0, rwp_break = 0, rwp_case = 0;
uint8_t const rwp_catch = 0, rwp_class = 0, rwp_const = 0;
uint8_t const rwp_continue = 0, rwp_debugger = 0, rwp_default = 0;
uint8_t const rwp_delete = 0, rwp_do = 0, rwp_else = 0;
uint8_t const rwp_enum = 0, rwp_export = 0, rwp_extends = 0;
uint8_t const rwp_false = 0, rwp_finally = 0, rwp_for = 0;
uint8_t const rwp_function = 0, rwp_if = 0, rwp_import = 0;
uint8_t const rwp_in = precedence_relational;
uint8_t const rwp_instanceof = precedence_relational, rwp_new = 0;
uint8_t const rwp_null = 0, rwp_return = 0, rwp_super = 0;
uint8_t const rwp_switch = 0, rwp_this = 0, rwp_throw = 0;
uint8_t const rwp_true = 0, rwp_try = 0, rwp_typeof = 0;
uint8_t const rwp_var = 0, rwp_void = 0, rwp_while = 0;
uint8_t const rwp_with = 0, rwp_yield = 0;
uint8_t const rwp_let = 0, rwp_static = 0;
uint8_t const rwp_implements = 0, rwp_interface = 0, rwp_package = 0;
uint8_t const rwp_private = 0, rwp_protected = 0, rwp_public = 0;
uint8_t const rwp_as = 0, rwp_async = 0, rwp_from = 0;
uint8_t const rwp_get = 0, rwp_of = 0, rwp_set = 0, rwp_target = 0;
uint8_t const rwp_constructor = 0, rwp_eval = 0, rwp_arguments = 0;

uint8_t const node_group_none = 0x00;
//uint8_t const node_group_expression = 0x01;
//uint8_t const node_group_statement = 0x02;
uint8_t const node_group_literal = 0x04;
uint8_t const node_group_offending_cover_grammar = 0x20;
uint8_t const node_group_assignment_target = 0x40;
uint8_t const node_group_lhs_production = 0x80;

#define NONE    node_group_none
#define LHS     node_group_lhs_production
#define ASSIGN  node_group_assignment_target
#define COVER   node_group_offending_cover_grammar
#define LITERAL node_group_literal

// dummy node types
uint8_t const pnt_parse_node = 0;
uint8_t const pnt_parse_list_node = 0;
uint8_t const pnt_covered_parse_node = 0;

uint8_t const pnt_program = 1;
uint8_t const png_program = NONE;
uint8_t const pnt_identifier = 2;
uint8_t const png_identifier = LHS | ASSIGN;
uint8_t const pnt_literal = 3;
uint8_t const png_literal = LHS | LITERAL;
uint8_t const pnt_string_literal = 4;
uint8_t const png_string_literal = LHS | LITERAL;
uint8_t const pnt_regexp_literal = 7;
uint8_t const png_regexp_literal = LHS;
uint8_t const pnt_array_expression = 8;
uint8_t const png_array_expression = LHS | COVER;
uint8_t const pnt_object_expression = 9;
uint8_t const png_object_expression = LHS | COVER;
uint8_t const pnt_template_literal = 10;
uint8_t const png_template_literal = LHS;

// expressions
uint8_t const expression_base = 0x20;
uint8_t const pnt_this_expression = expression_base + 0;
uint8_t const png_this_expression = LHS;
uint8_t const pnt_property = expression_base + 1;
uint8_t const png_property = NONE;
uint8_t const pnt_spread_element = expression_base + 2;
uint8_t const png_spread_element = NONE;
uint8_t const pnt_function_expression = expression_base + 3;
uint8_t const png_function_expression = LHS;
//uint8_t const pnt__expression = expression_base + ;
//uint8_t const png__expression = NONE;
uint8_t const pnt_member_expression = expression_base + 4;
uint8_t const png_member_expression = LHS | ASSIGN;
uint8_t const pnt_tagged_template_expression = expression_base + 5;
uint8_t const png_tagged_template_expression = LHS;
uint8_t const pnt_new_expression = expression_base + 7;
uint8_t const png_new_expression = LHS;
uint8_t const pnt_call_expression = expression_base + 8;
uint8_t const png_call_expression = LHS;
uint8_t const pnt_covered_call_expression = expression_base + 9;
uint8_t const pnt_chain_expression = expression_base + 10;
uint8_t const png_chain_expression = LHS;
uint8_t const pnt_array_assignment_pattern = expression_base + 11;
uint8_t const png_array_assignment_pattern = LHS | ASSIGN | COVER;
uint8_t const pnt_object_assignment_pattern = expression_base + 12;
uint8_t const png_object_assignment_pattern = LHS | ASSIGN | COVER;
uint8_t const pnt_lhs_expression = expression_base + 13;
uint8_t const png_lhs_expression = LHS; // for inheritence checks only
uint8_t const pnt_update_expression = expression_base + 14;
uint8_t const png_update_expression = NONE;
uint8_t const pnt_unary_expression = expression_base + 15;
uint8_t const png_unary_expression = NONE;
uint8_t const pnt_binary_expression = expression_base + 16;
uint8_t const png_binary_expression = NONE;
uint8_t const pnt_logical_expression = expression_base + 17;
uint8_t const png_logical_expression = NONE;
uint8_t const pnt_conditional_expression = expression_base + 18;
uint8_t const png_conditional_expression = NONE;
uint8_t const pnt_arrow_function_expression = expression_base + 19;
uint8_t const png_arrow_function_expression = NONE;
uint8_t const pnt_assignment_expression = expression_base + 20;
uint8_t const png_assignment_expression = NONE;
uint8_t const pnt_expression = expression_base + 21;
uint8_t const png_expression = NONE;
uint8_t const pnt_assignment_property = expression_base + 22;
uint8_t const png_assignment_property = NONE;
uint8_t const pnt_rest_element = expression_base + 23;
uint8_t const png_rest_element = NONE;
uint8_t const pnt_yield_expression = expression_base + 24;
uint8_t const png_yield_expression = NONE;
uint8_t const pnt_class_expression = expression_base + 25;
uint8_t const png_class_expression = LHS;
uint8_t const pnt_await_expression = expression_base + 26;
uint8_t const png_await_expression = NONE;
uint8_t const pnt_import_expression = expression_base + 27;
uint8_t const png_import_expression = NONE;
uint8_t const pnt_parenthesized_expression = expression_base + 28;
uint8_t const png_parenthesized_expression = LHS | COVER;
/*
uint8_t const pnt__expression = expression_base + ;
uint8_t const png__expression = NONE;
*/
uint8_t const pnt_array_pattern = expression_base + 29;
uint8_t const png_array_pattern = NONE;
uint8_t const pnt_object_pattern = expression_base + 30;
uint8_t const png_object_pattern = NONE;
uint8_t const pnt_binding_assignment = expression_base + 31;
uint8_t const png_binding_assignment = NONE;
uint8_t const pnt_initialized_name = expression_base + 32;
uint8_t const png_initialized_name = NONE;

uint8_t const clause_base = 0x10;
uint8_t const pnt_catch_clause = clause_base + 0;
uint8_t const png_catch_clause = NONE;
uint8_t const pnt_case_clause = clause_base + 1;
uint8_t const png_case_clause = NONE;
uint8_t const pnt_function_body = clause_base + 2;
uint8_t const png_function_body = NONE;
uint8_t const pnt_class_body = clause_base + 3;
uint8_t const png_class_body = NONE;
uint8_t const pnt_method_definition = clause_base + 4;
uint8_t const png_method_definition = NONE;
uint8_t const pnt_super = clause_base + 5;
uint8_t const png_super = LHS | ASSIGN;
uint8_t const pnt_meta_property = clause_base + 6;
uint8_t const png_meta_property = LHS;
uint8_t const pnt_template_element = clause_base + 7;
uint8_t const png_template_element = NONE;

// statements
uint8_t const statement_base = 0x50;
uint8_t const pnt_block_statement = statement_base + 0;
uint8_t const png_block_statement = NONE;
uint8_t const pnt_empty_statement = statement_base + 1;
uint8_t const png_empty_statement = NONE;
uint8_t const pnt_expression_statement = statement_base + 2;
uint8_t const png_expression_statement = NONE;
uint8_t const pnt_if_statement = statement_base + 3;
uint8_t const png_if_statement = NONE;
uint8_t const pnt_do_statement = statement_base + 4;
uint8_t const png_do_statement = NONE;
uint8_t const pnt_while_statement = statement_base + 5;
uint8_t const png_while_statement = NONE;
uint8_t const pnt_for_statement = statement_base + 6;
uint8_t const png_for_statement = NONE;
uint8_t const pnt_for_in_statement = statement_base + 7;
uint8_t const png_for_in_statement = NONE;
uint8_t const pnt_for_of_statement = statement_base + 8;
uint8_t const png_for_of_statement = NONE;
uint8_t const pnt_switch_statement = statement_base + 9;
uint8_t const png_switch_statement = NONE;
uint8_t const pnt_continue_statement = statement_base + 10;
uint8_t const png_continue_statement = NONE;
uint8_t const pnt_break_statement = statement_base + 11;
uint8_t const png_break_statement = NONE;
uint8_t const pnt_return_statement = statement_base + 12;
uint8_t const png_return_statement = NONE;
uint8_t const pnt_with_statement = statement_base + 13;
uint8_t const png_with_statement = NONE;
uint8_t const pnt_labeled_statement = statement_base + 14;
uint8_t const png_labeled_statement = NONE;
uint8_t const pnt_throw_statement = statement_base + 15;
uint8_t const png_throw_statement = NONE;
uint8_t const pnt_try_statement = statement_base + 16;
uint8_t const png_try_statement = NONE;
uint8_t const pnt_debugger_statement = statement_base + 17;
uint8_t const png_debugger_statement = NONE;
uint8_t const pnt_directive = statement_base + 18;
uint8_t const png_directive = NONE;
/*
uint8_t const pnt__statement = statement_base + ;
uint8_t const png__statement = NONE;
*/

// declarations
uint8_t const declaration_base = 0x70;
uint8_t const pnt_variable_declaration = declaration_base + 0;
uint8_t const png_variable_declaration = NONE;
uint8_t const pnt_variable_declarator = declaration_base + 1;
uint8_t const png_variable_declarator = NONE;
uint8_t const pnt_function_declaration = declaration_base + 2;
uint8_t const png_function_declaration = NONE;
uint8_t const pnt_class_declaration = declaration_base + 3;
uint8_t const png_class_declaration = NONE;
uint8_t const pnt_import_declaration = declaration_base + 4;
uint8_t const png_import_declaration = NONE;
uint8_t const pnt_import_specifier = declaration_base + 5;
uint8_t const png_import_specifier = NONE;
uint8_t const pnt_import_default_specifier = declaration_base + 6;
uint8_t const png_import_default_specifier = NONE;
uint8_t const pnt_import_namespace_specifier = declaration_base + 7;
uint8_t const png_import_namespace_specifier = NONE;
uint8_t const pnt_export_all_declaration = declaration_base + 8;
uint8_t const png_export_all_declaration = NONE;
uint8_t const pnt_export_named_declaration = declaration_base + 9;
uint8_t const png_export_named_declaration = NONE;
uint8_t const pnt_export_default_declaration = declaration_base + 10;
uint8_t const png_export_default_declaration = NONE;
uint8_t const pnt_export_specifier = declaration_base + 11;
uint8_t const png_export_specifier = NONE;

// patterns
uint8_t const pattern_base = 0x90;
uint8_t const pnt_assignment_pattern = pattern_base + 0;
uint8_t const png_assignment_pattern = NONE;

uint8_t const program_kind_script = 0x01;
uint8_t const program_kind_module = 0x02;
uint8_t const property_kind_init = 0x01;
uint8_t const property_kind_get = 0x02;
uint8_t const property_kind_set = 0x03;
uint8_t const property_kind_method = 0x04;
uint8_t const property_kind_constructor = 0x05;

uint8_t const flag_none = 0x00;
//
uint8_t const status_flag_incomplete = 0x00;
uint8_t const status_flag_failed = 0x01;
uint8_t const status_flag_complete = 0x02;
//
uint8_t const property_flag_method = 0x01;
uint8_t const property_flag_shorthand = 0x02;
uint8_t const property_flag_computed = 0x04;
uint8_t const method_flag_special = 0x08;
uint8_t const method_flag_static = 0x20;
//
uint8_t const function_flag_expression = 0x01;
uint8_t const function_flag_generator = 0x02;
uint8_t const function_flag_async = 0x04;
//
uint8_t const member_flag_computed = 0x01;
uint8_t const optional_flag_optional = 0x02;
//
uint8_t const yield_flag_delegate = 0x01;
uint8_t const for_flag_await = 0x01;
uint8_t const operator_flag_prefix = 0x01;
uint8_t const template_flag_tail = 0x01;

uint32_t const param_flag_await = 0x0001 << 16;
uint32_t const param_flag_default = 0x0002 << 16;
uint32_t const param_flag_in = 0x0004 << 16;
uint32_t const param_flag_return = 0x0008 << 16;
uint32_t const param_flag_yield = 0x0010 << 16;
uint32_t const param_flag_tagged = 0x0020 << 16;
//
uint32_t const param_flag_strict_mode = 0x0001;
uint32_t const param_flag_loose_mode = 0x0002;
uint32_t const param_flag_module = 0x0004;
uint32_t const param_flag_annex = 0x0008;
//uint32_t const cover_flag_initializer = 0x0001; // both a param and state flag
uint32_t const cover_flag_parameters = 0x0020; // both a param and state flag
uint32_t const param_flag_for_binding = 0x0040;
uint32_t const param_flag_vanilla_function = 0x0080;
uint32_t const param_flag_function = 0x0100;
uint32_t const param_flag_class = 0x0200;
uint32_t const param_flag_formal = 0x0400;
uint32_t const param_flag_streaming = 0x8000;
/*
uint32_t const cover_flag_array = 0x0001;
uint32_t const cover_flag_assignment = 0x0002;
uint32_t const cover_flag_array_assignment = cover_flag_array | cover_flag_assignment;
*/

uint8_t const change_flag_assignment = 0x01;
uint8_t const change_flag_binding = 0x02;
uint8_t const change_flag_array = 0x04;
uint8_t const change_flag_object = 0x08;
//uint8_t const change_mask_cover = change_flag_assignment | change_flag_binding;
uint8_t const change_mask_group = ~(change_flag_array | change_flag_object);
uint8_t const change_flag_array_binding = change_flag_array | change_flag_binding;
uint8_t const change_flag_object_binding = change_flag_object | change_flag_binding;
uint8_t const change_flag_array_assignment = change_flag_array | change_flag_assignment;
uint8_t const change_flag_object_assignment = change_flag_object | change_flag_assignment;

uint8_t const compile_flag_source = 0x01;
uint8_t const compile_flag_octal = 0x02;
uint8_t const compile_flag_not_escape = 0x04;

uint32_t const syntatic_flag_break = 0x01;
uint32_t const syntatic_flag_continue = 0x02;

#undef NONE
#undef LHS
#undef ASSIGN
#undef COVER
#undef LITERAL

#endif //_CONSTANTS_H_
