#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_value_float(sunce_json_node_t* node, sunce_float_t value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE("%f", value);
  node->value.type = SUNCE_JSON_VALUE_TYPE_FLOAT;
  node->value.value.float_u = value;
}
