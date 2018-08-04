#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_name(sunce_json_t* json, sunce_json_node_t* node, const sunce_string_t name)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE("\"%s\"", name);
  node->name = name;
}
