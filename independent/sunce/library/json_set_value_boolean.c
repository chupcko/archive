#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_value_boolean(sunce_json_node_t* node, sunce_boolean_t value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE("%s", sunce_boolean_string(value));
  node->value.type = SUNCE_JSON_VALUE_TYPE_BOOLEAN;
  node->value.value.boolean_u = value;
}
