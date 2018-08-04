#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_value_integer(sunce_json_node_t* node, sunce_integer_t value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE("%ld", value);
  node->value.type = SUNCE_JSON_VALUE_TYPE_INTEGER;
  node->value.value.integer_u = value;
}
