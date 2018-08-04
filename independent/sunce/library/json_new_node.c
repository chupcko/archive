#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
sunce_json_node_t* sunce_json_new_node(sunce_json_t* json)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  sunce_json_node_t* node = (sunce_json_node_t*)sunce_json_malloc(json, sizeof(sunce_json_node_t));
  if(node == SUNCE_NULL)
    return SUNCE_NULL;
  node->name = SUNCE_NULL;
  node->value.type = SUNCE_JSON_VALUE_TYPE_UNKNOWN;
  node->next = SUNCE_END;
  return node;
}
