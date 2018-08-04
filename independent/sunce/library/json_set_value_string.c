#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_value_string(sunce_json_node_t* node, sunce_string_t value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE("\"%s\"", value);
  node->value.type = SUNCE_JSON_VALUE_TYPE_STRING;
  node->value.value.string_u = value;
}
