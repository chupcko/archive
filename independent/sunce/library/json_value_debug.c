#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_value_debug(sunce_json_value_t* value, sunce_size_t indent)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  switch(value->type)
  {
    case SUNCE_JSON_VALUE_TYPE_BOOLEAN:
      printf("boolean %s\n", sunce_boolean_string(value->value.boolean_u));
      break;
    case SUNCE_JSON_VALUE_TYPE_UNKNOWN:
      printf("unknown\n");
      break;
    case SUNCE_JSON_VALUE_TYPE_INTEGER:
      printf("integer %ld\n", value->value.integer_u);
      break;
    case SUNCE_JSON_VALUE_TYPE_FLOAT:
      printf("float %f\n", value->value.float_u);
      break;
    case SUNCE_JSON_VALUE_TYPE_STRING:
      printf("string \"%s\"\n", value->value.string_u);
      break;
    case SUNCE_JSON_VALUE_TYPE_MAP:
      sunce_json_nodes_debug(value->value.map_u, SUNCE_TRUE, indent+1);
      break;
    case SUNCE_JSON_VALUE_TYPE_ARRAY:
      sunce_json_nodes_debug(value->value.array_u, SUNCE_FALSE, indent+1);
      break;
  }
}
