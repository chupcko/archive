#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_nodes_debug(sunce_json_node_t* start_node, sunce_boolean_t is_map, sunce_size_t indent)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  if(is_map == SUNCE_TRUE)
    printf("map_begin\n");
  else
    printf("array_begin\n");
  sunce_json_node_t* node = start_node;
  while(node != SUNCE_END)
  {
    printf
    (
      SUNCE_INDENT_FORMAT
      "%p : %p ",
      SUNCE_INDENT(indent, 1, SUNCE_INDENT_STEP),
      node,
      node->next
    );
    if(is_map == SUNCE_TRUE)
      printf("\"%s\" ", node->name);
    sunce_json_value_debug(&node->value, indent);
    node = node->next;
  }
  if(is_map == SUNCE_TRUE)
    printf
    (
      SUNCE_INDENT_FORMAT
      "map_end\n",
      SUNCE_INDENT(indent, 0, SUNCE_INDENT_STEP)
    );
  else
    printf
    (
      SUNCE_INDENT_FORMAT
      "array_end\n",
      SUNCE_INDENT(indent, 0, SUNCE_INDENT_STEP)
    );
}
