#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_set_root(sunce_json_t* json, sunce_json_node_t* root)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  json->nodes = root;
}
