#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_value_array(sunce_json_node_t* node, sunce_json_node_t* value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  node->value.type = SUNCE_JSON_VALUE_TYPE_ARRAY;
  node->value.value.array_u = value;
}
