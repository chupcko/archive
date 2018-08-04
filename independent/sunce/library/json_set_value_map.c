#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_value_map(sunce_json_node_t* node, sunce_json_node_t* value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  node->value.type = SUNCE_JSON_VALUE_TYPE_MAP;
  node->value.value.map_u = value;
}
