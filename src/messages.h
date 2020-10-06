#ifndef _MESSAGES_H_
#define _MESSAGES_H_

char const* const unknown_token = "unknown token";
char const* parse_token_name[256] = {unknown_token};

#define define_error(id, type, message) \
   uint16_t const error_##type##_id = id; \
   char const* error_##type##_message = message;

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

define_error(0x1000, missing_assignment_or_binding_flag,
   "internal-error: change flags must have one of assignment or binding flag"
);
define_error(0x1001, is_not_a_property_node,
   "internal-error: all the properties of an object node must be of property_t type"
);
define_error(0x1002, null_node_in_change_types,
   "internal-error: null node encounted while changing node types of cover grammar"
);

#endif //_MESSAGES_H_
