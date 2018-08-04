#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_next(sunce_json_t* json, sunce_json_node_t* node, sunce_json_node_t* next)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  node->next = next;
}
