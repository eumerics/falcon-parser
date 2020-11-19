#ifndef _MESSAGES_H_
#define _MESSAGES_H_

char const* const unknown_token = "unknown token";
char const* parse_token_name[256] = {unknown_token};

#define define_error(_id, type, _message) \
   parse_error_t const error_##type = {.id = _id, .message = _message};
#define set_error(x) state->parse_error = &error_##x;
#define return_error(x, value) { set_error(x); return value; }
#define return_scan_error(x, _code, value) { \
   set_error(x); \
   state->code = _code; \
   state->error_position = make_position(state); \
   return value; \
}
#define return_compiled_error(compiled_string, value) { \
   compiled_string_t const* _compiled_string = compiled_string; \
   state->parse_error = _compiled_string->offending_error; \
   state->error_position = _compiled_string->offending_position; \
   return value; \
}
#define return_position_error(x, position, value) { \
   state->error_position = position; \
   return_error(x, value); \
}
#define return_location_error(x, location, value) { \
   location_t const* _location = location; \
   if(_location) state->error_position = _location->begin; \
   return_error(x, value); \
}
#define return_location_end_error(x, location, value) { \
   location_t const* _location = location; \
   if(_location) state->error_position = _location->end; \
   return_error(x, value); \
}
#define return_node_error(x, node, value) { \
   return_location_error(x, ((parse_node_t*)(node))->location, value); \
}
#define return_token_error(x, token, value) { \
   return_location_error(x, &(token->location), value); \
}

define_error(0x0001, lvalue, "assigning to non-lvalue");
define_error(0x0006, binding_identifier, "lvalue of a binding pattern must be an identifier");
define_error(0x0002, middle_rest, "rest element must be the last element in a sequence");
define_error(0x0003, rest_argument, "invalid assignment target for a rest element");
define_error(0x0004, object_assignment_rest, "invalid assignment target for a rest element in an object assigment");
define_error(0x0004, object_binding_rest, "invalid assignment target for a rest element in an object pattern");
define_error(0x0005, non_assignment,
   "invalid assignment operator in a binding or assignment pattern"
);
define_error(0x0006, unexpected_await, "await is valid only in async functions and async generators");
define_error(0x0007, missing_binding_initializer, "missing initializer in a destructuring declaration");
define_error(0x0008, missing_const_initializer, "missing initializer in a const declaration");
define_error(0x0009, missing_import_specifier, "missing import specifier");
define_error(0x000a, expecting_unicode_sequence, "expecting unicode escape sequence");
define_error(0x000b, not_enough_hexdigits, "not enough hex digits in unicode escape sequence");
define_error(0x000c, missing_unicode_closing, "missing closing parenthesis in unicode escape sequence");
define_error(0x000d, missing_leading_surrogate, "UTF16 coding error; missing leading surrogate");
define_error(0x000e, missing_trailing_surrogate, "UTF16 coding error; missing trailing surrogate");
define_error(0x000f, surrogate_in_identifier,
   "Unicode character in an identifier must not be a surrogate. "
   "Instead of specifying a surrogate pair, use unicode escape sequence format \\u{xxxxx}."
);
define_error(0x0010, contextual_identifier, "identifier cannot be a contextual reserved word");
define_error(0x0011, contextual_label, "label cannot be a contextual reserved word");
define_error(0x0012, trailing_comma, "unexpected trailing comma");
define_error(0x0013, invalid_binding_element, "invalid binding element");
define_error(0x0014, initializer_in_for, "initialier is not allowed in for-in/for-of statement");
define_error(0x0015, missing_try_handler, "one of catch or finally handler must be defined for try");
define_error(0x0016, octal_in_strict, "octal string literal is not allowed in strict mode");
define_error(0x0017, for_of_begins_with_let, "for-of statement cannot begin with non-declarative let");
define_error(0x0018, invalid_for_assignment, "invalid assignment target in for-in / for-of left-hand-side");
define_error(0x0019, standalone_super, "super keyword can only be used to access super class properties and methods");
define_error(0x001a, import_in_non_module, "import keyword can only appear in a module");
define_error(0x001b, new_meta, "new meta property can only appear inside a function");
define_error(0x001c, invalid_strict_mode_identifier, "invalid strict mode identifier");
define_error(0x001d, unicode_keyword, "keywords cannot be specified with unicode escape sequences");
define_error(0x001e, yield_in_strict_mode, "yield is a reserved word in strict mode");
define_error(0x001f, await_in_module, "await is a reserved word in module");
define_error(0x0020, eval_args_in_strict_mode, "eval and arguments are invalid as references in strict mode");
define_error(0x0021, invalid_update, "invalid increment/decrement operand");
define_error(0x0022, invalid_labeled, "labeled statement is not allowed here");
define_error(0x0023, duplicate_symbol, "redeclaration of variable");
define_error(0x0024, duplicate_label, "redeclaration of label");
define_error(0x0025, let_in_lexical, "a lexical declaration cannot declare a variable named let");
define_error(0x0026, with_in_strict_mode, "with statement cannot be used in strict mode");
define_error(0x0027, invalid_constructor, "constructor must not be a getter, setter, async, generator or async-generator");
define_error(0x0028, unsyntatic_continue, "continue statement must be inside a loop");
define_error(0x0029, unsyntatic_break, "unlabeled break statement must be inside a loop or switch statement");
define_error(0x002a, unsyntatic_return, "return statement must be inside a function");
define_error(0x002b, undefined_label, "undefined label");
define_error(0x002c, misplaced_super_property, "super property can only be accessed inside methods");
define_error(0x002d, misplaced_super_call, "super call can only appear in class constructors");
define_error(0x002e, eval_or_arguments_in_strict_mode, "eval/arguments cannot be used as a binding identifier in strict mode");
define_error(0x0031, duplicate_export, "duplicate export symbol");
define_error(0x0032, duplicate_default_export, "duplicate default export");
define_error(0x0033, missing_export_reference, "missing export reference");
define_error(0x0034, elision_in_binding_pattern, "elisiion is not allowed in a destructuring pattern");
define_error(0x0035, expecting_binding_identifier, "expecting a binding indentifier");
define_error(0x0036, duplicate_constructor, "duplicate constructor");
define_error(0x0037, static_prototype, "static prototype method is not allowed");
define_error(0x0038, identifier_deletion, "deleting a variable is not allowed in strict mode");
define_error(0x0039, invalid_strict_mode, "strict mode is not allowed when formal parameters are not simple");
define_error(0x003a, no_labeled_function, "labeled function cannot be used here");
define_error(0x003b, yield_await_in_arrow_params, "yield or arrow expression in arrow parameters");
define_error(0x003c, duplicate_prototype, "duplicate __proto__ property");
define_error(0x003d, duplicate_regexp_flag, "duplicate regular expression flag");
define_error(0x003e, invalid_regexp_flag, "invalid regular expression flag");
define_error(0x003f, annex_numeral, "numeric literals cannot start with 0 in strcit mode");
define_error(0x0040, expecting_of, "expecting 'of' token in a for-of statement");
define_error(0x0041, newline_in_string_literal, "unescaped line feed and carriage return are not allowed in a string literal");
define_error(0x0042, invalid_escape_sequence, "octal or decimal escape sequence is not allowed here");
define_error(0x0043, unterminated_string, "unterminated string literal");
define_error(0x0044, unterminated_template, "unterminated template literal");
define_error(0x0045, unterminated_regexp, "unterminated regular expression");
define_error(0x0046, terminated_regexp, "line terminator in a regular expression is invalid");
define_error(0x0047, unicode_range, "unicode code point is out of unicode range");
define_error(0x0048, unexpected_for_await, "for-await statement can only appear in async functions and async generators");
define_error(0x0049, duplicate_default_clause, "duplicate default clause in a switch statement");
define_error(0x004a, invalid_assignment_target, "invalid assignment target");
define_error(0x004b, invalid_binding_target, "invalid binding target");
define_error(0x004c, invalid_cover_grammar, "invalid cover grammar");
define_error(0x004d, empty_parenthetical, "empty parenthesized expression");
define_error(0x004e, missing_parenthesis, "expecting closing parenthesis");

define_error(0x1000, missing_assignment_or_binding_flag,
   "internal-error: change flags must have one of assignment or binding flag"
);
define_error(0x1001, is_not_a_property_node,
   "internal-error: all the properties of an object node must be of property_t type"
);
define_error(0x1002, null_node_in_change_types,
   "internal-error: null node encounted while changing node types of cover grammar"
);
define_error(0x1003, null_node_in_bind_nodes,
   "internal-error: null node encounted while binding nodes of cover grammar"
);

#endif //_MESSAGES_H_
