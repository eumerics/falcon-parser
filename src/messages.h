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

define_error(0x1000, missing_assignment_or_binding_flag,
   "internal-error: change flags must have one of assignment or binding flag"
);
define_error(0x1001, is_not_a_property_node,
   "internal-error: all the properties of an object node must be of property_t type"
);
define_error(0x1002, null_node_in_change_types,
   "internal-error: null node encounted while changing node types of cover grammar"
);
